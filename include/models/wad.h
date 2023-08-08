#ifndef WAD_H
#define WAD_H

#include <QFileInfo>
#include <QString>
#include <QList>
#include <QDataStream>

/**
 * @brief Base class for the IWAD and Modfile model classes.
 * Mostly based off https://www.cyotek.com/blog/reading-doom-wad-files,
 * ported from C# to C++/Qt (and trimmed off the stuff about reading lump
 * data, since I didn't need that here)
*/
class WAD {
public:
    /**
     * @brief name
     * @return The instance's name.
     */
    QString name() const;

    /**
     * @brief file_path
     * @return The instance's file path.
     */
    QString file_path() const;

    void set_name(const QString& name);
    void set_file_path(const QString& path);

    // Gets a const reference to the maps vector.
    const QList<QString>& maps() const;
protected:
    QString m_name;
    QFileInfo m_file;

    int m_lump_count;           // Number of lumps in the wad
    int m_directory_start;      // Offset to the start of the directory list
    QList<QString> map_names;    // Map names contained in the wad

    /**
     * @brief Constructs a new WAD instance (protected,
     * as this class is supposed to be derived).
     * @param name The WAD's name.
     * @param path The WAD's file path.
     */
    WAD(const QString& name, const QString& path);

    /**
     * @brief Reads the WAD header info and stores it.
     * @param input An open file input stream.
     * @return The stream.
     */
    QFile& read_wad_header(QFile& input);

    /**
     * @brief Reads the WAD directory list to find the map names.
     * @param input An open file input stream.
     * @return The stream.
     */
    QFile& find_map_names(QFile& input);


    /**
     * @brief Gets the MD5 hash from the WAD file.
     * @param input An open file input stream.
     * @return The stream.
     */
    QString get_md5(QFile& input) const;
};

#endif // WAD_H
