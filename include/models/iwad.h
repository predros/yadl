#ifndef IWAD_H
#define IWAD_H

#include "wad.h"
#include <QString>
#include <QJsonObject>

/**
 * @brief Model class for IWAD instances.
*/
class IWAD : public WAD {
public:
    /**
     * @brief Creates an IWAD instance.
     * @param id The instance's ID.
     * @param name The instance's name.
     * @param path The instance's file path.
     * @param params The instance's command-line parameters.
     */
    IWAD(int id, const QString& name, const QString& path, const QString& params);

    /**
     * @brief Deserializes a JSON object into an IWAD instance.
     * @param json The JSON object.
     */
    IWAD(const QJsonObject& json);

    /**
     * @brief id
     * @return The instance's ID.
     */
    int id() const;
    /**
     * @brief params
     * @return The instance's command-line parameters.
     */
    QString params() const;

    /**
     * @brief Sets the instance's command-line parameters.
     * @param params The new parameters.
     */
    void set_params(const QString& params);

    /**
     * @brief Serializes the instance to JSON.
     * @return The serialized JSON object.
     */
    QJsonObject to_json() const;

protected:
    int m_id;
    QString m_params;
};

#endif // IWAD_H
