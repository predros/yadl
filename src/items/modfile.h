#ifndef MODFILE_H
#define MODFILE_H

#include "wad.h"

class ModFile : public WAD {
public:
    ModFile(const QString& path);
};

#endif // MODFILE_H
