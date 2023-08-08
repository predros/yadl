#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>

void MainWindow::save_configs() const {
    QFile save_file(QStringLiteral("yadlconfig"));

    if (!save_file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open configuration file.");
        return;
    }

    QJsonObject current;
    QString current_iwad = m_iwad_controller.get_at(ui->tab1_cb_iwad->currentIndex(),
                           3).toString();
    QString current_port = m_sourceport_controller.get_at(ui->tab1_cb_port->currentIndex(),
                           3).toString();

    current["iwad"] = current_iwad;
    current["port"] = current_port;
    current["map"] = QString::number(ui->tab1_cb_map->currentIndex());
    current["skill"] = QString::number(ui->tab1_cb_skill->currentIndex());
    current["complevel"] = QString::number(ui->tab1_cb_complevel->currentIndex());
    current["params"] = ui->tab1_entry_params->text();
    current["fast"] = ui->tab1_ch_fast->isChecked() ? "1" : "0";
    current["coop"] = ui->tab1_ch_coop->isChecked() ? "1" : "0";

    QJsonArray modfiles;

    for (int i = 0; i < m_modfile_controller.rowCount(); i++) {
        QJsonObject mod;
        mod["path"] = m_modfile_controller.get_at(i, 1).toString();
        modfiles.append(mod);
    }

    current["mods"] = modfiles;

    QJsonObject json;
    json["sourceports"] = m_sourceport_controller.to_json_array();
    json["iwads"] = m_iwad_controller.to_json_array();
    json["current"] = current;

    save_file.write(QJsonDocument(json).toJson());
}

void MainWindow::save_presets() const {
    QFile save_file(QStringLiteral("yadlpresets"));

    if (!save_file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open presets file.");
        return;
    }

    QJsonObject json;
    json["presets"] = m_preset_controller.to_json_array();
    save_file.write(QJsonDocument(json).toJson());
}

void MainWindow::load_configs() {
    QFile open_file(QStringLiteral("yadlconfig"));

    if (!open_file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open configuration file.");
        return;
    }

    QByteArray data = open_file.readAll();
    QJsonDocument json(QJsonDocument::fromJson(data));

    QJsonValue sourceports = json["sourceports"];
    QJsonValue iwads = json["iwads"];
    QJsonValue current = json["current"];

    if (sourceports.isArray())
        m_sourceport_controller.populate(sourceports.toArray());

    if (iwads.isArray())
        m_iwad_controller.populate(iwads.toArray());

    if (current.isObject()) {
        int port_id = current["port"].toString().toInt();
        int iwad_id = current["iwad"].toString().toInt();

        int port_index = m_sourceport_controller.index_from_id(port_id);
        int iwad_index = m_iwad_controller.index_from_id(iwad_id);
        int map_index = current["map"].toString().toInt();
        int skill_index = current["skill"].toString().toInt();
        int complevel_index = current["complevel"].toString().toInt();
        QString params = current["params"].toString();
        bool fast = current["fast"].toString() == "1";
        bool coop = current["coop"].toString() == "1";

        ui->tab1_cb_port->setCurrentIndex(port_index);
        ui->tab1_cb_iwad->setCurrentIndex(iwad_index);
        ui->tab1_cb_skill->setCurrentIndex(skill_index);
        ui->tab1_cb_complevel->setCurrentIndex(complevel_index);
        ui->tab1_entry_params->setText(params);
        ui->tab1_ch_fast->setChecked(fast);
        ui->tab1_ch_coop->setChecked(coop);

        QJsonValue mods = current["mods"];

        if (mods.isArray())
            m_modfile_controller.populate(mods.toArray());

        ui->tab1_cb_map->setCurrentIndex(map_index);
    }
}

void MainWindow::load_presets() {
    QFile open_file(QStringLiteral("yadlpresets"));

    if (!open_file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open configuration file.");
        return;
    }

    QByteArray data = open_file.readAll();
    QJsonDocument json(QJsonDocument::fromJson(data));

    QJsonValue presets = json["presets"];

    if (presets.isArray())
        m_preset_controller.populate(presets.toArray());
}
