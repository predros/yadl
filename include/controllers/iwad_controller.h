#ifndef IWADCONTROLLER_H
#define IWADCONTROLLER_H

#include "models/iwad.h"
#include <QAbstractTableModel>
#include <QJsonArray>

/**
 * @brief Controller class for the IWAD model.
 */
class IWADController : public QAbstractTableModel {
    Q_OBJECT
public:
    /**
     * @brief Creates an IWADController instance.
     * @param parent The controller's parent.
     */
    explicit IWADController(QObject *parent = nullptr);

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
     * @brief Fetches the data at the given item (via its unique id) and column
     * @param id The item's id.
     * @param column The desired column.
     * @return The data at the given position.
     */
    QVariant get_at_id(int id, int column) const;

    /**
     * @brief get_maps Gets a list of every map name in a given IWAD.
     * @param index The IWAD's index.
     * @return The list of map names.
     */
    QList<QString> get_maps(int index) const;

    /**
     * @brief Finds the index of an item with a given id.
     * @param id The item's id.
     * @return The item's index if a match is found. Otherwise, -1.
     */
    int index_from_id(int id) const;

    /**
     * @brief Populates the controller with a JSON containing serialized IWAD instances.
     * If any item is invalid, it is skipped.
     * @param array The JSON array containing the serialized instances.
     */
    void populate(const QJsonArray& array);

    /**
     * @brief Adds a new IWAD instance to the controller.
     * @param name The new IWAD's name.
     * @param path The new IWAD's file path.
     * @param params The new IWAD's command-line parameters.
     */
    void add(const QString& name, const QString& path,
             const QString& params);

    /**
     * @brief Edits an existing IWAD instance. Does nothing if the index
     * is out of bounds.
     * @param index The IWAD's index.
     * @param name The IWAD's new name.
     * @param path The IWAD's new file path.
     * @param params The IWAD's new command-line parameters.
     */
    void edit(int index, const QString& name, const QString& path,
              const QString& params);

    /**
     * @brief Removes an existing IWAD instance. If the index is out-of-bounds,
     * nothing is done.
     * @param index The IWAD's index.
     */
    void remove(int index);

    /**
     * @brief Moves an IWAD up the list. Does nothing if the index
     * is out of bounds or if the IWAD is already at the top.
     * @param index The IWAD's index.
     */
    void move_up(int index);

    /**
     * @brief Moves an IWAD up the list. Does nothing if the index
     * is out of bounds or if the IWAD is already at the bottom.
     * @param index The IWAD's index.
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
    QList<IWAD> m_data;

    /**
     * @brief Finds the next unique ID (i.e. the successor to the
     * largest id in the list).
     * @return
     */
    int next_id() const;

};

#endif // IWADCONTROLLER_H
