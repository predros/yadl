#ifndef MODFILECONTROLLER_H
#define MODFILECONTROLLER_H

#include "models/modfile.h"
#include <QAbstractListModel>

/**
 * @brief Controller class for the ModFile model.
 */
class ModFileController : public QAbstractListModel {
    Q_OBJECT
public:
    /**
     * @brief Creates a ModFileController instance.
     * @param parent The controller's parent.
     */
    explicit ModFileController(QObject *parent = nullptr);

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
     * @brief Fetches data at a given row-column pair
     * (using integer indices instead of using a QModelIndex instance).
     * @param row The item's row.
     * @param column The desired column.
     * @return The data at the given position.
     */
    QVariant get_at(int row, int column) const;

    /**
     * @brief get_maps Gets a list of every map name in a given ModFile.
     * @param index The item's index.
     * @return The list of map names.
     */
    QList<QString> get_maps(int index) const;

    /**
     * @brief Populates the controller with a QStringList containing file paths.
     * If any item is invalid, it is skipped.
     * @param mods The QStringList containg the mod file paths.
     */
    void populate(const QList<QString>& mods);

    /**
     * @brief Populates the controller with a JSON containing serialized IWAD instances.
     * If any item is invalid, it is skipped.
     * @param mods The JSON array containing the serialized instances.
     */
    void populate(const QJsonArray& mods);

    /**
     * @brief Clears the controller, removing every model instance.
    */
    void clear();

    /**
     * @brief Adds a new modfile, with a given file path.
     * @param path Path to the new instance.
    */
    void add(const QString& path);

    /**
     * @brief Removes an existing modfile. If index is out-of-bounds,
     * nothing is done.
     * @param index The modfile's index.
    */
    void remove(int index);

    /**
     * @brief Moves a modfile up the list. Does nothing if the index
     * is out of bounds or if the file is already at the top.
     * @param index The modfile's index.
     */
    void move_up(int index);

     /**
     * @brief Moves a modfile down the list. Does nothing if the index
     * is out of bounds or if the modfile is already at the bottom.
     * @param index The modfile's index.
     */
    void move_down(int index);
protected:
    /**
     * @brief Contains all the model instances.
     */
    QList<ModFile> m_data;

};

#endif // MODFILECONTROLLER_H
