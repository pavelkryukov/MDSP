/**
 * main.cpp
 *
 * Simmy launcher
 *
 * @author Pavel Kryukov
 * Copyright 2012 MDSP team
*/

#include <simmy/simmy.h>

int main(int ac, char *av[]) {
    const unsigned char program[] =
        {0x84, 0x0C, 0x01, 0x0A, 0x00, // mov r1 1x000A
         0x44, 0x00, 0x02, 0x00, 0x00, // not r2
         0x01, 0x08, 0x01, 0x02, 0x00, // and r1 r2
         0x02, 0x08, 0x01, 0x02, 0x00, // or  r1 r2
         0x03, 0x08, 0x01, 0x01, 0x00, // xor r1 r1
         0x82, 0x0C, 0x01, 0x10, 0x00, // add r1 1x0010
         0x82, 0x08, 0x01, 0x01, 0x00, // add r1 r1
         0x83, 0x0C, 0x03, 0x00, 0xff, // sub r3 1x00FF
         0x84, 0x0C, 0x0F, 0x0A, 0x00, // mov r15 1x000A
         0x81, 0x0C, 0x0F, 0x10, 0x00, // mul r15 1x0010
         0x80, 0x08, 0x0F, 0x01, 0x00, // div r15 r1
         0xC1, 0x00, 0x0A, 0x00, 0x00, // inc r10
         0xC0, 0x00, 0x0B, 0x00, 0x00, // dec r11
         0xC2, 0x0C, 0x0A, 0x00, 0x00, // ssgn 1, r10
         0xC3, 0x00, 0x0B, 0x00, 0x00, // isgn r11
         0xC2, 0x00, 0x0A, 0x00, 0x00, // ssgn 0, r10
        };

    Simmy::Simmy* simulator = new Simmy::Simmy(program);
    simulator->execute(sizeof(program)/(5*sizeof(program[0])));
    delete simulator;

    return 0;
}