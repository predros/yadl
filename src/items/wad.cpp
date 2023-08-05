#include "wad.h"
#include "../exceptions.h"
#include <QRegularExpression>

WAD::WAD(const QString& name, const QString& path) : m_name(name) {
    m_file = QFileInfo(path);
    // Opens the WAD
    QFile file(path);

    // If the WAD cannot be openend, throw an exception
    if (!file.open(QIODevice::ReadOnly)) throw WADNotFoundException();

    if (m_file.suffix().toLower() == "wad") {
        read_wad_header(file);
        find_map_names(file);
    }
}

QString WAD::name() const {
    return m_name;
}

QString WAD::file_path() const {
    return m_file.absoluteFilePath();
}

void WAD::set_name(const QString& new_name) {
    m_name = new_name;
}

void WAD::set_file_path(const QString& path) {
    m_file = QFileInfo(path);
    QFile input(path);

    // If the WAD cannot be openend, throw an exception
    if (input.open(QIODevice::ReadOnly)) throw WADNotFoundException();

    if (m_file.suffix().toLower() == "wad") {
        read_wad_header(input);
        find_map_names(input);
    }
}

const QList<QString>& WAD::maps() const {
    return map_names;
}

QFile& WAD::read_wad_header(QFile& input) {
    // Sets the cursor position to the beginning of the file
    input.seek(0);

    // Creates a 12-byte long buffer (same size as the header)
    QByteArray buffer = input.read(12);

    // The middle 4 bytes represent the number of lumps in the file (little-endian)
    m_lump_count = (unsigned char)buffer[7] << 24 | (unsigned char)buffer[6] << 16
                   | (unsigned char)buffer[5] << 8 | (unsigned char)buffer[4];

    // The final 4 bytes represent the offset to the directory list (also little-endian)
    m_directory_start = (unsigned char)buffer[11] << 24 | (unsigned char)buffer[10] << 16
                        | (unsigned char)buffer[9] << 8 | (unsigned char)buffer[8];

    return input;
}

QFile& WAD::find_map_names(QFile& input) {
    // Sets the regex for episodic (DOOM, Heretic, etc) and non-episodic (DOOM 2, Final DOOM)
    // map name formats
    static QRegularExpression doom1("E[0-9]M[0-9]");
    static QRegularExpression doom2("MAP[0-9][0-9]");

    // Iterate through every lump in the directory list
    for (int i = 0; i < m_lump_count - 1; i++) {
        // Set the cursor to the current directory
        input.seek(m_directory_start + 16 * i);

        // Copy the current directory to a buffer (16 bytes long)
        QByteArray buffer = input.read(16);

        // The middle 4 bytes contain the lump size, in little-endian format
        int lump_size = (unsigned char)buffer[7] << 24 | (unsigned char)buffer[6] << 16 |
                        (unsigned char)buffer[5] << 8 | (unsigned char)buffer[4];

        // Map names are virtual lumps used by the engine as markers (between the actual map
        // contents, such as THINGS or LINEDEFS). As such, any map name lump will have size 0.
        if (lump_size != 0) continue;

        // Create a name string and a string length parameter.
        QString name = "";
        int name_length = 0;

        // Lump names are up to 8 bytes long, being padded by NULL characters. So, we iterate
        // backwards through the final 8 bytes until we find a non-NULL character: the rest of
        // the bytes are our lump name.
        for (int j = 16; j > 8; j--) {
            if (buffer[j - 1] != '\0') {
                name_length = j - 8;
                break;
            }
        }

        // If everything went correct, this shouldn't be an issue
        if (name_length > 0) {
            // Convert the bytes to signed char (ASCII), and then to a string
            QByteArray name_array = buffer.sliced(8, name_length);
            name = QString(name_array);

            // If the resulting name matches either regex (and thus is a map
            // name), add it to the map list.
            if (doom1.match(name).hasMatch() || doom2.match(name).hasMatch()) {
                map_names.append(name);
            }
        }
    }

    return input;
}
