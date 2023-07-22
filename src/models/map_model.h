#ifndef MAPMODEL_H
#define MAPMODEL_H

#include "modfile_model.h"
#include "iwad_model.h"
#include <QAbstractListModel>

class MapModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit MapModel(const IWADModel& iwad_model, const ModFileModel& modfile_model,
                      QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant get_at(int row) const;

    void populate(int iwad_index);
protected:
    QList<QString> m_data;
    const IWADModel& m_iwad_model;
    const ModFileModel& m_modfile_model;

};

#endif // MAPMODEL_H
