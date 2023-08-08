#include "mainwindow.h"
#include "formdialog.h"
#include "../exceptions.h"
#include <QMessageBox>

void MainWindow::add_port() {
    FormDialog form("Add source port", "Port name", false);
    int result = form.exec();

    QMessageBox error;
    error.setIcon(QMessageBox::Warning);
    error.setStandardButtons(QMessageBox::Ok);

    if (result == QDialog::Accepted) {
        auto results = form.get_data();

        try {
            m_sourceport_controller.add(results[0], results[1], results[2]);
            save_configs();
        } catch (PortNotFoundException& e) {
            error.setText("Unable to open source port!");
            error.exec();
        } catch (PortNotExecutableException& e) {
            error.setText("Source port must be an executable!");
            error.exec();
        }
    }
}

void MainWindow::edit_port(int index) {
    if (index < 0 || index >= m_sourceport_controller.rowCount() - 1) return;

    QString name = m_sourceport_controller.get_at(index, 0).toString();
    QString path = m_sourceport_controller.get_at(index, 1).toString();
    QString params = m_sourceport_controller.get_at(index, 2).toString();

    FormDialog form("Edit source port", "Port name", false, name, path, params);
    int result = form.exec();

    if (result == QDialog::Accepted) {
        auto results = form.get_data();

        QMessageBox error;
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);

        try {
            m_sourceport_controller.edit(index, results[0], results[1], results[2]);
            save_configs();
        } catch (PortNotFoundException&) {
            error.setText("Unable to open source port!");
            error.exec();
        } catch (PortNotExecutableException&) {
            error.setText("Source port must be an executable!");
            error.exec();
        }
    }
}

void MainWindow::delete_port(int index) {
    if (index < 0 || index > m_sourceport_controller.rowCount() - 1) return;

    QString port_name = m_sourceport_controller.get_at(index, 0).toString();

    QMessageBox warning;
    warning.setText("Are you sure you want to remove " + port_name +
                    " from your source ports list?");
    warning.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    warning.setIcon(QMessageBox::Warning);

    int result = warning.exec();

    if (result == QMessageBox::Ok) {
        m_sourceport_controller.remove(index);
        save_configs();
    }
}

void MainWindow::move_port_up(int index) {
    if (index < 1 || index > m_sourceport_controller.rowCount() - 1) return;

    m_sourceport_controller.move_up(index);
    save_configs();
}

void MainWindow::move_port_down(int index) {
    if (index < 0 || index > m_sourceport_controller.rowCount() - 2) return;

    m_sourceport_controller.move_down(index);
    save_configs();
}
