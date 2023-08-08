#ifndef MODFILE_H
#define MODFILE_H

#include "wad.h"

/**
 * @brief Model class for ModFile instances.
 */
class ModFile : public WAD {
public:
    /**
     * @brief Creates a ModFile instance.
     * @param path File path to the given mod.
     */
    ModFile(const QString& path);
};

#endif // MODFILE_H
