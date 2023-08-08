#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QInputDialog>

void MainWindow::add_modfile() {
    QList<QString> files = QFileDialog::getOpenFileNames(this, "Open mod files",
                           QDir::currentPath(), "Doom mod files (*.wad *.WAD *.pk3 *.PK3 *.zip *.ZIP)");

    for (auto& file : files) {
        m_modfile_controller.add(file);
    }

    auto last_index = m_modfile_controller.index(m_modfile_controller.rowCount() - 1, 0);

    ui->tab1_list_files->setCurrentIndex(last_index);
    m_map_controller.populate(ui->tab1_cb_iwad->currentIndex());
}

void MainWindow::delete_modfile(int index) {
    if (index < 0 || index > m_modfile_controller.rowCount() - 1) return;

    m_modfile_controller.remove(index);
    ui->tab1_list_files->setCurrentIndex(m_modfile_controller.index(index - 1, 0));
    m_map_controller.populate(ui->tab1_cb_iwad->currentIndex());
}

void MainWindow::move_modfile_up(int index) {
    if (index < 1 || index > m_modfile_controller.rowCount() - 1) return;

    m_modfile_controller.move_up(index);
    ui->tab1_list_files->setCurrentIndex(m_modfile_controller.index(index - 1, 0));
    m_map_controller.populate(ui->tab1_cb_iwad->currentIndex());
}

void MainWindow::move_modfile_down(int index) {
    if (index < 0 || index > m_modfile_controller.rowCount() - 2) return;

    m_modfile_controller.move_down(index);
    ui->tab1_list_files->setCurrentIndex(m_modfile_controller.index(index + 1, 0));
    m_map_controller.populate(ui->tab1_cb_iwad->currentIndex());
}

void MainWindow::add_or_edit_preset() {
    bool ok;
    QString preset_name = QInputDialog::getText(this, tr("Save preset"), tr("Preset name"),
                          QLineEdit::Normal, tr(""), &ok);

    if (ok && !preset_name.isEmpty()) {
        int iwad_index = ui->tab1_cb_iwad->currentIndex();
        int port_index = ui->tab1_cb_port->currentIndex();
        int skill_index = ui->tab1_cb_skill->currentIndex();
        int complevel_index = ui->tab1_cb_complevel->currentIndex();
        bool fast = ui->tab1_ch_fast->isChecked();
        bool coop = ui->tab1_ch_coop->isChecked();
        QString params = ui->tab1_entry_params->text();

        int iwad_id = iwad_index < 0 ? -1 : m_iwad_controller.get_at(iwad_index, 3).toInt();
        int port_id = port_index < 0 ? -1 : m_sourceport_controller.get_at(port_index, 3).toInt();

        QList<QString> mods;

        for (int i = 0; i < m_modfile_controller.rowCount(); i++)
            mods.append(m_modfile_controller.get_at(i, 1).toString());

        m_preset_controller.add_or_edit(preset_name, port_id, iwad_id, skill_index,
                                        complevel_index,
                                        fast, coop, params, mods);
        save_presets();
    }
}
