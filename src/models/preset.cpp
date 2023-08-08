#include "models/preset.h"
#include <QJsonObject>
#include <QJsonArray>

Preset::Preset(int id, const QString& name, int sourceport_id, int iwad_id, int skill,
               int complevel, bool fast, bool coop, const QString& params,
               const QList<QString>& mods)
    : m_id(id), m_name(name), m_port_id(sourceport_id), m_iwad_id(iwad_id), m_params(params),
      m_skill(skill), m_complevel(complevel), m_fast(fast), m_coop(coop) {
    for (auto& mod : mods)
        m_mods.append(mod);
}

Preset::Preset(const QJsonObject& json) {
    m_id = json["id"].toString().toInt();
    m_name = json["name"].toString();
    m_port_id = json["port"].toString().toInt();
    m_iwad_id = json["iwad"].toString().toInt();
    m_skill = json["skill"].toString().toInt();
    m_complevel = json["complevel"].toString().toInt();
    m_fast = json["fast"].toString() == "1";
    m_coop = json["coop"].toString() == "1";
    m_params = json["params"].toString();
    m_mods = QList<QString>();

    QJsonValue mods_list = json["mods"];

    if (mods_list.isArray()) {
        QJsonArray array = mods_list.toArray();

        try {
            for (int i = 0; i < array.size(); i++)
                m_mods.append(array[i].toObject()["path"].toString());
        } catch (std::exception&) {
        }
    }
}

int Preset::id() const {
    return m_id;
}

QString Preset::name() const {
    return m_name;
}

int Preset::iwad_id() const {
    return m_iwad_id;
}

int Preset::sourceport_id() const {
    return m_port_id;
}

int Preset::skill() const {
    return m_skill;
}

int Preset::complevel() const {
    return m_complevel;
}

bool Preset::fast() const {
    return m_fast;
}

bool Preset::coop() const {
    return m_coop;
}

QString Preset::params() const {
    return m_params;
}

QList<QString> Preset::mods() const {
    return m_mods;
}

void Preset::set_name(const QString& new_name) {
    m_name = new_name;
}

void Preset::set_iwad_id(int new_id) {
    m_iwad_id = new_id;
}

void Preset::set_sourceport_id(int new_id) {
    m_port_id = new_id;
}

void Preset::set_skill(int new_skill) {
    m_skill = new_skill;
}

void Preset::set_complevel(int new_complevel) {
    m_complevel = new_complevel;
}

void Preset::set_fast(bool new_fast) {
    m_fast = new_fast;
}

void Preset::set_coop(bool new_coop) {
    m_coop = new_coop;
}

void Preset::set_params(const QString& new_params) {
    m_params = new_params;
}

void Preset::set_mods(const QList<QString>& mods) {
    m_mods.clear();

    for (auto& mod : mods)
        m_mods.append(mod);
}

QJsonObject Preset::to_json() const {
    QJsonObject json;

    json["id"] = QString::number(m_id);
    json["name"] = m_name;
    json["port"] = QString::number(m_port_id);
    json["iwad"] = QString::number(m_iwad_id);
    json["skill"] = QString::number(m_skill);
    json["complevel"] = QString::number(m_complevel);
    json["fast"] = m_fast ? "1" : "0";
    json["coop"] = m_coop ? "1" : "0";
    json["params"] = m_params;

    QJsonArray mods;

    for (auto& mod : m_mods) {
        QJsonObject obj;
        obj["path"] = mod;
        mods.append(obj);
    }

    json["mods"] = mods;

    return json;
}
