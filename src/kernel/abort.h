#pragma once

#include "../global.h"

#define abort(reasson) _abort(reasson " \n(" __FILE__  ":" TOSTRING(__LINE__) ")\n");

void _abort(const char *reasson);
