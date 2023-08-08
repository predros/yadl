#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "controllers/sourceport_controller.h"
#include "controllers/iwad_controller.h"
#include "controllers/modfile_controller.h"
#include "controllers/map_controller.h"
#include "controllers/preset_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void save_configs() const;

    void save_presets() const;

    void load_configs();

    void load_presets();

    void launch(QString port_path, SourcePortType port_type, QString iwad_path, int skill,
                int complevel, QString map,
                QList<QString> mods, QString params = "", bool fast = false, bool coop = false) const;

protected:
    Ui::MainWindow *ui;

    SourcePortController m_sourceport_controller;
    IWADController m_iwad_controller;
    ModFileController m_modfile_controller;
    MapController m_map_controller;
    PresetController m_preset_controller;
    QSortFilterProxyModel m_preset_proxy;

    void add_modfile();
    void delete_modfile(int index);
    void move_modfile_up(int index);
    void move_modfile_down(int index);

    void add_port();
    void edit_port(int index);
    void delete_port(int index);
    void move_port_up(int index);
    void move_port_down(int index);

    void add_iwad();
    void edit_iwad(int index);
    void delete_iwad(int index);
    void move_iwad_up(int index);
    void move_iwad_down(int index);

    void load_preset(int index);
    void add_or_edit_preset();
    void delete_preset(int index);
    void move_preset_up(int index);
    void move_preset_down(int index);
    void filter_preset(const QString& filter);

    void closeEvent(QCloseEvent *event) override;


private slots:
    void on_tab1_bt_add_clicked();
    void on_tab1_bt_remove_clicked();
    void on_tab1_bt_up_clicked();
    void on_tab1_bt_down_clicked();
    void on_tab1_cb_iwad_currentIndexChanged(int index);
    void on_tab1_list_files_indexesMoved(const QModelIndexList& indexes);
    void on_tab1_bt_launch_clicked();
    void on_tab1_bt_preset_clicked();

    void on_tab2_bt_portadd_clicked();
    void on_tab2_bt_portedit_clicked();
    void on_tab2_bt_portdel_clicked();
    void on_tab2_bt_portup_clicked();
    void on_tab2_bt_portdown_clicked();
    void on_tab2_bt_iwadadd_clicked();
    void on_tab2_bt_iwadedit_clicked();
    void on_tab2_bt_iwaddel_clicked();
    void on_tab2_bt_iwadup_clicked();
    void on_tab2_bt_iwaddown_clicked();

    void on_tab3_bt_load_clicked();
    void on_tab3_bt_remove_clicked();
    void on_tab3_bt_up_clicked();
    void on_tab3_bt_down_clicked();
    void on_tab3_entry_filter_textChanged(const QString& arg1);
};
#endif // MAINWINDOW_H
