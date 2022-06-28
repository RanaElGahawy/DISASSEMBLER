#include "compressed.h"
#include <iostream>
using namespace std;

void CLW (unsigned int ComInsWord)  // compressed lw
{
    string AssemblyInstruction;
    unsigned int rd, rs, offset;
    rd = (ComInsWord >> 2 ) & 0x0003;
    rs = (ComInsWord >> 7 ) & 0x0007;
    offset = ((ComInsWord >> 6)|((ComInsWord >> 10) << 1)|((ComInsWord >> 5 ) << 4)) << 2;  // check offset calculations

    AssemblyInstruction = "lw\tx" + to_string(rd) + ", " + to_string(offset) + "(x" + to_string(rs) + ")\n";
    cout << "lw\tx" << rd << ", " << offset << "(x" << rs << ")\n"; //lw x!, num(x!)

}

void CSW (unsigned int ComInsWord)  // compressed sw
{
    unsigned int rs1, rs2, offset;
    rs2 = (ComInsWord >> 2 ) & 0x0003;
    rs1 = (ComInsWord >> 7 ) & 0x0007;
    offset = ((ComInsWord >> 6)|((ComInsWord >> 10) << 1)|((ComInsWord >> 5 ) << 4)) << 2;

    cout << "sw\t" << "x" << rs2 << ", " << offset << "(x" << rs1 << ")\n";   // sw x!, num(x!)
}

void QuadrantZero (unsigned int ComInsWord) // opcode zero
{
    unsigned int fun3;

    fun3 = (ComInsWord >> 13) & 0x0007;

    switch (fun3)
    {
        case 2:
        {
            CLW(ComInsWord);
            break;
        }
        case 6:
        {
            CSW(ComInsWord);
            break;
        }
        default:
        {
            cout << "Unsupported Instruction.\n";
            break;
        }

    }

}


/////////////////////////////////////////////////////////////////////////

void CSLLI (unsigned int ComInsWord)    //compressed shoft ledt logical (immediate)
{
    unsigned int rd, Imm;

    rd = (ComInsWord >> 7 ) & 0x1F;
    Imm = ((ComInsWord >> 2) & 0x001F) | (((ComInsWord >> 12) & 0x0001) << 5);
    if (!rd)
        cout << "Error in the instruction!!";
    else
        cout << "slli\tx" << rd << ", x" << rd << ", " << Imm << endl;  // slli x!, x!, Imm

}


void CJR_MV (unsigned int ComInsWord)
{
    unsigned int rs, rd;

    rs = (ComInsWord >> 2) & 0x1F;
    rd = (ComInsWord >> 7) & 0x1F;

    if (rs)
    {
        //  MV
        cout << "add\tx" << rd << ", x0, x" << rs << endl;  //  add rd, x0, rs
    }
    else
    {
        //  JR
        cout << "jalr\tx0, x" << rd << ", 0\n"; //  jalr x0, rs, 0
    }

}


void CLWSP (unsigned int ComInsWord)
{
    unsigned int rd, offset;
    rd = (ComInsWord >> 7 ) & 0x1F;
    offset = (((ComInsWord >> 4) & 0x0007)|(((ComInsWord >> 12) & 0x1) << 3)|(((ComInsWord >> 2 ) & 0x3) << 4)) << 2;
    cout << "lw\tx" << rd << ", " << offset << "(x2)\n"; //lw x!, num(x2)
}
void CSWSP (unsigned int ComInsWord)
{
    unsigned int rs2, offset;
    rs2 = (ComInsWord >> 2 ) & 0x1F;
    offset = (((ComInsWord >> 9) & 0x0007) |(((ComInsWord >> 7) & 0x3) << 4)) << 2;
    cout << "sw\t" << "x" << rs2 << ", " << offset << "(x2)\n";   // sw x!, num(x!)

}

void CJALR_AND (unsigned int ComInsWord)
{
    unsigned int rs, rd;

    rs = (ComInsWord >> 2) & 0x1F;
    rd = (ComInsWord >> 7) & 0x1F;

    if (rs)
    {
        //  MV
        cout << "add\tx" << rd << ", x" << rd << ", x" << rs << endl;  //  add rd, rd, rs
    }
    else
    {
        //  JR
        cout << "jalr\tx1, x" << rd << ", 0\n"; //  jalr x1, rd, 0

    }
}

void QuadrantTwo (unsigned int ComInsWord) // opcode two
{
    unsigned int fun3, Bit12;

    fun3 = (ComInsWord >> 13) & 0x0007;

    switch (fun3)
    {
        case 0:
        {
            CSLLI(ComInsWord);
            break;
        }
        case 2:
        {
            CLWSP(ComInsWord);
            break;
        }
        case 4:
        {
            Bit12 = (ComInsWord >>12) & 0x0001;

            if (Bit12)
                CJALR_ADD(ComInsWord);
            else
                CJR_MV(ComInsWord);
            break;
        }

        case 6:
        {
            CSWSP(ComInsWord);
            break;
        }
        default:
        {
            cout << "Unsupported Instruction.\n";
            break;
        }

    }

}

///////////////////////////////////////////////////////////////////////

// how to get negative offset

void CJ (unsigned int ComInsWord)
{
    unsigned int offset;
    
    offset = (((ComInsWord >> 3 ) & 0x0007 ) | ((ComInsWord >> 11) & 0x0001) | ((ComInsWord >> 2) & 0x0001) | ((ComInsWord >> 7) & 0x0001) | ((ComInsWord >> 6) & 0x0001) | ((ComInsWord >> 9) & 0x0003) | ((ComInsWord >> 8 ) & 0x0001) | ((ComInsWord >> 12) & 0x0001));  // shift by 1 or not ?
    cout << "jal\tx0, " << hex << offset;
}


void CJAL (unsigned int ComInsWord)
{
    unsigned int offset;
    
    offset = (((ComInsWord >> 3 ) & 0x0007 ) | ((ComInsWord >> 11) & 0x0001) | ((ComInsWord >> 2) & 0x0001) | ((ComInsWord >> 7) & 0x0001) | ((ComInsWord >> 6) & 0x0001) | ((ComInsWord >> 9) & 0x0003) | ((ComInsWord >> 8 ) & 0x0001) | ((ComInsWord >> 12) & 0x0001));  // shift by 1 or not ?
    cout << "jal\tx1, " << hex << offset;
}


void QuadrantOne (unsigned int ComInsWord) // opcode two
{

}
