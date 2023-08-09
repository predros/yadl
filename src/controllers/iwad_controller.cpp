#include "controllers/iwad_controller.h"

IWADController::IWADController(QObject *parent)
    : QAbstractTableModel{parent} {
}

int IWADController::rowCount(const QModelIndex&) const {
    return m_data.size();
}

int IWADController::columnCount(const QModelIndex&) const {
    return 3;
}

QVariant IWADController::data(const QModelIndex& index, int role) const {
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

QVariant IWADController::headerData(int section, Qt::Orientation orientation,
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

QVariant IWADController::get_at(int row, int column) const {
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

QVariant IWADController::get_at_id(int id, int column) const {
    IWAD const *result = nullptr;

    for (auto& iwad : m_data)
        if (iwad.id() == id) result = &iwad;

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

QList<QString> IWADController::get_maps(int index) const {
    if (index < 0 || index > rowCount() - 1) return QList<QString>();

    return m_data[index].maps();
}

int IWADController::index_from_id(int id) const {
    for (int i = 0; i < m_data.size(); i++) {
        if (m_data[i].id() == id) return i;
    }

    return -1;
}

int IWADController::next_id() const {
    if (m_data.size() == 0) return 0;

    int result = 0;

    for (auto& iwad : m_data) {
        result = std::max(result, iwad.id());
    }

    return result + 1;
}

void IWADController::populate(const QJsonArray& array) {
    beginResetModel();
    m_data.clear();

    for (auto& json : array) {
        try {
            m_data.append(IWAD(json.toObject()));
        } catch (std::exception& e) {
            continue;
        }
    }

    endResetModel();
}

void IWADController::add(const QString& name, const QString& path,
                         const QString& params) {
    beginResetModel();
    int id = next_id();
    IWAD iwad(id, name, path, params);
    m_data.append(iwad);
    endResetModel();
}

void IWADController::edit(int index, const QString& name, const QString& path,
                          const QString& params) {
    if (index < 0 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data[index].set_file_path(path);
    m_data[index].set_name(name);
    m_data[index].set_params(params);
    endResetModel();
}

void IWADController::remove(int index) {
    if (index < 0 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data.removeAt(index);
    endResetModel();
}

void IWADController::move_up(int index) {
    if (index < 1 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data.move(index, index - 1);
    endResetModel();
}

void IWADController::move_down(int index) {
    if (index < 0 || index > m_data.size() - 2) return;

    beginResetModel();
    m_data.move(index, index + 1);
    endResetModel();
}

QJsonArray IWADController::to_json_array() const {
    QJsonArray array;

    for (auto& iwad : m_data)
        array.append(iwad.to_json());

    return array;
}
