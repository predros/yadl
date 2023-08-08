#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QRegularExpression>
#include <QInputDialog>

void MainWindow::on_tab1_bt_add_clicked() {
    add_modfile();
}

void MainWindow::on_tab1_bt_remove_clicked() {
    int current_index = ui->tab1_list_files->currentIndex().row();
    delete_modfile(current_index);
}

void MainWindow::on_tab1_bt_up_clicked() {
    int current_index = ui->tab1_list_files->currentIndex().row();
    move_modfile_up(current_index);
}

void MainWindow::on_tab1_bt_down_clicked() {
    int current_index = ui->tab1_list_files->currentIndex().row();
    move_modfile_down(current_index);
}

void MainWindow::on_tab1_cb_iwad_currentIndexChanged(int) {
    m_map_controller.populate(ui->tab1_cb_iwad->currentIndex());
}

void MainWindow::on_tab1_list_files_indexesMoved(const QModelIndexList&) {
    m_map_controller.populate(ui->tab1_cb_iwad->currentIndex());
}

void MainWindow::on_tab1_bt_launch_clicked() {
    static QList<int> complevels_list = {-1, 2, 3, 4, 9, 11, 21};

    int complevel_index = ui->tab1_cb_complevel->currentIndex();
    int port_index = ui->tab1_cb_port->currentIndex();
    int iwad_index = ui->tab1_cb_iwad->currentIndex();
    int map_index = ui->tab1_cb_map->currentIndex();

    QMessageBox error(this);
    error.setIcon(QMessageBox::Warning);
    error.setStandardButtons(QMessageBox::Ok);

    if (port_index == -1) {
        error.setText("No source port selected!");
        error.exec();
        return;
    }

    if (iwad_index == -1) {
        error.setText("No IWAD selected!");
        error.exec();
        return;
    }

    QString port_path = m_sourceport_controller.get_at(port_index, 1).toString();
    SourcePortType port_type = static_cast<SourcePortType>(m_sourceport_controller.get_at(
                                   port_index, 4).toString().toInt());
    QString port_params = m_sourceport_controller.get_at(port_index, 2).toString();

    QString iwad_path = m_iwad_controller.get_at(iwad_index, 1).toString();
    QString iwad_params = m_iwad_controller.get_at(iwad_index, 2).toString();

    QString map_name = map_index > 0 ? m_map_controller.get_at(map_index).toString() : "";

    int skill = ui->tab1_cb_skill->currentIndex();
    int complevel = complevels_list[complevel_index];

    bool fast_monsters = ui->tab1_ch_fast->isChecked();
    bool coop_monsters = ui->tab1_ch_coop->isChecked();

    QString params = ui->tab1_entry_params->text();
    QString total_params = params + port_params + iwad_params;

    QList<QString> mods;

    for (int i = 0; i < m_modfile_controller.rowCount(); i++) {
        QString mod_path = m_modfile_controller.get_at(i, 1).toString();
        mods.append(mod_path);
    }

    try {
        launch(port_path, port_type, iwad_path, skill, complevel, map_name, mods, total_params,
               fast_monsters, coop_monsters);
    } catch (QString& e) {
        error.setText(e);
        error.exec();
    }
}

void MainWindow::on_tab1_bt_preset_clicked() {
    add_or_edit_preset();
}
