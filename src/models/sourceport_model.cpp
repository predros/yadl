#include "sourceport_model.h"
#include <QFont>

SourcePortModel::SourcePortModel(QObject *parent)
    : QAbstractTableModel{parent} {

}

int SourcePortModel::rowCount(const QModelIndex&) const {
    return m_data.size();
}

int SourcePortModel::columnCount(const QModelIndex&) const {
    return 3;
}

QVariant SourcePortModel::data(const QModelIndex& index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return m_data[index.row()].name();

            case 1:
                return m_data[index.row()].file_path();

            case 2:
                return m_data[index.row()].params();

            case 3:
                return m_data[index.row()].id();
        }
    }

    return QVariant();
}

QVariant SourcePortModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return "Name";

            case 1:
                return "Path";

            case 2:
                return "Parameters";
        }
    }

    return QVariant();
}

QVariant SourcePortModel::get_at(int row, int column) {
    if (row < 0 || row > rowCount() - 1) return QVariant();

    switch (column) {
        case 0:
            return m_data[row].name();

        case 1:
            return m_data[row].file_path();

        case 2:
            return m_data[row].params();

        case 3:
            return m_data[row].id();

    }

    return QVariant();
}

QVariant SourcePortModel::get_at_id(int id, int column) const {
    SourcePort const *result = nullptr;

    for (auto& port : m_data)
        if (port.id() == id) result = &port;

    if (result == nullptr) return QVariant();

    switch (column) {
        case 0:
            return result->name();

        case 1:
            return result->file_path();

        case 2:
            return result->params();

        case 3:
            return result->id();
    }

    return QVariant();
}

int SourcePortModel::index_from_id(int id) const {
    for (int i = 0; i < m_data.size(); i++) {
        if (m_data[i].id() == id) return i;
    }

    return -1;
}

int SourcePortModel::next_id() const {
    int result = 0;

    for (auto& port : m_data)
        result = std::max(result, port.id());

    return result + 1;
}

void SourcePortModel::populate(const QJsonArray& array) {
    beginResetModel();
    m_data.clear();

    for (auto& json : array) {
        try {
            m_data.append(SourcePort(json.toObject()));
        } catch (std::exception&) {
            continue;
        }
    }

    endResetModel();
}

void SourcePortModel::add(const QString& name, const QString& path,
                          const QString& params) {
    beginResetModel();
    int id = next_id();
    SourcePort sp(id, name, path, params);
    m_data.append(sp);
    endResetModel();
}

void SourcePortModel::edit(int index, const QString& name, const QString& path,
                           const QString& params) {
    if (index < 0 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data[index].set_file_path(path);
    m_data[index].set_name(name);
    m_data[index].set_params(params);
    endResetModel();
}

void SourcePortModel::remove(int index) {
    if (index < 0 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data.removeAt(index);
    endResetModel();
}

void SourcePortModel::move_up(int index) {
    if (index < 1 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data.move(index, index - 1);
    endResetModel();
}

void SourcePortModel::move_down(int index) {
    if (index < 0 || index > m_data.size() - 2) return;

    beginResetModel();
    m_data.move(index, index + 1);
    endResetModel();
}

QJsonArray SourcePortModel::to_json_array() const {
    QJsonArray array;

    for (auto& sp : m_data)
        array.append(sp.to_json());

    return array;
}
