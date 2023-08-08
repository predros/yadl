#ifndef PRESET_H
#define PRESET_H

#include <QString>
#include <QList>
class QJsonObject;

class Preset {
public:
    Preset(int id, const QString& name, int sourceport_id, int iwad_id, int skill,
           int complevel, bool fast, bool coop, const QString& params = "",
           const QList<QString>& mods = QList<QString>());
    Preset(const QJsonObject& json);

    int id() const;
    QString name() const;
    int sourceport_id() const;
    int iwad_id() const;
    int skill() const;
    int complevel() const;
    QString params() const;
    bool fast() const;
    bool coop() const;
    QList<QString> mods() const;

    void set_name(const QString& new_name);
    void set_sourceport_id(int new_id);
    void set_iwad_id(int new_id);
    void set_skill(int new_skill);
    void set_complevel(int new_complevel);
    void set_params(const QString& new_params);
    void set_fast(bool new_fast);
    void set_coop(bool new_coop);
    void set_mods(const QList<QString>& mods);

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
