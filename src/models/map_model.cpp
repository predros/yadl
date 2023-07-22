#include "map_model.h"

MapModel::MapModel(const IWADModel& iwad_model, const ModFileModel& modfile_model,
                   QObject *parent)
    : QAbstractListModel{parent}, m_iwad_model(iwad_model),  m_modfile_model(modfile_model)
{}

int MapModel::rowCount(const QModelIndex&) const {
    return m_data.size();
}

int MapModel::columnCount(const QModelIndex&) const {
    return 1;
}

QVariant MapModel::data(const QModelIndex& index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return m_data[index.row()];
        }
    }

    return QVariant();
}

QVariant MapModel::get_at(int row) const {
    if (row < 0 || row > rowCount() - 1) return QVariant();

    return m_data[row];

}

void MapModel::populate(int iwad_index) {
    beginResetModel();
    m_data.clear();

    if (iwad_index == -1) return;

    for (int i = 0; i < m_modfile_model.rowCount(); i++) {
        auto mod_maps = m_modfile_model.get_maps(i);

        for (auto& map : mod_maps)
            if (!m_data.contains(map)) m_data.append(map);

    }

    if (m_data.size() == 0) {
        auto iwad_maps = m_iwad_model.get_maps(iwad_index);

        for (auto& map : iwad_maps)
            m_data.append(map);

    } else
        m_data.sort(Qt::CaseInsensitive);

    m_data.insert(0, "Default");
    endResetModel();
}
