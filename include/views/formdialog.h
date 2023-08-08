#ifndef FORMDIALOG_H
#define FORMDIALOG_H

#include <QDialog>

// Namespace declaration
namespace Ui {
class FormDialog;
}

/**
 * @brief View class for the Add/Edit sourceport/IWAD dialog window.
 */
class FormDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Creates a FormDialog instance
     * @param window_title The dialog's title.
     * @param label The label to be added to the "Instance name" field.
     * @param is_wad Whether it is an IWAD adding/editing dialog.
     * @param name String to be initially placed in the "Name" field.
     * @param path String to be initially placed in the "Path" field.
     * @param params String to be initially placed in the "Parameters" field.
     * @param parent The dialog's parent widget.
     */
    explicit FormDialog(const QString& window_title, const QString& label, bool is_wad,
                        const QString& name = "", const QString& path = "",
                        const QString& params = "", QWidget *parent = nullptr);

    /**
     * Class destructor.
     */
    ~FormDialog();

    /**
     * @brief Returns the input name, path and params as a QStringList.
     */
    QList<QString> get_data();

private slots:
    /**
     * @brief Fired when the "Open file" button is clicked.
     */
    void on_button_file_clicked();

private:
    Ui::FormDialog *ui;
    bool m_is_wad;
    void done(int r) override;
};

#endif // FORMDIALOG_H
