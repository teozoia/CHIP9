0000 (22 fe ff) LDX 0xfffe
0003 (76 -- --) XOR A
0004 (0f 18 00) JMP 0x0018  
0007 (00 -- --) NOP                 
0008 (00 -- --) NOP                 
0009 (00 -- --) NOP                 
000a (51 -- --) PUSH BC   
000b (79 -- --) MOV B, A      
000c (8c -- --) MOV A, B    
000d (e9 -- --) MOV C, (HL)    
000e (16 -- --) XOR C          
000f (9c -- --) MOV A, C    
0010 (e1 -- --) SOUT        
0011 (74 -- --) ADD A          
0012 (c8 -- --) INX HL         
0013 (2f 0c 00) JMPNZ 0x000c 
0016 (52 -- --) POP BC             
0017 (0e -- --) RET                 
0018 (41 82 00) LDX 0x0082   
001b (90 00 --) LDI 0x00 
001d (1e 0a 00) CALL 0x000a  
0020 (f0 -- --) CLRSCR
0021 (41 a0 00) LDX HL, 0x00a0
0024 (20 05 --) LDI B, 0x05
0026 (30 20 --) LDI C, 0x20
0028 (ec -- --) MOV A, (HL)
0029 (c8 -- --) INX HL
002a (f1 -- --) DRAW
002b (00 -- --) NOP
002c (90 08 --) LDI A, 0x08
002e (14 -- --) ADD C
002f (90 ff --) LDI A, 0xff
0031 (93 -- --) ADDX DE
0032 (00 -- --) NOP
0033 (00 -- --) NOP 
0034 (00 -- --) NOP
0035 (90 5b --) LDI A, 0x5b
0037 (96 -- --) CMP C
0038 (3f 28 00) JMPCC-N 0x0028
003b (03 -- --) INC B
003c (90 3a --) LDI A, 0x3a
003e (86 -- --) CMP B
003f (2f 26 00) JMPCC-NZ 0x0026
0042 (0f 4e 00) JMP 0x004e

...

004d (6c -- --) HCF 
004e (90 0f 00) LDI A, 0x0f
0050 (21 0f 10) LDX BC, 0x100f
0053 (df 03 --) NJMPCC-NN 0x03 ;0x0058
0055 ... 
                      
...       
                               
0058 (0f 4c 02) JMP 0x024c           

...

00a0 (00) NOP ;ASCII art duck
00a1 (00) NOP
00a2 (00) NOP
00a3 (38) SETFLAG N, 1
00a4 (3C) MOV (HL), E
00a5 (00) NOP
00a6 (00) NOP
00a7 (00) NOP

...

024c (41 5d 00) LDX HL, 0x005d
024f (90 ab --) LDI A, 0xab
0251 (1e 0a 00) CALL 0x000a
0254 (90 0f --) LDI A, 0x0f
0256 (96 -- --) CMP C
0257 (af 03 --) NJMPCC-Z 0x03 ;0x025c

...

025c (91 -- --) PUSH C
025d (91 -- --) PUSH C
025e (30 22 --) LDI C, 0x22
0260 (92 -- --) POP C
0261 (00 -- --) NOP
0262 (96 -- --) CMP C
0263 (af 03 --) NJMPCC-Z 0x03 ;0x0268

...

0268 (00 -- --) NOP
0269 (00 -- --) NOP
026a (1f 97 02) JMPCC-Z 0x0297

...

0297 (90 1c --) LDI A, 0x1c
0299 (00 -- --) NOP
029a (00 -- --) NOP
029b (94 -- --) SUB C
029c (cf 09 --) NJMPCC-N 0x09 ;0x02a7
029e (1e 0a 00) CALL 0x000a
02a1 (1E 45 00) CALL 0x0045
02a4 (0F 9E 02) JMP 0x029e
02a7 (00 -- --) NOP
02a8 (00 -- --) NOP
02a9 (a7 02 --) ADDI A 0x02

029e ...







