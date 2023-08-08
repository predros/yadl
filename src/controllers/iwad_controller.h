#ifndef IWADCONTROLLER_H
#define IWADCONTROLLER_H

#include "../models/iwad.h"
#include <QAbstractTableModel>
#include <QJsonArray>

class IWADController : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit IWADController(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QVariant get_at(int row, int column) const;
    QVariant get_at_id(int id, int column) const;

    QList<QString> get_maps(int index) const;
    int index_from_id(int id) const;

    void populate(const QJsonArray& array);

    void add(const QString& name, const QString& path,
             const QString& params);
    void edit(int index, const QString& name, const QString& path,
              const QString& params);
    void remove(int index);
    void move_up(int index);
    void move_down(int index);

    QJsonArray to_json_array() const;

protected:
    QList<IWAD> m_data;
    int next_id() const;

};

#endif // IWADCONTROLLER_H
