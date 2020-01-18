# CHIP9 Emu
_Project developped for Advanced Computer Programming exam @ Unimi_


Based on X-MAS CTF 2019 chall, CHIP9 is a 8-bit CPU with 64Kb of main memory (quite similar to Intel 8080 / Z80). CHIP9-Emu is an emulator for the architecture described in the chall specification.

## About challenge
> I found an old CHIP9 console in the attic and a cartridge with a program. Unfortunately the motherboard is gone and the console doesn't turn on anymore. The good news is that I also found the developer's manual, can you understand something more about it?

There are also 3 attachments provided: a PDF with the CPU design specification and 2 compiled program (hex byte): _bootrom_ and _rom_.

## Emulator

The emulator for CHIP9 console is developped with Data Driven Programming, Object Orientation and Generic Programming.

##Architecture design
For understandng and design a stable, strong and reusable architecture we need to know specificatelly ho w areal work CPU works. 
Every CPU (Von Newman based) has it's own register divided in :
* Program counter (PC, IX in my arch), indicating the address of the current instruction to be executed by teh CPU.
*  Stack pointer (SP), etc...

Every CPU register have a well known size (eg. 32/64-bit), maybe a bigger register can be composed by other register (eg. in Intel EAX is composed by AX, AH and AL). The registers are the only data that the CPU can manipulate (change it's state).

In real world CPU can manipulate other components like L1/2... cache, but in this case only register can be manipulated.

Every CPU have it's own primary memory (basicaly the RAM) this memory have a size usually quite big and is there the programs executed push all data needed. The CPU cannot direct manipulate the memory but it can only load and store data. The only way to manipulate data in memory is push that data in a register modify that register and put it back with a store instruction.

For this project CHIP9 CPU need a 64K of RAM, addressed with a 16-bit index. The granularity of the RAM is byte so we can read 8-bit integer.
I designed the RAM as an uint8_t array of size 0x10000 (64K).

**image of EAX, AX, AH, AL**

innanzitutto io non ho accesso come porgramma alla cache giusto?
e poi perché la scelta della memoria condivisa?
