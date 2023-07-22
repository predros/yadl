#ifndef FORMDIALOG_H
#define FORMDIALOG_H

#include <QDialog>

namespace Ui {
class FormDialog;
}

class FormDialog : public QDialog {
    Q_OBJECT

public:
    explicit FormDialog(const QString& window_title, const QString& label, bool is_wad,
                        const QString& name = "", const QString& path = "",
                        const QString& params = "", QWidget *parent = nullptr);
    ~FormDialog();
    QList<QString> get_data();

private slots:
    void on_button_file_clicked();

private:
    Ui::FormDialog *ui;
    bool m_is_wad;
    void done(int r) override;
};

#endif // FORMDIALOG_H
