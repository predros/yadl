#ifndef WAD_H
#define WAD_H

#include <QFileInfo>
#include <QString>
#include <QList>

/**
 * Mostly based off https://www.cyotek.com/blog/reading-doom-wad-files,
 * ported from C# to C++ (and trimmed off the stuff about reading lump
 * data, since I didn't need that here)
*/
class WAD {
public:
    QString name() const;
    QString file_path() const;

    void set_name(const QString& name);
    void set_file_path(const QString& path);

    // Gets a const reference to the maps vector.
    const QList<QString>& maps() const;
protected:
    // Class constructor
    WAD(const QString& name, const QString& path);

    // Reads the WAD header info.
    void read_wad_header(std::ifstream& input);
    // Reads the WAD directory list to find the map names.
    void find_map_names(std::ifstream& input);

    QString m_name;
    // Path to the WAD file
    QFileInfo m_file;

    // Number of lumps in the wad
    int m_lump_count;
    // Offset to the start of the directory list
    int m_directory_start;
    // Map names contained in the wad
    QList<QString> map_names;
};

#endif // WAD_H
