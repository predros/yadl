#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

void MainWindow::on_tab3_bt_load_clicked() {
    int current_preset = ui->tab3_table_presets->currentIndex().row();

    if (current_preset < 0 || current_preset >= m_preset_model.rowCount())
        return;

    int port_id = m_preset_model.get_at(current_preset, 3).toInt();
    int iwad_id = m_preset_model.get_at(current_preset, 4).toInt();
    int skill = m_preset_model.get_at(current_preset, 5).toInt();
    int complevel = m_preset_model.get_at(current_preset, 6).toInt();
    bool fast = m_preset_model.get_at(current_preset, 7).toBool();
    bool coop = m_preset_model.get_at(current_preset, 8).toBool();
    QString params = m_preset_model.get_at(current_preset, 9).toString();
    QList<QString> mods = m_preset_model.get_at(current_preset, 10).toStringList();

    int port_index = m_sourceport_model.index_from_id(port_id);
    int iwad_index = m_iwad_model.index_from_id(iwad_id);

    ui->tab1_cb_port->setCurrentIndex(port_index);
    ui->tab1_cb_iwad->setCurrentIndex(iwad_index);
    ui->tab1_cb_skill->setCurrentIndex(skill);
    ui->tab1_cb_complevel->setCurrentIndex(complevel);
    ui->tab1_ch_fast->setChecked(fast);
    ui->tab1_ch_coop->setChecked(coop);
    ui->tab1_entry_params->setText(params);

    m_modfile_model.populate(mods);

    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_tab3_bt_remove_clicked() {
    int current_index = ui->tab3_table_presets->currentIndex().row();

    if (current_index < 0 || current_index >= m_preset_model.rowCount()) return;

    QString preset_name = m_sourceport_model.get_at(current_index, 0).toString();

    QMessageBox warning;
    warning.setText("Are you sure you want to remove " + preset_name +
                    " from your presets list?");
    warning.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    warning.setIcon(QMessageBox::Warning);

    int result = warning.exec();

    if (result == QMessageBox::Ok) m_preset_model.remove(current_index);

}

void MainWindow::on_tab3_bt_up_clicked() {
    int current_index = ui->tab3_table_presets->currentIndex().row();

    if (current_index < 1 || current_index >= m_preset_model.rowCount()) return;

    m_preset_model.move_up(current_index);
}

void MainWindow::on_tab3_bt_down_clicked() {
    int current_index = ui->tab3_table_presets->currentIndex().row();

    if (current_index < 1 || current_index >= m_preset_model.rowCount()) return;

    m_preset_model.move_up(current_index);
}
