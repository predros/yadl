#ifndef MAPCONTROLLER_H
#define MAPCONTROLLER_H

#include "modfile_controller.h"
#include "iwad_controller.h"
#include <QAbstractListModel>

/**
 * @brief Controller class for the Maps list.
 */
class MapController : public QAbstractListModel {
    Q_OBJECT
public:
    /**
     * @brief Creates an MapController instance, linked to a given
     * IWADController and ModFileController.
     * @param iwad_controller The associated IWADController.
     * @param modfile_controller The associated ModFileController.
     * @param parent The controller's parent.
     */
    explicit MapController(const IWADController& iwad_controller,
                           const ModFileController& modfile_controller,
                           QObject *parent = nullptr);

    /**
     * @brief returns the number of rows under the given parent.
     * If no parent is passed, returns the total number of rows.
     * @param parent The parent QModelIndex
     * @return The number of rows.
     */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * @brief returns the number of columns under the given parent.
     * If no parent is passed, returns the total number of columns.
     * @param parent The parent QModelIndex
     * @return The number of columns.
     */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /**
     * @brief Fetches the data stored under the given role for the item referred to by the index.
     * @param index QModelIndex containing the row and column to be fetched.
     * @param role The assigned role.
     * @return The respective data for the given role and item.
     */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Fetches data at a given row
     * (using an integer index instead of using a QModelIndex instance).
     * @param row The item's row.
     * @return The data at the given position.
     */
    QVariant get_at(int row) const;

    /**
     * @brief Populates the controller with the map names from a given IWAD
     * and the current ModFiles.
     * @param iwad_index The selected IWAD's index.
     */
    void populate(int iwad_index);
protected:
    /**
     * @brief Contains all the model instances.
     */
    QList<QString> m_data;

    /**
     * @brief Reference to the IWADController.
    */
    const IWADController& m_iwad_controller;

    /**
     * @brief Reference to the ModFileController.
    */
    const ModFileController& m_modfile_controller;
};

#endif // MAPCONTROLLER_H
