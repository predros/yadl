#include "views/mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

void MainWindow::on_tab3_bt_load_clicked() {
    int current_index = ui->tab3_table_presets->currentIndex().row();
    load_preset(current_index);
}

void MainWindow::on_tab3_bt_remove_clicked() {
    int current_index = ui->tab3_table_presets->currentIndex().row();
    delete_preset(current_index);
}

void MainWindow::on_tab3_bt_up_clicked() {
    int current_index = ui->tab3_table_presets->currentIndex().row();
    move_preset_up(current_index);
}

void MainWindow::on_tab3_bt_down_clicked() {
    int current_index = ui->tab3_table_presets->currentIndex().row();
    move_preset_down(current_index);
}

void MainWindow::on_tab3_entry_filter_textChanged(const QString& new_text) {
    QString trim = new_text.trimmed();
    filter_preset(trim);
}
