#include "models/sourceport.h"
#include "exceptions.h"

SourcePort::SourcePort(int id, const QString& name, const QString& path,
                       const QString& params) : m_id(id), m_name(name), m_params(params) {
    m_file = QFileInfo(path);

    if (!m_file.exists()) throw PortNotFoundException();

    if (!m_file.isExecutable()
            && m_file.suffix() != "exe") throw PortNotExecutableException();

    set_sourceport_type();
}

SourcePort::SourcePort(const QJsonObject& json) {
    try {
        m_id = json["id"].toString().toInt();
        m_name = json["name"].toString();
        m_file = QFileInfo(json["file_path"].toString());
        m_params = json["params"].toString();
        set_sourceport_type();
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

SourcePortType SourcePort::sourceport_type() const {
    return m_type;
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

    set_sourceport_type();
}

QJsonObject SourcePort::to_json() const {
    QJsonObject json;
    json["id"] = QString::number(m_id);
    json["name"] = m_name;
    json["file_path"] = m_file.absoluteFilePath();
    json["params"] = m_params;

    return json;
}

void SourcePort::set_sourceport_type() {
    QString name = m_file.fileName();

    if (name.contains("chocolate", Qt::CaseInsensitive)) {
        m_type = SOURCEPORT_CHOCOLATE;
    } else if (name.contains("crispy", Qt::CaseInsensitive)) {
        m_type = SOURCEPORT_CRISPY;
    } else if (name.contains("dsda", Qt::CaseInsensitive)) {
        m_type = SOURCEPORT_DSDA;
    } else if (name.contains("eternity", Qt::CaseInsensitive)) {
        m_type = SOURCEPORT_ETERNITY;
    } else if (name.contains("nugget", Qt::CaseInsensitive)) {
        m_type = SOURCEPORT_ETERNITY;
    } else if (name.contains("prboom", Qt::CaseInsensitive) ||
               name.contains("glboom", Qt::CaseInsensitive)) {
        m_type = SOURCEPORT_PRBOOM;
    } else if (name.contains("retro", Qt::CaseInsensitive)) {
        m_type = SOURCEPORT_RETRO;
    } else if (name.contains("woof", Qt::CaseInsensitive)) {
        m_type = SOURCEPORT_WOOF;
    } else if (name.contains("zdoom", Qt::CaseInsensitive)) {
        m_type = SOURCEPORT_ZDOOM;
    } else {
        m_type = SOURCEPORT_GENERIC;
    }

}
