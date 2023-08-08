#ifndef PRESET_H
#define PRESET_H

#include <QString>
#include <QList>

// Forward declarations
class QJsonObject;

/**
 * @brief Model class for preset instances.
 */
class Preset {
public:
    /**
     * @brief Creates a new Preset instance.
     * @param id The instance's id.
     * @param name The instance's name.
     * @param sourceport_id The associated sourceport's id.
     * @param iwad_id The associated iwad's id.
     * @param skill The instance's skill level.
     * @param complevel The instance's complevel.
     * @param fast True if fast monsters are enabled, false otherwise.
     * @param coop True if co-op monsters are enabled, false otherwise.
     * @param params The instance's command-line parameters.
     * @param mods List containing the mods file paths.
     */
    Preset(int id, const QString& name, int sourceport_id, int iwad_id, int skill,
           int complevel, bool fast, bool coop, const QString& params = "",
           const QList<QString>& mods = QList<QString>());

    /**
     * @brief Deserializes a JSON object into a Preset instance.
     * @param json The JSON object.
     */
    Preset(const QJsonObject& json);

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
     * @brief sourceport_id
     * @return The associated sourceport's id.
     */
    int sourceport_id() const;

    /**
     * @brief iwad_id
     * @return The associated IWAD's id.
     */
    int iwad_id() const;

    /**
     * @brief skill
     * @return The instance's skill level.
     */
    int skill() const;

    /**
     * @brief complevel
     * @return The instance's complevel.
     */
    int complevel() const;

    /**
     * @brief params
     * @return The instance's command-line parameters.
     */
    QString params() const;

    /**
     * @brief fast
     * @return True if fast monsters are enabled, false otherwise.
     */
    bool fast() const;

    /**
     * @brief coop
     * @return True if co-op monsters are enabled, false otherwise.
     */
    bool coop() const;

    /**
     * @brief mods
     * @return List containing the instance's mod file paths.
     */
    QList<QString> mods() const;

    /**
     * @brief Sets the instance's name.
     * @param new_name The new name.
     */
    void set_name(const QString& new_name);

    /**
     * @brief Sets the associated sourceport ID.
     * @param new_id The new ID.
     */
    void set_sourceport_id(int new_id);

    /**
     * @brief Sets the associated IWAD ID.
     * @param new_id The new ID.
     */
    void set_iwad_id(int new_id);

    /**
     * @brief Sets the instance's skill level.
     * @param new_skill The new skill level.
     */
    void set_skill(int new_skill);

    /**
     * @brief Sets the instance's complevel.
     * @param new_complevel The new complevel.
     */
    void set_complevel(int new_complevel);

    /**
     * @brief Sets the instance's command-line parameters.
     * @param new_params The new parameters.
     */
    void set_params(const QString& new_params);

    /**
     * @brief Sets whether fast monsters are enabled.
     * @param new_fast Self-explanatory.
     */
    void set_fast(bool new_fast);

    /**
     * @brief Sets whether co-op monsters are enabled.
     * @param new_coop Self-explanatory.
     */
    void set_coop(bool new_coop);

    /**
     * @brief set_mods Sets the instance's list of mods.
     * @param mods List containing each mod's file path.
     */
    void set_mods(const QList<QString>& mods);

    /**
     * @brief Serializes the instance to JSON.
     * @return The serialized JSON object.
     */
    QJsonObject to_json() const;

protected:
    int m_id;
    QString m_name;
    int m_port_id;
    int m_iwad_id;
    QString m_params;
    int m_skill;
    int m_complevel;
    bool m_fast;
    bool m_coop;
    QList<QString> m_mods;
};

#endif // PRESET_H
