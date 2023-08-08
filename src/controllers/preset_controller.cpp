#include "preset_controller.h"
#include "sourceport_controller.h"
#include "iwad_controller.h"
#include <QJsonArray>

PresetController::PresetController(SourcePortController& sp, IWADController& iwad,
                                   QObject *parent)
    : QAbstractTableModel{parent}, m_sourceport_controller(sp), m_iwad_controller(iwad) {
}

int PresetController::rowCount(const QModelIndex&) const {
    return m_data.size();
}

int PresetController::columnCount(const QModelIndex&) const {
    return 3;
}

QVariant PresetController::data(const QModelIndex& index, int role) const {

    if (index.isValid() && role == Qt::DisplayRole) {
        int id;

        switch (index.column()) {
            case 0:
                return m_data[index.row()].name();

            case 1:
                id = m_data[index.row()].sourceport_id();
                return m_sourceport_controller.get_at_id(id, 0);

            case 2:
                id = m_data[index.row()].iwad_id();
                return m_iwad_controller.get_at_id(id, 0);
        }
    }

    return QVariant();
}

QVariant PresetController::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return "Name";

            case 1:
                return "Sourceport";

            case 2:
                return "IWAD";
        }
    }

    return QVariant();
}

QVariant PresetController::get_at(int row, int column) const {
    if (row < 0 || row > rowCount() - 1) return QVariant();

    int id;

    switch (column) {
        case 0:
            return m_data[row].name();

        case 1:
            id = m_data[row].sourceport_id();
            return m_sourceport_controller.get_at_id(id, 0);

        case 2:
            id = m_data[row].iwad_id();
            return m_iwad_controller.get_at_id(id, 0);

        case 3:
            return m_data[row].sourceport_id();

        case 4:
            return m_data[row].iwad_id();

        case 5:
            return m_data[row].skill();

        case 6:
            return m_data[row].complevel();

        case 7:
            return m_data[row].fast();

        case 8:
            return m_data[row].coop();

        case 9:
            return m_data[row].params();

        case 10:
            return m_data[row].mods();
    }

    return QVariant();
}

int PresetController::index_from_id(int id) const {
    for (int i = 0; i < m_data.size(); i++) {
        if (m_data[i].id() == id) return i;
    }

    return -1;
}

int PresetController::next_id() const {
    int result = 0;

    for (auto& iwad : m_data)
        result = std::max(result, iwad.id());

    return result + 1;
}

void PresetController::populate(const QJsonArray& array) {
    beginResetModel();
    m_data.clear();

    for (auto& json : array) {
        try {
            m_data.append(Preset(json.toObject()));
        } catch (std::exception& e) {
            continue;
        }
    }

    endResetModel();
}

void PresetController::add_or_edit(const QString& name, int port_id, int iwad_id,
                                   int skill,
                                   int complevel, bool fast, bool coop, const QString& params,
                                   const QList<QString>& mods) {
    Preset *exists = nullptr;

    for (auto& preset : m_data)
        if (preset.name() == name) exists = &preset;

    beginResetModel();

    if (exists == nullptr) {
        int id = next_id();
        Preset new_preset(id, name, port_id, iwad_id, skill, complevel, fast, coop, params, mods);
        m_data.append(new_preset);
    } else {
        exists->set_name(name);
        exists->set_sourceport_id(port_id);
        exists->set_iwad_id(iwad_id);
        exists->set_skill(skill);
        exists->set_complevel(complevel);
        exists->set_fast(fast);
        exists->set_coop(coop);
        exists->set_params(params);
        exists->set_mods(mods);
    }

    endResetModel();
}

void PresetController::remove(int index) {
    if (index < 0 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data.removeAt(index);
    endResetModel();
}

void PresetController::move_up(int index) {
    if (index < 1 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data.move(index, index - 1);
    endResetModel();
}

void PresetController::move_down(int index) {
    if (index < 0 || index > m_data.size() - 2) return;

    beginResetModel();
    m_data.move(index, index + 1);
    endResetModel();
}

QJsonArray PresetController::to_json_array() const {
    QJsonArray array;

    for (auto& preset : m_data)
        array.append(preset.to_json());

    return array;
}
