#ifndef SOURCEPORT_H
#define SOURCEPORT_H

#include <QString>
#include <QFileInfo>
#include <QDataStream>
#include <QJsonObject>

class SourcePort {
public:
    SourcePort(int id, const QString& name, const QString& path, const QString& params);
    SourcePort(const QJsonObject& json);

    int id() const;
    QString name() const;
    QString file_path() const;
    QFileInfo file() const;
    QString params() const;

    void set_name(const QString& new_name);
    void set_file_path(const QString& new_path);
    void set_params(const QString& new_params);

    QJsonObject to_json() const;

protected:
    int m_id;
    QString m_name;
    QFileInfo m_file;
    QString m_params;

};
#endif // SOURCEPORT_H
