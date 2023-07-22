#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formdialog.h"
#include "../exceptions.h"
#include <QMessageBox>

void MainWindow::on_tab2_bt_portadd_clicked() {
    FormDialog form("Add source port", "Port name", false);
    int result = form.exec();

    QMessageBox error;
    error.setIcon(QMessageBox::Warning);
    error.setStandardButtons(QMessageBox::Ok);

    if (result == QDialog::Accepted) {
        auto results = form.get_data();

        try {
            m_sourceport_model.add(results[0], results[1], results[2]);
            save_to_JSON();
        } catch (PortNotFoundException& e) {
            error.setText("Unable to open source port!");
            error.exec();
        } catch (PortNotExecutableException& e) {
            error.setText("Source port must be an executable!");
            error.exec();
        }
    }
}

void MainWindow::on_tab2_bt_portedit_clicked() {
    int current_index = ui->tab2_table_ports->currentIndex().row();

    if (current_index == -1) return;

    QString name = m_sourceport_model.get_at(current_index, 0).toString();
    QString path = m_sourceport_model.get_at(current_index, 1).toString();
    QString params = m_sourceport_model.get_at(current_index, 2).toString();

    FormDialog form("Edit source port", "Port name", false, name, path, params);
    int result = form.exec();

    if (result == QDialog::Accepted) {
        auto results = form.get_data();

        QMessageBox error;
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);

        try {
            m_sourceport_model.edit(current_index, results[0], results[1], results[2]);
            save_to_JSON();
        } catch (PortNotFoundException&) {
            error.setText("Unable to open source port!");
            error.exec();
        } catch (PortNotExecutableException&) {
            error.setText("Source port must be an executable!");
            error.exec();
        }
    }
}

void MainWindow::on_tab2_bt_portdel_clicked() {
    int current_index = ui->tab2_table_ports->currentIndex().row();

    if (current_index < 0 || current_index >= m_sourceport_model.rowCount()) return;

    QString port_name = m_sourceport_model.get_at(current_index, 0).toString();

    QMessageBox warning;
    warning.setText("Are you sure you want to remove " + port_name +
                    " from your source ports list?");
    warning.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    warning.setIcon(QMessageBox::Warning);

    int result = warning.exec();

    if (result == QMessageBox::Ok) m_sourceport_model.remove(current_index);
}

void MainWindow::on_tab2_bt_portup_clicked() {
    int current_index = ui->tab2_table_ports->currentIndex().row();

    if (current_index < 1 || current_index >= m_sourceport_model.rowCount()) return;

    m_sourceport_model.move_up(current_index);
}

void MainWindow::on_tab2_bt_portdown_clicked() {
    int current_index = ui->tab2_table_ports->currentIndex().row();

    if (current_index < 0 || current_index >= m_sourceport_model.rowCount() - 1) return;

    m_sourceport_model.move_down(current_index);
}

void MainWindow::on_tab2_bt_iwadadd_clicked() {
    FormDialog form("Add IWAD", "IWAD name", true);

    int result = form.exec();

    if (result == QDialog::Accepted) {
        auto results = form.get_data();

        QMessageBox error;
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);

        try {
            m_iwad_model.add(results[0], results[1], results[2]);
            save_to_JSON();
        } catch (WADNotFoundException&) {
            error.setText("Unable to open WAD!");
            error.exec();
        }
    }
}

void MainWindow::on_tab2_bt_iwadedit_clicked() {
    int current_index = ui->tab2_table_iwads->currentIndex().row();

    if (current_index == -1) return;

    QString name = m_iwad_model.get_at(current_index, 0).toString();
    QString path = m_iwad_model.get_at(current_index, 1).toString();
    QString params = m_iwad_model.get_at(current_index, 2).toString();

    FormDialog form("Edit IWAD", "IWAD name", true, name, path, params);

    int result = form.exec();

    if (result == QDialog::Accepted) {
        auto results = form.get_data();

        QMessageBox error;
        error.setIcon(QMessageBox::Warning);
        error.setStandardButtons(QMessageBox::Ok);

        try {
            m_iwad_model.edit(current_index, results[0], results[1], results[2]);
            save_to_JSON();
        } catch (WADNotFoundException& w) {
            error.setText("Unable to open WAD!");
            error.exec();
        }
    }
}

void MainWindow::on_tab2_bt_iwaddel_clicked() {
    int current_index = ui->tab2_table_iwads->currentIndex().row();

    if (current_index < 0 || current_index >= m_iwad_model.rowCount()) return;

    QString iwad_name = m_iwad_model.get_at(current_index, 0).toString();

    QMessageBox warning;
    warning.setText("Are you sure you want to remove " + iwad_name +
                    " from your IWADs list?");
    warning.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    warning.setIcon(QMessageBox::Warning);

    int result = warning.exec();

    if (result == QMessageBox::Ok) m_iwad_model.remove(current_index);
}

void MainWindow::on_tab2_bt_iwadup_clicked() {
    int current_index = ui->tab2_table_iwads->currentIndex().row();

    if (current_index < 1 || current_index >= m_iwad_model.rowCount()) return;

    m_iwad_model.move_up(current_index);
}

void MainWindow::on_tab2_bt_iwaddown_clicked() {
    int current_index = ui->tab2_table_iwads->currentIndex().row();

    if (current_index < 0 || current_index >= m_iwad_model.rowCount() - 1) return;

    m_iwad_model.move_down(current_index);
}
