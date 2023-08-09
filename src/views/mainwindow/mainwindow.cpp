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
    run_process.waitForFinished(-1);

    QString error(run_process.readAllStandardError());

    // Woof has a really annoying habit of outputting everything
    // to stderr instead of stdoutput
    if (port_type == SOURCEPORT_WOOF) {
        // Actual breaking errors (I_Error)
        static QStringList valid_errors = {
            "IWAD not found",
            "Unknown or invalid IWAD file",
            "Unknown game version",
            "Invalid parameter",
            "No parameter for",
            "Bad savegame",
            "Couldn't read file",
            "Error: couldn't open",

            "CheckIWAD: failed to read IWAD",
            "CheckIWAD: failed to read header",
            "CheckIWAD: IWAD tag not present",
            "CheckIWAD: failed to read directory",

            "check your dehacked",
            "Check your dehacked",
            "Error reading lump directory from",
            "Disconnected from server in drone mode",
            "Lost connection to server",
            "Netgame startup aborted",
            "D_StartNetGame: invalid ticdup value",
            "No server found on local LAN",
            "Unable to resolve",
            "D_InitNetGame: Failed to connect to",
            "TryRunTics: lowtic < gametic",
            "gametic>lowtic",
            "D_AddZipFile: Failed to open",
            "No such response file!",
            "Cannot find .deh or .bex file named",
            "'BETAGRPH.WAD' is required for beta emulation!",
            "You cannot -file with the shareware version",
            "This is not the registered version",
            "Not enough players to continue the demo",
            "G_DoPlayDemo: Unknown demo format",
            "consistency failure",
            "G_CheckSpot: unexpected angle",
            "G_ReloadDefaults: Beta emulation requires complevel MBF",
            "G_ReloadDefaults: Helper dogs require complevel MBF or MBF21",
            "mbf21_WriteOptions: MBF21_GAME_OPTION_SIZE is too small",
            "G_WriteOptions: GAME_OPTION_SIZE is too small",
            "Encountered unknown mbf21 compatibility options",
            "The -beta option is required to play",
            "Error recording demo",
            "I_UpdateSoundParams: channel out of range",
            "I_StopSound: channel out of range",
            "I_SoundIsPlaying: channel out of range",
            "I_SoundID: channel out of range",
            "MidiPlayerFallback: No music module could be initialized",
            "I_Realloc: failed on reallocation",
            "Failed to get renderer output size",
            "Could not get display mode for video display",
            "Error creating window for video startup",
            "Error creating window for video startup",
            "Error creating renderer for screen window",
            "Failed to initialize video",
            "Failed to allocate new string",
            "Could not find config variable",
            "Could not write defaults to",
            "Failed to duplicate string",
            "Failed to open",
            "NET_AddModule: No more modules for context",
            "NET_CL_InitServer: attempted to initialize client pipe end as a server",
            "NET_SV_InitClient: attempted to initialize server pipe end as a client",
            "NET_QueryAddress: Host",
            "No response from",
            "NET_SDL_FreeAddress: Attempted to remove an unused address",
            "NET_SDL_InitClient: Unable to open a socket",
            "NET_SDL_InitServer: Unable to bind to port",
            "NET_SDL_SendPacket: Error transmitting packet",
            "NET_SDL_RecvPacket: Error receiving packet",
            "Wanted to send",
            "NET_WriteProtocol: protocol",
            "Weird actor->movedir",
            "P_SetupLevel: Hexen map format not supported in",
            "P_LoadNodes: Error during ZDBSP nodes decompression initialization",
            "P_LoadNodes: Error during ZDBSP nodes decompression",
            "P_LoadNodes: Error during ZDBSP nodes decompression shut-down",
            "P_LoadNodes: No subsectors in map",
            "P_LoadNodes: Incorrect number of segs in ZDBSP nodes",
            "P_GiveAmmo: bad type",
            "PTR_SlideTraverse: not a line",
            "P_MapStart: tmthing set",
            "Unknown tclass",
            "P_UnArchiveSpecials: Pusher thinker without source in sector",
            "P_UnarchiveSpecials:Unknown tclass",
            "P_CrossSubsector: ss",
            "P_InitPicAnims: bad cycle from",
            "P_StartButton: no button slots left",
            "R_Subsector: ss",
            "R_InitTextures: bad texture directory",
            "R_DrawColumn: ",
            "R_DrawSkyColumn: ",
            "R_DrawFuzzColumn: ",
            "R_MapPlane: ",
            "Bad R_RenderWallRange",
            "R_InstallSpriteLump: Bad frame characters in lump",
            "R_DrawSpriteRange: bad texturecolumn",
            "invalid sprite number",
            "invalid frame",
            "Bad sfx",
            "Attempt to set music volume at",
            "Attempt to set sfx volume at",
            "Bad music number",
            "W_FileLength: failure in fstat",
            "W_InitFiles: no files found",
            "Couldn't allocate lumpcache",
            "Cannot open internal lumps wad",
            "owner is required for purgable blocks",
            "Z_Malloc: Failure trying to allocate",
            "freed a pointer without ZONEID",
        };

        static QList<QRegularExpression> valid_regex = {
            QRegularExpression("IWAD file .* not found"),
            QRegularExpression("Wad file .* doesn't have IWAD or PWAD id"),
            QRegularExpression("Only .* deathmatch spots, .* required"),
            QRegularExpression("The command line parameter .* was "
                               "specified to a dedicated server."),
            QRegularExpression("P_LoadSegs: linedef .* for seg .*"),
            QRegularExpression("Line .* is missing a tag"),
            QRegularExpression("[0-9]* errors"),
            QRegularExpression("R_InitSprites: Sprite .* frame .* "
                               "is missing rotations"),
            QRegularExpression("handle .* out of range"),
            QRegularExpression("Bad V_.*"),
            QRegularExpression("W_GetNumForName: .* not found"),
            QRegularExpression(".* >= numlumps"),
            QRegularExpression("Z_FreeTag: Tag .* does not exist"),


        };

        QStringList errors = error.split('\n');

        auto iter = errors.constEnd();
        bool found_error = false;

        while (iter != errors.constBegin() && !found_error) {
            iter--;

            for (auto& regex : valid_regex) {
                if (regex.match(*iter).hasMatch()) {
                    throw *iter;
                }
            }

            for (auto& string : valid_errors) {
                if (iter->contains(string)) {
                    throw *iter;
                }
            }
        }
    } else if (!error.trimmed().isEmpty())
        throw error.remove('\n');
}

