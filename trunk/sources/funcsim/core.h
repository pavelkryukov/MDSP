/**
 * core.h - Header of Core class which defines
 * fields and methods used to run the simulator
 * @author Pavel Zaichenkov
 * Copyright 2009 MDSP team
 */

#ifndef CORE_H
#define CORE_H

#include <cassert>
#include <fstream>
#include "types.h"

class MemoryModel;
class RegisterFileModel;
class Flags;

using namespace std;
/**
 * Class of simulator's core description
 */
class Core
{
    hostUInt16 pc; // 16-bit program counter
    MemoryModel* memory;
    RegisterFileModel* rf;
    Flags* flags;
public:
    Core();

    /* Get methods */
    inline hostUInt16 GetPC() { return this->pc; }
    inline MemoryModel* GetMemory() { return this->memory; }
    inline RegisterFileModel* GetRF() { return this->rf; }
    inline Flags* GetFlags() { return this->flags; }
    inline hostUInt32 GetIP() { return 0x0000000A + this->pc; }

    void init( hostUInt16 start_pc);
    int loadBinary ( ifstream& input);
    void run();

};

#endif /* CORE_H */
