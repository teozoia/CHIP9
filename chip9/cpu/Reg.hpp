#include <iostream>

#ifndef CHIP9_REG_HPP
#define CHIP9_REG_HPP

template <typename Generic>
class Reg{
    
private:
    char name[2];
    Generic value;
    
public:
    Reg(Generic value, char *name){
        strncpy(this->name, name, 2);
        this->value = value;
    }
    Reg() = default;
    
    void set(Generic value){
        this->value = value;
    }
    
    Generic getValue(){
        return this->value;
    }
    
    char *getName(){
        return this->name;
    }
    
    void print(){
        printf("%s: 0x%x (%d)", this->name, this->value, this->value);
    }
};

#endif //CHIP9_REG_HPP
