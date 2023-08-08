#include "modfile_controller.h"
#include <QJsonArray>
#include <QJsonObject>

ModFileController::ModFileController(QObject *parent)
    : QAbstractListModel{parent} {

}

int ModFileController::rowCount(const QModelIndex&) const {
    return m_data.size();
}

int ModFileController::columnCount(const QModelIndex&) const {
    return 2;
}

QVariant ModFileController::data(const QModelIndex& index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return m_data[index.row()].name();

            case 1:
                return m_data[index.row()].file_path();
        }
    }

    return QVariant();
}

QVariant ModFileController::get_at(int row, int column) const {
    if (row < 0 || row > rowCount() - 1) return QVariant();

    switch (column) {
        case 0:
            return m_data[row].name();

        case 1:
            return m_data[row].file_path();
    }

    return QVariant();
}

QList<QString> ModFileController::get_maps(int index) const {
    if (index < 0 || index > rowCount() - 1) return QList<QString>();

    return m_data[index].maps();
}

void ModFileController::populate(const QList<QString>& mods) {
    beginResetModel();

    m_data.clear();

    for (auto& mod : mods) {
        try {
            ModFile m(mod);
            m_data.append(m);
        } catch (std::exception&) {
            continue;
        }
    }

    endResetModel();
}

void ModFileController::populate(const QJsonArray& mods) {
    beginResetModel();

    m_data.clear();

    for (auto& mod : mods) {
        try {
            ModFile m(mod.toObject()["path"].toString());
            m_data.append(m);
        } catch (std::exception&) {
            continue;
        }
    }

    endResetModel();
}

void ModFileController::clear() {
    beginResetModel();
    m_data.clear();
    endResetModel();
}

void ModFileController::add(const QString& path) {
    beginResetModel();
    ModFile mod(path);
    m_data.append(mod);
    endResetModel();
}

void ModFileController::remove(int index) {
    if (index < 0 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data.removeAt(index);
    endResetModel();
}

void ModFileController::move_up(int index) {
    if (index < 1 || index > m_data.size() - 1) return;

    beginResetModel();
    m_data.move(index, index - 1);
    endResetModel();
}

void ModFileController::move_down(int index) {
    if (index < 0 || index > m_data.size() - 2) return;

    beginResetModel();
    m_data.move(index, index + 1);
    endResetModel();
}
