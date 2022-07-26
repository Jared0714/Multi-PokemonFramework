#ifndef STDAFX_HPP
#define STDAFX_HPP

#define _USE_MATH_DEFINES

#include <CTRPluginFramework.hpp>
#include <3ds.h>
#include "csvc.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstdio>
#include <string>
#include <ctime>
#include <cmath>
#include <math.h>
#include <random>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <iterator>

using namespace std;

namespace CTRPluginFramework {
    using CallbackPointer = void (*)(void);
    using OnEventCallback = void(*)(Keyboard &, KeyboardEvent &Event);
    using String = string;
    using StringVector = vector<string>;
    using uVector32 = vector<u32>;
    using uVector16 = vector<u16>;
    using uVector8 = vector<u8>;
    using sVector32 = vector<s32>;
    using sVector16 = vector<s16>;
    using sVector8 = vector<s8>;
}

#endif