#include <3ds.h>
#include <algorithm>
#include <atomic>
#include <cfloat>
#include <cmath>
#include <cstring>
#include <limits>
#include <list>
#include <memory>
#include <queue>
#include <string>
#include <type_traits>
#include <vector>

#include "types.h"

#include "CTRPluginFramework/Utils/StringExtensions.hpp"
#include "CTRPluginFramework/Menu/MenuEntryHotkeys.hpp"
#include "CTRPluginFramework/Menu/MessageBox.hpp"
#include "CTRPluginFramework/System/Clock.hpp"
#include "CTRPluginFramework/System/Controller.hpp"
#include "CTRPluginFramework/System/File.hpp"
#include "CTRPluginFramework/System/Hook.hpp"
#include "CTRPluginFramework/System/Mutex.hpp"
#include "CTRPluginFramework/System/Process.hpp"
#include "CTRPluginFramework/System/Rect.hpp"
#include "CTRPluginFramework/System/Task.hpp"
#include "CTRPluginFramework/System/Touch.hpp"
#include "CTRPluginFramework/System/Vector.hpp"
#include "CTRPluginFramework/Graphics/Color.hpp"
#include "CTRPluginFramework/Graphics/CustomIcon.hpp"

using namespace std;