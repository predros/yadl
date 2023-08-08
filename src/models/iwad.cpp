#include "iwad.h"

IWAD::IWAD(int id, const QString& name, const QString& path,
           const QString& params) : WAD{name, path}, m_id(id), m_params(params) {

}

IWAD::IWAD(const QJsonObject& json) : WAD{json["name"].toString(), json["file_path"].toString()},
    m_id(json["id"].toString().toInt()), m_params(json["params"].toString()) {
}

QString IWAD::params() const {
    return m_params;
}

int IWAD::id() const {
    return m_id;
}

void IWAD::set_params(const QString& params) {
    m_params = params;
}

QJsonObject IWAD::to_json() const {
    QJsonObject json;

    json["id"] = QString::number(m_id);
    json["name"] = m_name;
    json["file_path"] = m_file.absoluteFilePath();
    json["params"] = m_params;

    return json;
}
