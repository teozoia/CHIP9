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
    // insert code here...
    std::cout << "Hello, World!\n";
    
    //char rompath[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/bootrom";
    char rompath[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/bootrom.patched";
    
    Cpu chip9 = Cpu();
    GScreen gscreen = GScreen();

    //chip9.status();
    gscreen.init("CHIP9", chip9.get_scr());

    chip9.loadrom(rompath, 779, 0x0);
    chip9.show_memory(0,300);

    while(gscreen.running()){
        gscreen.handleEvents();

        chip9.cycle();

        gscreen.update();
        gscreen.render();
    }
     /*
    for(int i = 0; i < 10000; i++){
        chip9.fetch();
        chip9.decode();
        chip9.execute();
        chip9.status();

    }
    */
    return 0;
}
