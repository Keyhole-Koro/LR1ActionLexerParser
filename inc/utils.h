#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

#include "conditions"

char *readUntil(bool (*condition)(char*), char *ipt);

#endif