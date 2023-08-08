#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

void MainWindow::on_tab2_bt_portadd_clicked() {
    add_port();
}

void MainWindow::on_tab2_bt_portedit_clicked() {
    int current_index = ui->tab2_table_ports->currentIndex().row();
    edit_port(current_index);
}

void MainWindow::on_tab2_bt_portdel_clicked() {
    int current_index = ui->tab2_table_ports->currentIndex().row();
    delete_port(current_index);
}

void MainWindow::on_tab2_bt_portup_clicked() {
    int current_index = ui->tab2_table_ports->currentIndex().row();
    move_port_up(current_index);
}

void MainWindow::on_tab2_bt_portdown_clicked() {
    int current_index = ui->tab2_table_ports->currentIndex().row();
    move_port_down(current_index);
}

void MainWindow::on_tab2_bt_iwadadd_clicked() {
    add_iwad();
}

void MainWindow::on_tab2_bt_iwadedit_clicked() {
    int current_index = ui->tab2_table_iwads->currentIndex().row();
    edit_iwad(current_index);
}

void MainWindow::on_tab2_bt_iwaddel_clicked() {
    int current_index = ui->tab2_table_iwads->currentIndex().row();
    delete_iwad(current_index);
}

void MainWindow::on_tab2_bt_iwadup_clicked() {
    int current_index = ui->tab2_table_iwads->currentIndex().row();
    move_iwad_up(current_index);
}

void MainWindow::on_tab2_bt_iwaddown_clicked() {
    int current_index = ui->tab2_table_iwads->currentIndex().row();
    move_iwad_down(current_index);
}
