//
//  main.cpp
//  CHIP9
//
//  Created by Matteo Zoia on 29/12/2019.
//  Copyright © 2019 Matteo Zoia. All rights reserved.
//

#include <iostream>
#include "cpu/Cpu.cpp"
#include "cpu/GScreen.hpp"

int main(int argc, const char * argv[]) {

    char bootrompath[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/bootrom.patched";
    char rompath[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/rom.patched";

    std::clock_t start;
    double duration;
    start = std::clock();
    
    Cpu chip9 = Cpu();
    GScreen gscreen = GScreen();

    gscreen.init("CHIP9", chip9.get_scr());

    chip9.loadrom(bootrompath, 779, 0x0);
    chip9.loadrom(rompath, 3072, 0x0597);

    double t = 20000; // Time for screen refresh

    while(gscreen.running()){

        chip9.cycle();
        duration = ( std::clock() - start );

        if(duration - t > 0){
            start = std::clock();
            gscreen.handleEvents();
            gscreen.update();
            gscreen.render();
        }

    }

    return 0;
}
