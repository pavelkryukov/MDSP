/**
* operation.h - Header of Operation class,
* which defines an instruction fields
* Copyright 2009 MDSP team
*/

#ifndef OPERATION_H
#define OPERATION_H

#include <iostream>
#include <cassert>
#include "types.h"
#include "memory.h"

using namespace std;

/**
* Class of operation description
*/
class Operation
{
    hostUInt32 instr_word;

    OperType type;
    OperCode opcode0, opcode1, opcode2; // all 3 opcodes are needed for ALU only

    /* bit fields are used for memory saving */
    hostUInt8 sd:2; // S/D field
    hostUInt8 am:3; // addressing mode field
    hostUInt16 imm10:10, imm16;
    hostUInt8 rs1:5, rs2:5, rd:5;

    /* set operation in binary form from memory block */
    void setInstrWord( MemVal* mem_value);

public:
    Operation() {};

    /* Get methods */
    inline OperType getType() { return this->type; }
    inline OperCode getOpcode( unsigned num)
    {
        switch( num)
        {
            case 0:
                return this->opcode0;
            case 1:
                return this->opcode1;
            case 2:
                return this->opcode2;
            default:
                cout << "Illegal operation code number\n";
                assert( 0);
        }
    }
    inline hostUInt8 getAM() { return this->am; }
    inline hostUInt8 getSD() { return this->sd; }
    inline hostUInt16 getImm10() { return this->imm10; }
    inline hostUInt16 getImm16() { return this->imm16; }
    inline hostUInt8 getSReg1() { return this->rs1; }
    inline hostUInt8 getSReg2() { return this->rs2; }
    inline hostUInt8 getDReg() { return this->rd; }
    
    /* Set methods */
    inline void setType( OperType type) { this->type = type; }
    inline void setOpcode( unsigned num, OperCode opcode)
    {
        switch( num)
        {
            case 0:
                this->opcode0 = opcode;
            case 1:
                this->opcode1 = opcode;
            case 2:
                this->opcode2 = opcode;
            default:
                cout << "Illegal operation code number\n";
                assert(0);
        }
    }
    inline void setSD( hostUInt8 sd) { this->sd = sd; }
    inline void setAM( hostUInt8 am) { this->am = am; }
    inline void setImm10( hostUInt16 imm10) { this->imm10 = imm10; }
    inline void setImm16( hostUInt16 imm16) { this->imm16 = imm16; }
    inline void setSReg1( hostUInt8 rs1) { this->rs1 = rs1; }
    inline void setSReg2( hostUInt8 rs2) { this->rs2 = rs2; }
    inline void setDReg( hostUInt8 rd) { this->rd = rd; }

    inline void clear()
    {
        this->instr_word = 0;
        this->type = NO_TYPE;
        this->opcode0 = this->opcode1 = this->opcode2 = NOP;
        this->sd = this->am = 0;
        this->imm10 = this->imm16 = 0;
        this->rs1 = this->rs2 = this->rd = 0;
    }

    /* Set the operation */
    void set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
              hostUInt8 sd, hostUInt8 am, 
              hostUInt16 imm10, hostUInt16 imm16,
              hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd);
    
    void set( OperType type, OperCode opcode0, 
              hostUInt8 sd, hostUInt16 imm16, 
              hostUInt8 rs1, hostUInt8 rd);

    void set( OperType type, OperCode opcode0, OperCode opcode1, OperCode opcode2,
              hostUInt8 am, hostUInt16 imm10, 
              hostUInt8 rs1, hostUInt8 rs2, hostUInt8 rd);

    void set( OperType type, OperCode opcode0,
              hostUInt8 sd, hostUInt16 imm16, 
              hostUInt8 rd);

    /* Encode / decode the operation */
    MemVal* encode();
    void decode( MemVal* mem_value);

    /* Execute the operation */
    void execute();
    void executeMove();
    void executeALU();
    void executePFlow();

    void dump();
};

#endif