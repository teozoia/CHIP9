//
//  DoubleReg.cpp
//  CHIP9
//
//  Created by Matteo Zoia on 30/12/2019.
//  Copyright © 2019 Matteo Zoia. All rights reserved.
//

#include <stdio.h>
#include "Reg.cpp"
#pragma once

template <typename Generic>
class DoubleReg{
    
private:
    char name[3];
    Reg<Generic> *high;
    Reg<Generic> *low;
    
public:
    DoubleReg(Reg<Generic> *high, Reg<Generic> *low){
        this->high = high;
        this->low = low;
        strncpy(name, high->getName(), 2);
        strncpy(name + 1, low->getName(), 2);
    }
    DoubleReg() = default;
    
    void setHigh(Generic value){
        this->high->set(value);
    }
    
    void setLow(Generic value){
        this->low->set(value);
    }
    
    void set(Generic high_v, Generic low_v){
        setHigh(high_v);
        setLow(low_v);
    }
    
    Generic getHigh(){
        return this->high->getValue();
    }
    
    Generic getLow(){
        return this->low->getValue();
    }
    
    /* Unfortunatelly this class can't expose a set(uint16_t val) or uint16_t get()
     * So we define a method outside this class to do this job.
     */
    
    char *getName(){
        return this->name;
    }
    
    void print(){
        printf("%s%s: 0x%02x%02x",
               this->high->getName(), this->low->getName(),
               this->high->getValue(), this->low->getValue());
    }
};

/* Extra function specific for this architecture */
static uint16_t getD(DoubleReg<uint8_t> *dr){
    return ((uint16_t)dr->getHigh() << 8) | ((uint16_t)dr->getLow());
}

static void setD(DoubleReg<uint8_t> *dr, uint16_t dval){
    dr->set((uint8_t)(dval >> 8), (uint8_t)dval);
}
