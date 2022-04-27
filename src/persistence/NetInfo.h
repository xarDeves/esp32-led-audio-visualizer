#pragma once

#include "debug.h"

namespace NetInfo{

	struct info{

        char ssid[64];
        char pass[64];
        char ip[14];
        char gateway[14];
        char subnet[14];
    };

}
