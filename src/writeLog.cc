#include "writeLog.h"

void writeLog(FILE* file, string log) {
    fwrite(log.c_str(), log.size(), 1, file);
}