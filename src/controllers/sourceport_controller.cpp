#include "sourceport_controller.h"
#include <QFont>

SourcePortController::SourcePortController(QObject *parent)
    : QAbstractTableModel{parent} {

}

int SourcePortController::rowCount(const QModelIndex&) const {
    return m_data.size();
}

int SourcePortController::columnCount(const QModelIndex&) const {
    return 3;
}

QVariant SourcePortController::data(const QModelIndex& index, int role) const {
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

QVariant SourcePortController::headerData(int section, Qt::Orientation orientation,
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

QVariant SourcePortController::get_at(int row, int column) const {
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

        case 4:
            return m_data[row].sourceport_type();

    }

    return QVariant();
}

QVariant SourcePortController::get_at_id(int id, int column) const {
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

int SourcePortController::index_from_id(int id) const {
    for (int i = 0; i < m_data.size(); i++) {
        if (m_data[i].id() == id) return i;
    }

    return -1;
}

int SourcePortController::next_id() const {
    int result = 0;

    for (auto& port : m_data)
        result = std::max(result, port.id());

    return result + 1;
}

void SourcePortController::populate(const QJsonArray& array) {
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

void SourcePortController::add(const QString& name, const QString& path,
                          const QString& params) {
    beginResetModel();
    int id = next_id();
    SourcePort sp(id, name, path, params);
    m_data.append(sp);
    endResetModel();
}

void SourcePortController::edit(int index, const QString& name, const QString& path,
                           const QString& params) {
    if (index < 0 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data[index].set_file_path(path);
    m_data[index].set_name(name);
    m_data[index].set_params(params);
    endResetModel();
}

void SourcePortController::remove(int index) {
    if (index < 0 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data.removeAt(index);
    endResetModel();
}

void SourcePortController::move_up(int index) {
    if (index < 1 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data.move(index, index - 1);
    endResetModel();
}

void SourcePortController::move_down(int index) {
    if (index < 0 || index > m_data.size() - 2) return;

    beginResetModel();
    m_data.move(index, index + 1);
    endResetModel();
}

QJsonArray SourcePortController::to_json_array() const {
    QJsonArray array;

    for (auto& sp : m_data)
        array.append(sp.to_json());

    return array;
}
