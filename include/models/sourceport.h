#ifndef SOURCEPORT_H
#define SOURCEPORT_H

#include <QString>
#include <QFileInfo>
#include <QDataStream>
#include <QJsonObject>

/**
 * @brief Enum for common sourceport families.
 */
enum SourcePortType {
    SOURCEPORT_CHOCOLATE,
    SOURCEPORT_CRISPY,
    SOURCEPORT_DSDA,
    SOURCEPORT_ETERNITY,

    SOURCEPORT_GENERIC,

    SOURCEPORT_NUGGET,
    SOURCEPORT_PRBOOM,
    SOURCEPORT_RETRO,
    SOURCEPORT_WOOF,
    SOURCEPORT_ZDOOM,
};

/**
 * @brief Model class for sourceport instances.
 */
class SourcePort {
public:
    /**
     * @brief Creates a SourcePort instance.
     * @param id The instance's ID.
     * @param name The instance's name.
     * @param path The instance's file path.
     * @param params The instance's command-line parameters.
     */
    SourcePort(int id, const QString& name, const QString& path, const QString& params);

    /**
     * @brief Deserializes a JSON object into a SourcePort instance.
     * @param json The JSON object.
     */
    SourcePort(const QJsonObject& json);

    /**
     * @brief id
     * @return The instance's ID.
     */
    int id() const;

    /**
     * @brief name
     * @return The instance's name.
     */
    QString name() const;

    /**
     * @brief file_path
     * @return The instance's absolute file path.
     */
    QString file_path() const;

    /**
     * @brief file
     * @return A copy of the instance's QFileInfo.
     */
    QFileInfo file() const;

    /**
     * @brief params
     * @return The instance's command-line parameters.
     */
    QString params() const;

    /**
     * @brief sourceport_type
     * @return The instance's sourceport family.
     */
    SourcePortType sourceport_type() const;

    /**
     * @brief Sets the instance's name.
     * @param new_name The new name.
     */
    void set_name(const QString& new_name);

    /**
     * @brief Sets the instance's file path.
     * @param new_path The new file path.
     */
    void set_file_path(const QString& new_path);

    /**
     * @brief Sets the instance's command-line parameters.
     * @param new_params The new parameters.
     */
    void set_params(const QString& new_params);

    /**
     * @brief Serializes the instance to JSON.
     * @return The serialized JSON object.
     */
    QJsonObject to_json() const;

protected:
    int m_id;
    QString m_name;
    QFileInfo m_file;
    QString m_params;
    SourcePortType m_type;

    /**
     * @brief Sets the instance's sourceport family according
     * to the stored file name.
     */
    void set_sourceport_type();

};
#endif // SOURCEPORT_H
