#include "views/mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
    , m_map_controller(m_iwad_controller, m_modfile_controller),
      m_preset_controller(m_sourceport_controller,
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

void MainWindow::closeEvent(QCloseEvent *e) {
    save_configs();
    QMainWindow::closeEvent(e);
}

void MainWindow::launch(QString port_path, SourcePortType port_type, QString iwad_path,
                        int skill, int complevel,
                        QString map, QList<QString> mods, QString params, bool fast, bool coop) const {

    QFileInfo file_checker(port_path);
    QProcess run_process;
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

