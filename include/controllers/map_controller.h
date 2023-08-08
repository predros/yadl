#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include "modfile_controller.h"
#include "iwad_controller.h"
#include <QAbstractListModel>

class MapController : public QAbstractListModel {
    Q_OBJECT
public:
    explicit MapController(const IWADController& iwad_controller,
                           const ModFileController& modfile_controller,
                           QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant get_at(int row) const;

    void populate(int iwad_index);
protected:
    QList<QString> m_data;
    const IWADController& m_iwad_controller;
    const ModFileController& m_modfile_controller;

};

#endif // MAPCONTROLLER_H
