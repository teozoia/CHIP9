# CHIP9 Emu
_Project developped for Advanced Computer Programming exam @ Unimi_

Based on X-MAS CTF 2019 chall, CHIP9, is a 8-bit CPU with 64Kb of main memory (quite similar to Intel 8080 / Zilog Z80). CHIP9-Emu is an emulator for the architecture described in the chall.

![animation](static/animation.gif)

## The challenge

> I found an old CHIP9 console in the attic and a cartridge with a program. Unfortunately the motherboard is gone and the console doesn't turn on anymore. The good news is that I also found the developer's manual, can you understand something more about it?

There are also 3 attachments provided, a PDF with the CPU design specification and 2 already compiled program: _bootrom_ and _rom_.

### First approach

The first approach in a CTF game is always get a better knowledge about the challenge, in this case it means doing some search involving the name of the challenge _CHIP9_ or something about that. Couriously i didn't find any page about a CPU or architecture called _CHIP9_. 

Serching more deepily I found some article and website about an emulator called _CHIP8_, it appears to be an interpreter for develop game code back in time. I also found a very well described [technical reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) about it and some [emulator](https://github.com/massung/CHIP-8). Unfortunately _CHIP8_ doesn't help so much, because it has very different architecture, very tight set of instruction compared to _CHIP9_, different register and also different memory and addresses size. I think that it was only a starting point that the writer of the challenge used to build it's architecture.

The next step, before starting to develop such architecture described in the _CHIP9_ specification PDF, is to take a look at the others two files included in the challenge: _bootrom_ and _rom_. I first scan them with _binwalk_ (a command line tool that scan files and serching for know headers) and after that I try to inspect the byte inside with _hexdump_. The files appears to be a raw ones, in fact they are only hex bytes program to _CHIP9_ as expected.

## Emulation

Emulation works on simulation behavior of an existing processor and it's individual components. So the goal is to build each individual piece of the system and then connect the pieces much like wires do in hardware. There are three ways of handling processor emulation (given an executable rom):

- Interpretation
- Static recompilation
- Dynamic recompilation

With all of these paths, there are same overall goal: execute a piece of code to modify processor state and interact with hardware (or better, emulated hardware). Processor state is composed by processor registers, interrupt handlers, etc for a given processor target. 

In this case I choose interpretation for building _CHIP9_ emulator, so the basic idea is read byte by byte the given rom, fetch the type of the instruction, simulate the operation like the hardware do and if it's needed update all components (like CPU registers, memory, etc). According to the _ACP_ project constraint I built the emulator in _C++_ with _Data Driven Programming_, _Object Orientation_ and _Generic Programming_.

## Architecture design
The CPU of the described system is an 8-bit little-endian (means that the word starts with the less significant bit and end with the most significant bit), quite similar to an Intel 8080 or a Zilog Z80. The system is equipped with a 64Kbyte of main memory (RAM) and some input/output device like a screen of 128x64 1-bit pixels (1-bit pixels means that every pixel is not RGB but can only be switch on or off) and a joystick with basic controller button (`A`, `B`, `UP`, `DOWN`, `RIGHT`, `LEFT`, `START`, `SELECT`).

### Registers

Every modern CPU according to the _von Neumann architecture_ have it's own registers, on-bord memory that contains data to be manipulated. In _CHIP9_ arch there are:

* 7 8-bit  general purpose registers: `A`, `B`, `C`, `D`, `E`, `H` and `L`.
* 3 16-bit general purpose registers: `BC`, `DE` and `HL` that are composed by the 
* Stack pointer `SP`, 16-bit register that takes track of the current position in the stack.
* Program counter `PC`, 16-bit register that indicate the position in memory of the next code instruction that will be execute.
* Flag `F`, 8-bit register that contains flags about the last math operation executed.

#### Stack pointer

As said before the `SP` register indicates the current position of the stack in memory. The stack is used for saving variables, saving return addresses, passing arguments to subroutines, and various other uses. With the `CALL` and `PUSH` instructions data are putted onto the stack; on the other hand with `POP` and `RET` instructions the CPU takes information off of the stack.

When data are pushed to the stack, it grows downward in memory (RAM), for this reason as default the `SP` should always be initialized with the highest memory location (top of RAM space `0xFFFE`); the corrisponding operation command can be `LDX SP, 0xFFFE` (or `22` `FE` `FF` in machine code). Another important facts is that the stack has to be always aligned with memory addresses.

#### Program counter

The `PC` register that indicate the position in memory of the next code instruction that need to be execute, once this instruction has been executed the register will indicate the next byte in memory. If a `JUMP` instruction occours the `PC` register can be change it's value according to the jump indication. Some kind of instruction (eg. the ones that invove immediate like `ADDI`) need some extra read off  the memory to complete the instruction, for this reason the instruction that include parameeters need to increment the `PC` by an extra byte number.

On power up, the _CHIP9_ `PC` is initialized to `0x0000` and the instruction found at this location in RAM is executed.

##### Boot process

The specification manual indicate the address `0x0000` as the place where _CHIP9_ finds the _bootrom_; the manual also indicate the address `0x0597` as _CHIP9_ can find the desired rom to execute after the boot sequence. The `PC` starts always at value `0x0000`, all other general purpose register are left uninitialized, their values are affected by the electronical entropy, so the _bootrom_ is developped to workwith any initial register state.

#### Flag

The Flag Register is an 8-bit register, but it can't be modified by the programmer, it's value is updated after a math operation according to the specification below, the flag register consists of the following bits:

|  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
| :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
|  Z   |  N   |  H   |  C   |  0   |  0   |  0   |  0   |

* **Zero Flag** `Z`, this bit is set when the result of a math operation is zero or two values match when using the `CMP` instruction.

* **Negative Flag** `N`, this bit is set when the result of a math operation is negative (ie has bit 7 set).

* **Carry Flag** `H`, this bit is set if a carry occurred from the lower nibble in the last math operation.

* **Carry Flag** `C`, this bit is set if a carry occurred from the last math operation.

#### Implementation, templates in C++

The implementation of all general purpose register can be found in `Reg` class (`cpu/Reg.hpp`). The class is made of  two fields, the first one is a string of size 2 byte (`char` + terminator `\0`) that indicates the name of the register and the second one is the current numerical value of the register. As you can see the value type is `Generic`, defined according to the template up above, this means that I don't want to specify a type at this time, but only when the concrete object is used. More clearly this technique let me write a single class for every size registers (8-bit, 16-it or even 32/64-bit), assigning the concrete type later.

```c++
template <typename Generic>
class Reg{
    
private:
    char name[2];
    Generic value;
...
```

There are also special 16-bit registers like `BC`, `DE` and `HL` that are composed by the shortest 8-bit pair registers; so yes, the first idea is put these ones in `Reg<uint16_t>` like `SP` or `PC`, but doing this we're not ensure that the update of `BC` also update the conterparts `B` and `C`. The final implementation is building a new class that contains pointers (higher and lower) to the class `Reg`. With this `DoubleReg` class I can remap all architecture that use register coposition to create new greater-size registers. 

```c++
template <typename Generic>
class DoubleReg{
    
private:
    char name[3]; // BC or DE or HL
    Reg<Generic> *high;
    Reg<Generic> *low;
    
public:
    DoubleReg(Reg<Generic> *high, Reg<Generic> *low){
...
```

The `DoubleReg` class expose functions to set and get it's inner register, by simply wrap the call to `high` or `low` registers; but what if we try to update our 16-bit `DoubleReg` `BC` with a `uint16_t` value just poped from the stack?

We don't want to have a function with fixed `uint16_t` parameter bacause this breaks the template we just made; the workaround that I have fond is define outside of the class `DoubleReg` some extra `static` function that are specific for the architecture we are building, that handle full size register and propagate the value to inner registers.

```c++
/* Extra function specific for this architecture */
static uint16_t getD(DoubleReg<uint8_t> *dr){
    return ((uint16_t)dr->getHigh() << 8) | ((uint16_t)dr->getLow());
}

static void setD(DoubleReg<uint8_t> *dr, uint16_t dval){
    dr->set((uint8_t)(dval >> 8), (uint8_t)dval);
}
```

The register are defined in the class `Cpu` and are putted inside arrays, `gpregs[]` contains the `uint8_t` (8-bit) registers and `dregs[]` contains the 16-bit registers using `DoubleReg` class as explained before.

```c++
Reg<uint8_t> gpregs[N_REGS]; /* [ F, A, B, C, D, E, H, L, S, P, I, X ] */
DoubleReg<uint8_t> dregs[N_DREGS]; 	/* [ BC, DE, HL, SP, IX(PC) ] */
...
gpregs[0] = Reg<uint8_t>(FLAG_DEFAULT, REG_NAME[0]); /* F */
gpregs[1] = Reg<uint8_t>(GPR_DEFAULT, REG_NAME[1]);  /* A */
...
dregs[0] = DoubleReg<uint8_t>(&gpregs[2], &gpregs[3]); /* BC */
dregs[1] = DoubleReg<uint8_t>(&gpregs[4], &gpregs[5]); /* DE */
...
```

### Input/Output 

_CHIP9_ processor have some I/O peripheral and method to comunicate to them:

* **Output** text screen that can handle ASCII characters and according to the manual it should be used only for debbugging purpose.
* **Output** grapich display capabilities with a pixels screen 128x64.
* **Input** joystick with direction-pad that uses memory mapped I/O to comunicate with the CPU. 

The processor has full Serial I/O capabilities, the ISA indicate a couple of instructions dedicated to Serial I/O: `SIN` that takes the 8-bit value in the console input and store it into `A` register and `SOUT` that print in the console the content of register `A` interpreted as _ASCII_ value.

There is also another way to comunicate with external world: the grapichal display. The processor's ISA indicate two instructions: `CLRSCR` that turn every pixel on the screen to a lower state (switched off) and the `DRAW` instruction that print the content of register `A` on the screen at the signed X coordinate stored in register `C` and at the signed Y coordinate stored in register `B`.

The only way to give input to the _CHIP9_ processor is trought the joystick, as said before it's composed by arrows  `←` `→` `↓` `↑` and `A`, `B`, `START` and `SELECT` buttons. By following the manual, when the user press a button a special byte is set in memory; this technique that act directly on memory fixed location is called _MMIO_ (memory mapped input/output), the memory address that the CPU finds this information is `0xF000`. The program that is being executed may read from this byte in order to get input information. Each bit in this byte is set only when the corresponding button is being pressed. Otherwise, the bit will be `0`.

|  7   |  6   |  5   |  4   |  3   |  2   |    1     |    0    |
| :--: | :--: | :--: | :--: | :--: | :--: | :------: | :-----: |
| `↑`  | `←`  | `↓`  | `→`  | `A`  | `B`  | `SELECT` | `START` |

#### Implementation, little dive into SDL

The output ASCII screen has been developped by redirecting all the output byte into the console, so every call to assembly `SOUT` simply print the character in register `A` like this: 

```c++
static void sout(Instruction *i){ printf("%c", ...registerA...); }
```

The real pixel screen as been implemented like _ModelView_ pattern, the Screen class models the real data with a matrix of 1-bit Pixels and another layer placed takes that data and perform the output within a graphical library.

```c++
// Pixel class has been created for optimization by setting every uint8_t pixel to size 1-bit
class Pixel{
private:
    uint8_t pixel:1; // old school C-like packing
public:
    Pixel(){ pixel = 0; }
    void setPixel(uint8_t v){ pixel = v; }
    uint8_t getPixel(){ return pixel; }
};

class Screen{
private:
    Pixel screen[Y][X];
public:
    Screen();
    void clear();
    void setSegment(uint8_t val, uint8_t x, uint8_t y);
    uint8_t getPixel(int y, int x);
};
```

After some reserch on the web I found an easy-to-use library for grapich and multimedia in C++ called _SDL_ (Simple Directmedia Layer) available for Mac, Windows and Linux; the library has been installed through Xcode framework manager. The integration with _CHIP9_ was not easy because SDL has been implemented when all the functionality has been already consolidated. The main grapichal library cycle are:

```c++
while(application.isRunning()){
		handleEvents();
    update();
   	render();
}
```

There is polling cycle that continuously execute 3 functions until the application is running: first it checks input given to the application `handleUpdate()`, secondly the application `update()` it's internal data (maybe according to the user input) and lastly it's `render()` all the data that has been changed. The real implementation it's a little bit different bacause the screen specification indicate that the refresh rate is `60Hz` this means that we want `60 ` render calls for every seconds, I fix the classical cycle by inserting the timer below. 

```c++
double t = 20000; // Time for screen refresh
while(gscreen.running()){
		chip9.cycle(); // Here the CHIP9 CPU do a single cycle fetch-decode-execute
    duration = ( std::clock() - start );
		if(duration - t > 0){ // Every delta-time the screen is update
    		start = std::clock();
        gscreen.handleEvents(); // Here some event-oriented programming
        gscreen.update();
        gscreen.render();
    }
}
```

**Note:** the joystick input as not been implemented for now, this means that the instruction opcode is catched like other instruction but it only print a debug text to the console _function not implemented for now_. With SDL library this can be done in an easy way, because the `handleEvents()` function alreay manage input with event oriented programming. Obviously the joystick implementation is not needed to run the rom included, it's a extra feature included for future updates.

### Instruction and ISA

The logic function of any kind of data processing system is the ability to execute program steps; but even more, the ability to evaluate conditions and select alternative program steps on the basis of those conditions. _CHIP9_ processor has multiple instructions for branching as well as function calling through the use of `CALL` and `RET` instructions.

Like every processors _CHIP9_ have it's own _Instruction Set Architecture_ that include `MOV`, `XOR`, `ADD`, `JUMP`, `CALL`, `PUSH`, `RET`, `DRAW` etc. The specification explain more deeply every instruction in the _ISA_, but in the following I want show the very begining of the bootrom (decompiled in _CHIP9_ assembly) as example.

```assembly
// Decompiled assembly bootrom
0000 (22 fe ff) ldx 0xfffe
0003 (76 -- --) xor A
0004 (0f 18 00) jmp 0x0018  
0007 (00 -- --) nop                 
0008 (00 -- --) nop                 
0009 (00 -- --) nop                 
000a (51 -- --) push BC   
000b (79 -- --) mov B, A      
000c (8c -- --) mov A, B    
000d (e9 -- --) mov C, (HL)    
000e (16 -- --) xor C          
000f (9c -- --) mov A, C    
0010 (e1 -- --) sout

// hexdump bootrom
0000000 22 fe ff 76 0f 18 00 00 00 00 51 79 8c e9 16 9c
0000010 e1 74 c8 2f 0c 00 52 0e 41 82 00 90 00 1e 0a 00
...
```

#### Implementation, data driven programming with jump tables

As you can see from the previous section of code there are a lot of difference instructions, compiled as raw byte in the rom file; another observation is that not all instruction have the same length for example some of that needs to read parameters (next bytes). Here comes _data driven programming_, as explained in a interpreted emulator (like this) we want perform different operation based on the data just readed from the code section and that's exately _DDP_. We are in C++, call and external _AWK_ script don't seems to be a good idea, so how can we deal with this? 

For implementing _DDP_ I use jump tables, an old-school technique to change behavior (direct accessing to a function) based on a choosen parameter. In this case I use the _opcode_ to selecting an element of an array of functions, and that functions will be call to execute the operation selected. The next code snipped explain in a little bit better.

```c++
// Cpu.cpp
void execute(){
    /* Wrapper to real instruction (jump table) */
		EXECGATE[ istr.get_opcode() ](&istr);
}

// exec_gate.cpp
static void add(Instruction *i){
    uint16_t res = ((uint16_t)i->get_r2()->getValue()) + i->get_r1()->getValue();
    i->get_r2()->set((uint8_t)res);
    
    setflag_math(i, res); // Set flags
}

static void jmp(Instruction *i){
    i->get_rr1()->set(i->get_imm8_1(), i->get_imm8_0());
}

static void sout(Instruction *i){
    printf("%c", i->get_r1()->getValue());
}

static void init_e( void (*GATE[])(Instruction *i) ){
    
    std::fill_n(GATE, 0x100, &hcf);
    GATE[0x6C] = hcf;           // 6C HCF (HALT Intel)
  	...
		GATE[0x0F] = jmp;           // 0F JMP
  	...
  	GATE[0x04] = add;       		// 04 ADD B
  	GATE[0x14] = add;       		// 14 ADD C
  	...
    GATE[0xE1] = sout;          // E1 SOUT
  	...
}
```

Functions that maps instruction receive as input a instance of `Instruction` class that is a kell-known class that contains parameeters to be used for function execution common for all instruction.

```c++
class Instruction{
private:
    uint8_t opcode;
    Reg<uint8_t> *r1;
    Reg<uint8_t> *r2;
    DoubleReg<uint8_t> *rr1;
    DoubleReg<uint8_t> *rr2;
    Reg<uint8_t> *flag;
    uint8_t immediate8_0;
    uint8_t immediate8_1;
    
    Memory *mem;
    Screen *scr;
...
```

This _DDP_ is not directly applied to text files but is based on _opcodes_ values, the _DDP_ based on the data readed from the rom code segment in memory is the _fetch_ and the _execute_ that are quite similar to the part just explained, so I let the reader inspecting the code for more detail.

## Known issues

When try to compile a template class declared in an header file and implemented in a `.cpp` external file the linker run into an error, that say:

```
[ 66%] Linking CXX executable Chip9
Undefined symbols for architecture x86_64:
  "Reg<unsigned char>::print()", referenced from:
      _main in main.cpp.o
  "Reg<unsigned char>::Reg(unsigned char, char*)", referenced from:
      _main in main.cpp.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

The only way I found to working around is place the template class in a `.cpp` file instaeand of `.hpp/.h` and it's implementation `.cpp`. After some reserch about this error I found an intresting answer from [stackoverflow](https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c) with a funny example to explain it:

> The reason is templates cannot be compiled. Think of functions as cookies, and the compiler is an oven.
>
> Templates are only a cookie cutter, because they don't know what type of cookie they are. It only tells the compiler how to make the function when given a type, but in itself, it can't be used because there is no concrete type being operated on. You can't cook a cookie cutter. Only when you have the tasty cookie dough ready (i.e., given the compiler the dough [type]) can you cut the cookie and cook it.
>
> Likewise, only when you actually use the template with a certain type can the compiler generate the actual function, and compile it. It can't do this, however, if the template definition is missing. You have to move it into the header file, so the caller of the function can make the cookie.

## Conlusion

Generic programming help for some interesting reason, I can write once and reuse the code for contains different datatypes, but in this kind of application (low level project) is a bit forced because sometimes I need directly access to bytes and also I need controls on datatypes for handling registers.

In conclusion I not only coded a strange emulator, but I also found the flag: **X-MAS{m0re_l1ke_l0ve_4t_l1ght}**.

### Impovements

The function selected and executed thrught opcodes can be remapped directelly with native code (asssembly), this whould be better in terms of perfomance.

For now memory is now mapped in the stack throught an `uint8_t array[0x10000]`, this isn't the best choice because the stack grows enormously and this can be a problem for a normal program, so is better to call `malloc()` or `mmap()`.
