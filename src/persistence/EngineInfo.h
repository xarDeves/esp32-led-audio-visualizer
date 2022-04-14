#pragma once

namespace EngineInfo{

    struct info{
            
        unsigned int noise = 300;
        unsigned int rMax = 150000;
        
        unsigned char lowStart = 2;
        unsigned char lowEnd = 5;

        unsigned char midStart = 5;
        unsigned char midEnd = 68;

        unsigned char highStart = 68;
        unsigned char highEnd = 255;
        
        unsigned char rSmoothingLen = 0;
        unsigned char gSmoothingLen = 0;
        unsigned char bSmoothingLen = 0;

        //float band1Weight = 1;
        //float band2Weight = 1;
        //float band3Weight = 1;
    };

}
