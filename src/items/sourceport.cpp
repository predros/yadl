#include "sourceport.h"
#include "../exceptions.h"

SourcePort::SourcePort(int id, const QString& name, const QString& path,
                       const QString& params) : m_id(id), m_name(name), m_params(params) {
    m_file = QFileInfo(path);

    if (!m_file.exists()) throw PortNotFoundException();

    if (!m_file.isExecutable()) throw PortNotExecutableException();
}

SourcePort::SourcePort(const QJsonObject& json) {
    try {
        m_id = json["id"].toString().toInt();
        m_name = json["name"].toString();
        m_file = QFileInfo(json["file_path"].toString());
        m_params = json["params"].toString();
    } catch (int) {
        return;
    }
}

int SourcePort::id() const {
    return m_id;
}

QString SourcePort::name() const {
    return m_name;
}

QString SourcePort::file_path() const {
    return m_file.absoluteFilePath();
}

QString SourcePort::params() const {
    return m_params;
}

QFileInfo SourcePort::file() const {
    return m_file;
}

void SourcePort::set_name(const QString& name) {
    m_name = name;
}

void SourcePort::set_params(const QString& params) {
    m_params = params;
}

void SourcePort::set_file_path(const QString& path) {
    m_file = QFileInfo(path);

    if (!m_file.exists()) throw PortNotFoundException();

    if (!m_file.isExecutable()) throw PortNotExecutableException();
}

QJsonObject SourcePort::to_json() const {
    QJsonObject json;
    json["id"] = QString::number(m_id);
    json["name"] = m_name;
    json["file_path"] = m_file.absoluteFilePath();
    json["params"] = m_params;

    return json;
}
