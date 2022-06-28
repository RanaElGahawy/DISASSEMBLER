#include "compressed.h"
#include <iostream>
#include <string>
#include <cstring>
#include <istream>
#include <bits/stdc++.h>

using namespace std;

string CLW (unsigned int ComInsWord)  // compressed lw
{
    string AssemblyInstruction;
    unsigned int rd, rs, offset;
    rd = (ComInsWord >> 2 ) & 0x0003;
    rs = (ComInsWord >> 7 ) & 0x0007;
    offset = ((ComInsWord >> 6)|((ComInsWord >> 10) << 1)|((ComInsWord >> 5 ) << 4)) << 2;  // check offset calculations

    AssemblyInstruction = "lw\tx" + to_string(rd) + ", " + to_string(offset) + "(x" + to_string(rs) + ")\n";
//    cout << "lw\tx" << rd << ", " << offset << "(x" << rs << ")\n"; //lw x!, num(x!)
    return AssemblyInstruction;
}

string CSW (unsigned int ComInsWord)  // compressed sw
{
    string AssemblyInstruction;
    unsigned int rs1, rs2, offset;
    rs2 = (ComInsWord >> 2 ) & 0x0003;
    rs1 = (ComInsWord >> 7 ) & 0x0007;
    offset = ((ComInsWord >> 6)|((ComInsWord >> 10) << 1)|((ComInsWord >> 5 ) << 4)) << 2;
    AssemblyInstruction = "sw\tx" + to_string(rs2) + ", " + to_string (offset) + "(x" + to_string(rs1) + ")\n";
//    cout << "sw\t" << "x" << rs2 << ", " << offset << "(x" << rs1 << ")\n";   // sw x!, num(x!)
    return AssemblyInstruction;
}

string QuadrantZero (unsigned int ComInsWord) // opcode zero
{
    unsigned int fun3;

    fun3 = (ComInsWord >> 13) & 0x0007;

    switch (fun3)
    {
        case 2:
        {
            return CLW(ComInsWord);
            break;
        }
        case 6:
        {
            return CSW(ComInsWord);
            break;
        }
        default:
        {
            return "Unsupported Instruction.\n";
            break;
        }

    }

}


/////////////////////////////////////////////////////////////////////////

string CSLLI (unsigned int ComInsWord)    //compressed shoft ledt logical (immediate)
{
    string AssemblyInstruction;
    unsigned int rd, Imm;
    rd = (ComInsWord >> 7 ) & 0x1F;
    Imm = ((ComInsWord >> 2) & 0x001F) | (((ComInsWord >> 12) & 0x0001) << 5);
    if (!rd)
//        cout << "Error in the instruction!!";
    AssemblyInstruction = "Error in the instruction!!";
    else
//        cout << "slli\tx" << rd << ", x" << rd << ", " << Imm << endl;  // slli x!, x!, Imm
    AssemblyInstruction = "slli\tx" + to_string(rd) + ", x" + to_string(rd) + ", " + to_string(Imm) + "\n";

    return AssemblyInstruction;
}


string CJR_MV (unsigned int ComInsWord)
{
    unsigned int rs, rd;
    string AssemblyInstruction;

    rs = (ComInsWord >> 2) & 0x1F;
    rd = (ComInsWord >> 7) & 0x1F;

    if (rs)
    {
        //  MV
//        cout << "add\tx" << rd << ", x0, x" << rs << endl;  //  add rd, x0, rs
        AssemblyInstruction = "add\tx" + to_string(rd) + ", x0, x" + to_string(rs) + "\n";
    }
    else
    {
        //  JR
//       cout << "jalr\tx0, x" << rd << ", 0\n"; //  jalr x0, rs, 0
    AssemblyInstruction = "jalr\tx0, x" + to_string(rd) + ", 0\n";
    }

    return AssemblyInstruction;
}


string CLWSP (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd, offset;
    rd = (ComInsWord >> 7 ) & 0x1F;
    offset = (((ComInsWord >> 4) & 0x0007)|(((ComInsWord >> 12) & 0x1) << 3)|(((ComInsWord >> 2 ) & 0x3) << 4)) << 2;
//    cout << "lw\tx" << rd << ", " << offset << "(x2)\n"; //lw x!, num(x2)
    AssemblyInstruction = "lw\tx" + to_string(rd) + ", " + to_string(offset) + "(x2)\n";

    return AssemblyInstruction;
}


string CSWSP (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rs2, offset;
    rs2 = (ComInsWord >> 2 ) & 0x1F;
    offset = (((ComInsWord >> 9) & 0x0007) |(((ComInsWord >> 7) & 0x3) << 4)) << 2;
//   cout << "sw\t" << "x" << rs2 << ", " << offset << "(x2)\n";   // sw x!, num(x!)
    AssemblyInstruction = "sw\tx" + to_string(rs2) + ", " + to_string(offset) + "(x2)\n";
    return AssemblyInstruction;

}

string CJALR_AND (unsigned int ComInsWord)
{
    unsigned int rs, rd;
    string AssemblyInstruction;

    rs = (ComInsWord >> 2) & 0x1F;
    rd = (ComInsWord >> 7) & 0x1F;

    if (rs)
    {
        //  MV
//        cout << "add\tx" << rd << ", x" << rd << ", x" << rs << endl;  //  add rd, rd, rs
    AssemblyInstruction = "add\tx" + to_string(rd) + ", x" + to_string(rd) + ", x" + to_string(rs) + "\n";
    }
    else
    {
        //  JR
//        cout << "jalr\tx1, x" << rd << ", 0\n"; //  jalr x1, rd, 0
    AssemblyInstruction = "jalr\tx1, x" + to_string(rd) + ", 0\n";
    }

    return AssemblyInstruction;
}

string QuadrantTwo (unsigned int ComInsWord) // opcode two
{
    unsigned int fun3, Bit12;

    fun3 = (ComInsWord >> 13) & 0x0007;

    switch (fun3)
    {
        case 0:
        {
            return CSLLI(ComInsWord);
            break;
        }
        case 2:
        {
            return CLWSP(ComInsWord);
            break;
        }
        case 4:
        {
            Bit12 = (ComInsWord >>12) & 0x0001;

            if (Bit12)
                return CJALR_ADD(ComInsWord);
            else
                return CJR_MV(ComInsWord);
            break;
        }

        case 6:
        {
            return CSWSP(ComInsWord);
            break;
        }
        default:
        {
//            cout << "Unsupported Instruction.\n";
            return "Unsupported Instruction.\n";
            break;
        }

    }

}

///////////////////////////////////////////////////////////////////////

// how to get negative offset

string CJ (unsigned int ComInsWord)
{
    int offset;
    string AssemblyInstruction;

    offset = (((ComInsWord >> 3 ) & 0x0007 ) | ((ComInsWord >> 11) & 0x0001) | ((ComInsWord >> 2) & 0x0001) | ((ComInsWord >> 7) & 0x0001) | ((ComInsWord >> 6) & 0x0001) | ((ComInsWord >> 9) & 0x0003) | ((ComInsWord >> 8 ) & 0x0001) | ((ComInsWord >> 12) & 0x0001));  // shift by 1 or not ?
//    cout << "jal\tx0, " << hex << offset;
    stringstream ss;
    ss << "jal\tx0, " << hex << offset;
    AssemblyInstruction = ss.str();

    return AssemblyInstruction;
}


string CJAL (unsigned int ComInsWord)
{
    int offset;
    string AssemblyInstruction;
    
    offset = (((ComInsWord >> 3 ) & 0x0007 ) | ((ComInsWord >> 11) & 0x0001) | ((ComInsWord >> 2) & 0x0001) | ((ComInsWord >> 7) & 0x0001) | ((ComInsWord >> 6) & 0x0001) | ((ComInsWord >> 9) & 0x0003) | ((ComInsWord >> 8 ) & 0x0001) | ((ComInsWord >> 12) & 0x0001));  // shift by 1 or not ?
//    cout << "jal\tx1, " << hex << offset;
    stringstream ss;
    ss << "jal\tx1, " << hex << offset;
    AssemblyInstruction = ss.str();

    return AssemblyInstruction;
}


string QuadrantOne (unsigned int ComInsWord) // opcode two
{

}
