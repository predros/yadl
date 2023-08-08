#include "models/modfile.h"

ModFile::ModFile(const QString& path) : WAD{QFileInfo(path).fileName(), path} {
}
