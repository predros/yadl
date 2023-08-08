#ifndef MODFILECONTROLLER_H
#define MODFILECONTROLLER_H

#include "../models/modfile.h"
#include <QAbstractListModel>

class ModFileController : public QAbstractListModel {
    Q_OBJECT
public:
    explicit ModFileController(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant get_at(int row, int column) const;
    QList<QString> get_maps(int index) const;

    void populate(const QList<QString>& mods);
    void populate(const QJsonArray& mods);

    void clear();
    void add(const QString& path);
    void remove(int index);
    void move_up(int index);
    void move_down(int index);
protected:
    QList<ModFile> m_data;

};

#endif // MODFILECONTROLLER_H
