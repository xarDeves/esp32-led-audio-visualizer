#pragma once

namespace NetInfo{

	struct info{
        static const unsigned char size = 170;

        char ssid[64];
        char pass[64];
        char ip[14];
        char gateway[14];
        char subnet[14];
    };

};