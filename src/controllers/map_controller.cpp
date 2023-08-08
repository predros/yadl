#include "map_controller.h"

MapController::MapController(const IWADController& iwad, const ModFileController& modfile,
                             QObject *parent)
    : QAbstractListModel{parent}, m_iwad_controller(iwad),  m_modfile_controller(modfile)
{}

int MapController::rowCount(const QModelIndex&) const {
    return m_data.size();
}

int MapController::columnCount(const QModelIndex&) const {
    return 1;
}

QVariant MapController::data(const QModelIndex& index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return m_data[index.row()];
        }
    }

    return QVariant();
}

QVariant MapController::get_at(int row) const {
    if (row < 0 || row > rowCount() - 1) return QVariant();

    return m_data[row];

}

void MapController::populate(int iwad_index) {
    beginResetModel();
    m_data.clear();

    if (iwad_index == -1) return;

    for (int i = 0; i < m_modfile_controller.rowCount(); i++) {
        auto mod_maps = m_modfile_controller.get_maps(i);

        for (auto& map : mod_maps)
            if (!m_data.contains(map)) m_data.append(map);

    }

    if (m_data.size() == 0) {
        auto iwad_maps = m_iwad_controller.get_maps(iwad_index);

        for (auto& map : iwad_maps)
            m_data.append(map);

    } else
        m_data.sort(Qt::CaseInsensitive);

    m_data.insert(0, "Default");
    endResetModel();
}
