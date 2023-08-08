#include "mainwindow.h"
#include "formdialog.h"
#include "../exceptions.h"
#include <QMessageBox>

void MainWindow::add_iwad() {
    FormDialog form("Add IWAD", "IWAD name", true);

    int result = form.exec();

    if (result == QDialog::Accepted) {
        auto results = form.get_data();

        QMessageBox error;
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);

        try {
            m_iwad_controller.add(results[0], results[1], results[2]);
            save_configs();
        } catch (WADNotFoundException&) {
            error.setText("Unable to open WAD!");
            error.exec();
        }
    }
}

void MainWindow::edit_iwad(int index) {
    if (index < 0 || index > m_iwad_controller.rowCount() - 1) return;

    QString name = m_iwad_controller.get_at(index, 0).toString();
    QString path = m_iwad_controller.get_at(index, 1).toString();
    QString params = m_iwad_controller.get_at(index, 2).toString();

    FormDialog form("Edit IWAD", "IWAD name", true, name, path, params);

    int result = form.exec();

    if (result == QDialog::Accepted) {
        auto results = form.get_data();

        QMessageBox error;
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);

        try {
            m_iwad_controller.edit(index, results[0], results[1], results[2]);
            save_configs();
        } catch (WADNotFoundException& w) {
            error.setText("Unable to open WAD!");
            error.exec();
        }
    }
}

void MainWindow::delete_iwad(int index) {
    if (index < 0 || index > m_iwad_controller.rowCount() - 1) return;

    QString iwad_name = m_iwad_controller.get_at(index, 0).toString();

    QMessageBox warning;
    warning.setText("Are you sure you want to remove " + iwad_name +
                    " from your IWADs list?");
    warning.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    warning.setIcon(QMessageBox::Warning);

    int result = warning.exec();

    if (result == QMessageBox::Ok) {
        m_iwad_controller.remove(index);
        save_configs();
    }
}

void MainWindow::move_iwad_up(int index) {
    if (index < 1 || index > m_iwad_controller.rowCount() - 1) return;

    m_iwad_controller.move_up(index);
    save_configs();
}

void MainWindow::move_iwad_down(int index) {
    if (index < 0 || index > m_iwad_controller.rowCount() - 2) return;

    m_iwad_controller.move_down(index);
    save_configs();
}
