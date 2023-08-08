#ifndef PRESETCONTROLLER_H
#define PRESETCONTROLLER_H

#include "../models/preset.h"
#include <QAbstractTableModel>

class SourcePortController;
class IWADController;

class PresetController : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit PresetController(SourcePortController& port_controller,
                              IWADController& iwad_controller,
                              QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QVariant get_at(int row, int column) const;
    int index_from_id(int id) const;

    void populate(const QJsonArray& array);

    void add_or_edit(const QString& name, int port_id, int iwad_id, int skill, int complevel,
                     bool fast, bool coop, const QString& params, const QList<QString>& mods);
    void remove(int index);
    void move_up(int index);
    void move_down(int index);

    QJsonArray to_json_array() const;

protected:
    QList<Preset> m_data;
    SourcePortController& m_sourceport_controller;
    IWADController& m_iwad_controller;

    int next_id() const;

};

#endif // PRESETCONTROLLER_H
