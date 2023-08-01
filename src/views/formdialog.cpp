#include "formdialog.h"
#include "ui_formdialog.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QFileSystemModel>

FormDialog::FormDialog(const QString& window_title, const QString& label, bool is_wad,
                       const QString& name, const QString& path, const QString& params,
                       QWidget *parent) :
    QDialog(parent), ui(new Ui::FormDialog), m_is_wad(is_wad) {
    ui->setupUi(this);
    this->setWindowTitle(window_title);

    ui->label_type->setText(label);
    ui->entry_name->setText(name);
    ui->entry_path->setText(path);
    ui->entry_params->setText(params);
}

FormDialog::~FormDialog() {
    delete ui;
}

QList<QString> FormDialog::get_data() {
    QList<QString> result;

    result.append(ui->entry_name->text());
    result.append(ui->entry_path->text());
    result.append(ui->entry_params->text());

    return result;
}

void FormDialog::done(int r) {
    if (r == QDialog::Accepted) {
        QString name = ui->entry_name->text();
        QString path = ui->entry_path->text();

        QMessageBox error;
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);

        if (name.trimmed() == "") {
            error.setText("A valid name must be informed.");
            error.exec();
            return;
        }

        if (path.trimmed() == "") {
            error.setText("A valid file path must be informed.");
            error.exec();
            return;
        }

        QFileInfo file(path);

        if (!file.exists()) {
            error.setText("The informed file does not exist.");
            error.exec();
            return;
        }

        if (m_is_wad && file.suffix().toLower() != "wad") {
            error.setText("The informed file is not a WAD.");
            error.exec();
            return;
        }

        if (!m_is_wad && !file.isExecutable()) {
            error.setText("The informed file is not an executable.");
            error.exec();
            return;
        }
    }

    QDialog::done(r);
    return;
}

void FormDialog::on_button_file_clicked() {
    QString path;
    QFileInfo current_path(ui->entry_path->text());
    QString starting_path = current_path.exists() ? current_path.absoluteFilePath() : QDir::currentPath();
    if (m_is_wad) {
        QFileDialog dialog(this);

        path = dialog.getOpenFileName(this, tr("Select IWAD"), starting_path,
                                      tr("Doom IWAD Files (*.wad *.WAD)"));
    } else {
        QFileDialog dialog(this);
#ifdef _WIN32
        path = dialog.getOpenFileName(this, tr("Select executable"), starting_path,
                                      tr("Executable files (*.exe)"));

#else
        path = dialog.getOpenFileName(this, tr("Select executable"), starting_path);
#endif
    }

    ui->entry_path->setText(path);
}
