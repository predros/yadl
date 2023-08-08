#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../exceptions.h"
#include <QFile>
#include <QJsonDocument>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
    , m_map_controller(m_iwad_controller, m_modfile_controller), m_preset_controller(m_sourceport_controller,
            m_iwad_controller) {
    ui->setupUi(this);

    ui->tab3_table_presets->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_preset_proxy.setSourceModel(&m_preset_controller);
    ui->tab3_table_presets->setModel(&m_preset_proxy);

    ui->tab2_table_ports->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tab2_table_iwads->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tab2_table_ports->setModel(&m_sourceport_controller);
    ui->tab2_table_iwads->setModel(&m_iwad_controller);

    ui->tab1_list_files->setModel(&m_modfile_controller);
    ui->tab1_cb_port->setModel(&m_sourceport_controller);
    ui->tab1_cb_iwad->setModel(&m_iwad_controller);
    ui->tab1_cb_map->setModel(&m_map_controller);

    load_configs();
    load_presets();

    m_map_controller.populate(ui->tab1_cb_iwad->currentIndex());
}

MainWindow::~MainWindow() {
    delete ui;
}

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

void MainWindow::launch(QString port_path, SourcePortType port_type, QString iwad_path,
                        int skill, int complevel,
                        QString map, QList<QString> mods, QString params, bool fast, bool coop) const {

    static QFileInfo file_checker(port_path);
    static QProcess run_process;
    QStringList args_list;

    if (!file_checker.exists()) {
        throw QString("Source port could not be located!");
        return;
    }

    QString port_command = port_path;

    if (!file_checker.isExecutable()) {
#ifdef __unix__

        if (file_checker.suffix() == "exe") {
            args_list.append("wine");
            run_process.start("which", args_list);
            run_process.waitForFinished();
            QString output(run_process.readAllStandardOutput());
            args_list.clear();

            if (output.trimmed().isEmpty()) {
                throw QString("Source port is a Windows executable, but Wine could not be found!");
            } else {
                port_command = "wine";
                args_list.append(port_path);
            }
        }

#else
        throw QString("Source port must be an executable!");
        return;
#endif
    }

    file_checker = QFileInfo(iwad_path);

    if (!file_checker.exists()) {
        throw QString("Could not locate IWAD " + file_checker.fileName() + "!");
        return;
    }

    args_list.append("-iwad");
    args_list.append(iwad_path);

    if (complevel > 0 && complevel < 22) {
        args_list.append("-complevel");
        args_list.append(QString::number(complevel));
    }

    if (fast) args_list.append("-fast");

    if (coop) args_list.append("-net-solo");

    if (mods.size() > 0) {
        args_list.append("-file");

        for (int i = 0; i < mods.size(); i++) {
            file_checker = QFileInfo(mods[i]);

            if (!file_checker.exists()) {
                throw QString("Could not locate " + file_checker.fileName() + "!");
            }

            args_list.append(mods[i]);
        }
    }

    if (!map.trimmed().isEmpty()) {
        if (skill > 0 && skill < 6) {
            args_list.append("-skill");
            args_list.append(QString::number(skill));
        }

        if (port_type == SOURCEPORT_ZDOOM) {
            args_list.append("+map");
            args_list.append(map);
        } else {
            static QRegularExpression doom("E[0-9]M[0-9]");
            static QRegularExpression doom2("MAP[0-9]{2}");
            static QRegularExpression level("LEVEL[0-9]{2}");

            if (doom.match(map).hasMatch()) {
                args_list.append("-warp");
                args_list.append(map[1] + QString(" ") + map[3]);
            } else if (doom2.match(map).hasMatch()) {
                args_list.append("-warp");
                args_list.append(QString(map[3]) + QString(map[4]));
            } else if (level.match(map).hasMatch()) {
                args_list.append("-warp");
                args_list.append(QString(map[5]) + QString(map[6]));
            } else {
                args_list.append("+map");
                args_list.append(map);
            }
        }
    }

    QStringList custom_params = params.split(" ");

    if (custom_params.size() > 0 && custom_params[0] != "") {
        for (auto& p : custom_params)
            args_list.append(p);
    }

    run_process.start(port_command, args_list);
    run_process.waitForFinished();

    QString error(run_process.readAllStandardError());

    if (!error.trimmed().isEmpty())
        throw error.remove('\n');
}


void MainWindow::closeEvent(QCloseEvent *e) {
    save_configs();
    QMainWindow::closeEvent(e);
}

void MainWindow::on_tab3_entry_filter_textChanged(const QString& new_text) {
    QString trim = new_text.trimmed();

    if (trim.isEmpty())
        m_preset_proxy.setFilterRegularExpression(QRegularExpression());
    else
        m_preset_proxy.setFilterRegularExpression(QRegularExpression(trim,
                QRegularExpression::CaseInsensitiveOption));

    m_preset_proxy.setFilterKeyColumn(0);
}
