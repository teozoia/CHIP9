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

    char bootrompath[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/bootrom.patched";
    char rompath[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/rom.patched";
    //char myrom[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/winner/discoviking"; //1575 NO
    //char myrom[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/winner/dicesquad"; //5541 OK
    //char myrom[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/winner/perfectblue-dragonmaidontherun"; //17534 NO
    //char myrom[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/winner/redstoneblockchain-rickrom"; // 64050 NO
    //char myrom[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/winner/SiceSquad-mandelbrotzoom"; //1328
    //char myrom[] = "/Users/teozoia/Desktop/acp/project/chip9/rom/winner/wrecktheline-badapple"; //61118


    std::clock_t start;
    double duration;

    start = std::clock();
    
    Cpu chip9 = Cpu();
    GScreen gscreen = GScreen();

    //chip9.status();
    gscreen.init("CHIP9", chip9.get_scr());

    chip9.loadrom(bootrompath, 779, 0x0);
    chip9.loadrom(rompath, 3072, 0x0597);
    //chip9.loadrom(myrom, 61118, 0x0597);
    chip9.show_memory(0x05A2, 10);

    double t = 20000; //15000

    while(gscreen.running()){

        chip9.cycle();
        duration = ( std::clock() - start ); //(double) CLOCKS_PER_SEC;

        //std::cout<<"printf: "<< duration <<'\n';


        if(duration - t > 0){
            start = std::clock();
            gscreen.handleEvents();
            gscreen.update();
            gscreen.render();
        }


    }

    return 0;
}
