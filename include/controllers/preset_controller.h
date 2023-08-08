#ifndef PRESETCONTROLLER_H
#define PRESETCONTROLLER_H

#include "models/preset.h"
#include <QAbstractTableModel>

// Forward declarations
class SourcePortController;
class IWADController;

/**
 * @brief Controller class for the Preset model.
 */
class PresetController : public QAbstractTableModel {
    Q_OBJECT
public:
    /**
     * @brief Creates a PresetController instance, with linked
     * SourcePortController and IWADController instances.
     * @param port_controller The associated SourcePortController.
     * @param iwad_controller The associated IWADController.
     * @param parent The controller's parent.
     */
    explicit PresetController(SourcePortController& port_controller,
                              IWADController& iwad_controller,
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
     * @brief Returns the header info for a given section, orientation and role.
     * @param section The section (column for horizontal headers,
     * row for vertical headers).
     * @param orientation The header's orientation.
     * @param role The assigned role.
     * @return The header info.
    */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    
    /**
     * @brief Fetches data at a given row-column pair
     * (using integer indices instead of using a QModelIndex instance).
     * @param row The item's row.
     * @param column The desired column.
     * @return The data at the given position.
     */
    QVariant get_at(int row, int column) const;

    /**
     * @brief Finds the index of an item with a given id.
     * @param id The item's id.
     * @return The item's index if a match is found. Otherwise, -1.
     */
    int index_from_id(int id) const;

    /**
     * @brief Populates the controller with a JSON containing serialized preset instances.
     * If any item is invalid, it is skipped.
     * @param array The JSON array containing the serialized instances.
     */
    void populate(const QJsonArray& array);

    /**
     * @brief Adds a new preset instance to the controller. If an instance with
     * the same name exists, it is overwritten.
     * @param name The preset's name.
     * @param path The preset's sourceport ID.
     * @param params The preset's IWAD ID.
     * @param skill The preset's skill level.
     * @param complevel The preset's complevel.
     * @param fast True if fast monsters are enabled, false otherwise.
     * @param coop True if co-op monsters are enabled, false otherwise.
     * @param params Additional command-line parameters.
     * @param mods List of mod file paths.
     */
    void add_or_edit(const QString& name, int port_id, int iwad_id, int skill, int complevel,
                     bool fast, bool coop, const QString& params, const QList<QString>& mods);
    
    /**
     * @brief Removes an existing preset instance. If the index is out-of-bounds,
     * nothing is done.
     * @param index The preset's index.
     */
    void remove(int index);

    /**
     * @brief Moves a preset up the list. Does nothing if the index
     * is out of bounds or if the preset is already at the top.
     * @param index The preset's index.
     */
    void move_up(int index);

    /**
     * @brief Moves a preset up the list. Does nothing if the index
     * is out of bounds or if the preset is already at the bottom.
     * @param index The preset's index.
     */
    void move_down(int index);

    /**
     * @brief Serializes the controller to a JSON array.
     * @return The JSON array.
     */
    QJsonArray to_json_array() const;

protected:
    /**
     * @brief Contains all the model instances.
     */
    QList<Preset> m_data;

    /**
     * @brief Reference to the SourcePortController.
    */
    SourcePortController& m_sourceport_controller;

    /**
     * @brief Reference to the IWADController.
    */
    IWADController& m_iwad_controller;

    /**
     * @brief Finds the next unique ID (i.e. the successor to the
     * largest id in the list).
     * @return
     */
    int next_id() const;
};

#endif // PRESETCONTROLLER_H
