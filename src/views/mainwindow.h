#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "../models/sourceport_model.h"
#include "../models/iwad_model.h"
#include "../models/modfile_model.h"
#include "../models/map_model.h"
#include "../models/preset_model.h"

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

    void save_configs();

    void save_presets();

    void load_configs();

    void load_presets();

protected:
    Ui::MainWindow *ui;

    SourcePortModel m_sourceport_model;

    IWADModel m_iwad_model;

    ModFileModel m_modfile_model;

    MapModel m_map_model;

    PresetModel m_preset_model;

    QSortFilterProxyModel m_preset_proxy;

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
