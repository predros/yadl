#ifndef IWAD_H
#define IWAD_H

#include "wad.h"
#include <QString>
#include <QJsonObject>

class IWAD : public WAD {
public:
    IWAD(int id, const QString& name, const QString& path, const QString& params);
    IWAD(const QJsonObject& json);

    int id() const;
    QString params() const;
    void set_params(const QString& params);
    QJsonObject to_json() const;

protected:
    int m_id;
    QString m_params;
};

#endif // IWAD_H
