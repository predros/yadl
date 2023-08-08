#include "views/mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

void MainWindow::load_preset(int index) {
    if (index < 0 || index > m_preset_controller.rowCount() - 1)
        return;

    int port_id = m_preset_controller.get_at(index, 3).toInt();
    int iwad_id = m_preset_controller.get_at(index, 4).toInt();
    int skill = m_preset_controller.get_at(index, 5).toInt();
    int complevel = m_preset_controller.get_at(index, 6).toInt();
    bool fast = m_preset_controller.get_at(index, 7).toBool();
    bool coop = m_preset_controller.get_at(index, 8).toBool();
    QString params = m_preset_controller.get_at(index, 9).toString();
    QList<QString> mods = m_preset_controller.get_at(index, 10).toStringList();

    int port_index = m_sourceport_controller.index_from_id(port_id);
    int iwad_index = m_iwad_controller.index_from_id(iwad_id);

    ui->tab1_cb_port->setCurrentIndex(port_index);
    ui->tab1_cb_iwad->setCurrentIndex(iwad_index);
    ui->tab1_cb_skill->setCurrentIndex(skill);
    ui->tab1_cb_complevel->setCurrentIndex(complevel);
    ui->tab1_ch_fast->setChecked(fast);
    ui->tab1_ch_coop->setChecked(coop);
    ui->tab1_entry_params->setText(params);

    m_modfile_controller.populate(mods);
    m_map_controller.populate(iwad_index);

    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::delete_preset(int index) {
    if (index < 0 || index > m_preset_controller.rowCount() - 1) return;

    QString preset_name = m_sourceport_controller.get_at(index, 0).toString();

    QMessageBox warning;
    warning.setText("Are you sure you want to remove " + preset_name +
                    " from your presets list?");
    warning.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    warning.setIcon(QMessageBox::Warning);

    int result = warning.exec();

    if (result == QMessageBox::Ok) {
        m_preset_controller.remove(index);
        save_presets();
    }
}

void MainWindow::move_preset_up(int index) {
    if (index < 1 || index > m_preset_controller.rowCount() - 1) return;

    m_preset_controller.move_up(index);
    save_presets();
}

void MainWindow::move_preset_down(int index) {
    if (index < 0 || index > m_preset_controller.rowCount() - 2) return;

    m_preset_controller.move_down(index);
    save_presets();
}

void MainWindow::filter_preset(const QString& filter) {
    if (filter.isEmpty())
        m_preset_proxy.setFilterRegularExpression(QRegularExpression());
    else
        m_preset_proxy.setFilterRegularExpression(QRegularExpression(filter,
                QRegularExpression::CaseInsensitiveOption));

    m_preset_proxy.setFilterKeyColumn(0);
}
