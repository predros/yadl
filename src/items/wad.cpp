#include "wad.h"
#include "../exceptions.h"
#include <fstream>
#include <algorithm>
#include <regex>

WAD::WAD(const QString& name, const QString& path) : m_name(name) {
    m_file = QFileInfo(path);
    // Opens the WAD
    std::ifstream input(path.toStdString(), std::ios_base::binary);

    // If the WAD cannot be openend, throw an exception
    if (input.fail()) throw WADNotFoundException();

    if (m_file.suffix().toLower() == "wad") {
        read_wad_header(input);
        find_map_names(input);
    }

    input.close();
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
    std::ifstream input(path.toStdString(), std::ios_base::binary);

    // If the WAD cannot be openend, throw an exception
    if (input.fail()) throw WADNotFoundException();

    if (m_file.suffix().toLower() == "wad") {
        read_wad_header(input);
        find_map_names(input);
    }

    input.close();

}

const QList<QString>& WAD::maps() const {
    return map_names;
}

void WAD::read_wad_header(std::ifstream& input) {
    // Sets the cursor position to the beginning of the file
    input.seekg(0, std::ios_base::beg);

    // Creates a 12-byte long buffer (same size as the header)
    std::vector<unsigned char> buffer;
    buffer.reserve(12);

    // Copies the header from the WAD to the buffer
    std::copy_n(std::istreambuf_iterator<char>(input), 12, std::back_inserter(buffer));

    // The middle 4 bytes represent the number of lumps in the file (little-endian)
    m_lump_count = buffer[7] << 24 | buffer[6] << 16
                   | buffer[5] << 8 | buffer[4];

    // The final 4 bytes represent the offset to the directory list (also little-endian)
    m_directory_start = buffer[11] << 24 | buffer[10] << 16
                        | buffer[9] << 8 | buffer[8];
}

void WAD::find_map_names(std::ifstream& input) {
    // Sets the stream cursor to the start of the directory list.
    input.seekg(m_directory_start, std::ios_base::beg);

    // Sets the regex for episodic (DOOM, Heretic, etc) and non-episodic (DOOM 2, Final DOOM)
    // map name formats
    std::regex doom1("E[0-9]M[0-9]");
    std::regex doom2("MAP[0-9][0-9]");

    // Iterate through every lump in the directory list
    for (int i = 0; i < m_lump_count - 1; i++) {
        // Create a buffer 16 bytes long
        std::vector<char> buffer;
        buffer.reserve(16);

        // Set the cursor to the current directory
        input.seekg(m_directory_start + 16 * i, std::ios_base::beg);

        // Copy the current directory to the buffer
        std::copy_n(std::istreambuf_iterator<char>(input), 16, std::back_inserter(buffer));

        // The middle 4 bytes contain the lump size, in little-endian format
        int lump_size = buffer[7] << 24 | buffer[6] << 16 | buffer[5] << 8 | buffer[4];

        // Map names are virtual lumps used by the engine as markers (between the actual map
        // contents, such as THINGS or LINEDEFS). As such, any map name lump will have size 0.
        if (lump_size != 0) continue;

        // Create a name string and a string length parameter.
        std::string name = "";
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
            std::vector<char> name_vector(buffer.begin() + 8, buffer.begin() + 8 + name_length);
            name = std::string(name_vector.begin(), name_vector.end());

            // If the resulting name matches either regex (and thus is a map
            // name), add it to the map list.
            if (std::regex_match(name, doom1) || std::regex_match(name, doom2)) {
                map_names.append(QString::fromStdString(name));
            }
        }
    }
}
