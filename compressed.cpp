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

string CADDI4SPN (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd, Imm;

    rd = (ComInsWord >> 2) & 0x0007;
    Imm = (((ComInsWord >> 6) & 0x0001) | (((ComInsWord >> 5) & 0x0001) << 1) | (((ComInsWord >> 11) & 0x0003) << 2) | (((ComInsWord >> 7) & 0x000F) << 4));

    if (!Imm) return "Error loading Instruction\n";
    AssemblyInstruction = "addi\tx" + to_string(rd) + ", x2, " + to_string(Imm) + "\n";
    
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

    return "errorr\n";

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

string CJALR_ADD_EBREAK (unsigned int ComInsWord)
{
    unsigned int rs, rd;
    string AssemblyInstruction;

    rs = (ComInsWord >> 2) & 0x1F;
    rd = (ComInsWord >> 7) & 0x1F;

    if (rs == 0 & rd ==0)
    {
    AssemblyInstruction = "ebreak\n";
    }
    else if (rs)
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
                return CJALR_ADD_EBREAK(ComInsWord);
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
    
    return "errorr\n";


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

string CBEQZ (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rs1;
    signed int offset;

    rs1 = (ComInsWord >> 7) & 0x0007;
    offset = (((ComInsWord >> 3) & 0x0003) |(((ComInsWord >> 10) & 0x0003) << 2) | (((ComInsWord >> 2 ) & 0x0001) << 4) | (((ComInsWord >> 5) & 0x0003) << 5) | (((ComInsWord >> 12 ) & 0x0001) << 7));    //not multiplied by 2
    stringstream ss;
    ss << "beq\tx" << to_string(rs1) << ", x0, 0x" << hex << offset; 
    AssemblyInstruction = ss.str();
    return AssemblyInstruction;
}

string CBNEZ (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rs1;
    signed int offset;

    rs1 = (ComInsWord >> 7) & 0x0007;
    offset = (((ComInsWord >> 3) & 0x0003) |(((ComInsWord >> 10) & 0x0003) << 2) | (((ComInsWord >> 2 ) & 0x0001) << 4) | (((ComInsWord >> 5) & 0x0003) << 5) | (((ComInsWord >> 12 ) & 0x0001) << 7));    //not multiplied by 2
    stringstream ss;
    ss << "bne\tx" << to_string(rs1) << ", x0, 0x" << hex << offset; 
    AssemblyInstruction = ss.str();
    return AssemblyInstruction;
}

string CLI (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd;
    signed int Imm;

    rd = (ComInsWord >> 7) & 0x001F;

    if(!rd)
    {
        return "Unsupported Instruction!!\n";
    }
   
    Imm = (((ComInsWord >> 2) & 0x000F ) | ((ComInsWord >> 12) & 0x0001));
    AssemblyInstruction = "addi\tx" + to_string(rd) + ", x0, " + to_string(Imm) + "\n";

    return AssemblyInstruction;
}

string CLUI_ADDI16SP (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd;
    signed int Imm;

    rd = (ComInsWord >> 7) & 0x001F;

    if(!rd )
    {
        return "Unsupported Instruction!!\n";
    }
    else if (rd == 2)
    {
        // ADDI16SP
        Imm = (((ComInsWord >> 6) & 0x0001 ) | (((ComInsWord >> 2) & 0x0001) << 1 ) |  (((ComInsWord >> 5) & 0x0001) << 2 ) |  (((ComInsWord >> 3) & 0x0003) << 3 ) |  (((ComInsWord >> 12) & 0x0001) << 5 )) ; // << 4
        AssemblyInstruction = "addi x2, x2, " + to_string(Imm) + "\n";
    }
    else 
    {
        // LUI
        Imm = (((ComInsWord >> 2) & 0x000F ) | ((ComInsWord >> 12) & 0x0001)) << 12;
        AssemblyInstruction = "lui\tx" + to_string(rd) + ", x0, " + to_string(Imm) + "\n";
    }
    return AssemblyInstruction;
}

string CADDI_NOP (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd;
    signed int Imm;

    rd = (ComInsWord >> 7) & 0x001F;
    Imm = (((ComInsWord >> 2) & 0x000F ) | ((ComInsWord >> 12) & 0x0001));
    if ((rd == 0) & (Imm == 0))
    {
        AssemblyInstruction = "addi\tx0, x0, 0\n";
    }
    else
    {
    AssemblyInstruction = "addi\tx" + to_string(rd) + ", x" + to_string(rd) + ", " + to_string(Imm);
    }
    return AssemblyInstruction;

}


string CSRLI_SRAI_ANDI (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd, Imm, fun2;
    signed int ImmAnd;

    Imm = (((ComInsWord >> 2) & 0x1F) | (((ComInsWord >> 12) & 0x1) << 5));
    ImmAnd = (((ComInsWord >> 2) & 0x1F) | (((ComInsWord >> 12) & 0x1) << 5));
    rd = (ComInsWord >> 7) & 0x7;
    fun2 = (ComInsWord >> 12) & 0x3;

    if (fun2 == 0)
    {
        AssemblyInstruction = "srli\tx" + to_string(rd) + ", x" + to_string(rd) + ", " +  to_string(Imm) + "\n";
    }
    else if (fun2 == 1)
    {
        AssemblyInstruction = "srai\tx" + to_string(rd) + ", x" + to_string(rd) + ", " +  to_string(ImmAnd) + "\n";
    }
    else if (fun2 == 2)
    {
        AssemblyInstruction = "andi\tx" + to_string(rd) + ", x" + to_string(rd) + ", " +  to_string(Imm) + "\n";
    }
    else 
        AssemblyInstruction = "Instruction not supported!\n";

    return AssemblyInstruction;
}



string CAND_OR_XOR_SUB (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd, rs, func;
    rd = (ComInsWord >> 7) & 0x7;
    rs = (ComInsWord >> 2) & 0x7;
    func = (ComInsWord >> 5) & 0x3;

    if (func == 0)
    {
        AssemblyInstruction = "sub\tx" + to_string(rd) + ", x" + to_string(rd) + ", x" +  to_string(rs) + "\n";
    }
    else if (func == 1)
    {
        AssemblyInstruction = "xor\tx" + to_string(rd) + ", x" + to_string(rd) + ", x" +  to_string(rs) + "\n";
    }
    else if (func == 2)
    {
        AssemblyInstruction = "or\tx" + to_string(rd) + ", x" + to_string(rd) + ", x" +  to_string(rs) + "\n";
    }
    else if (func == 3)
    {
        AssemblyInstruction = "and\tx" + to_string(rd) + ", x" + to_string(rd) + ", x" +  to_string(rs) + "\n";
    }    
    else 
        AssemblyInstruction = "Instruction not supported!\n";

    return AssemblyInstruction;

}




string QuadrantOne (unsigned int ComInsWord) // opcode two
{
    string AssemblyInstruction;
    unsigned int func, func2;
    func = (ComInsWord >> 13) & 0x7;
    func2 = (ComInsWord >> 12) & 0x3;

    switch (func)
    {
        case 0:
        {
            AssemblyInstruction = CADDI_NOP (ComInsWord);
            break;
        }
        case 1:
        {
            AssemblyInstruction = CJAL (ComInsWord);
            break;
        }
        case 2:
        {
            AssemblyInstruction = CLI (ComInsWord);
            break;            
        }
        case 3:
        {
            AssemblyInstruction = CLUI_ADDI16SP (ComInsWord);
            break;            
        }
        case 4:
        {
            if (func2 == 3)
            {
                AssemblyInstruction = CAND_OR_XOR_SUB (ComInsWord);
            }
            else 
            {
                AssemblyInstruction = CSRLI_SRAI_ANDI (ComInsWord);
            }
            break;            
        }      
        case 5:
        {
            AssemblyInstruction = CJ (ComInsWord);
            break;            
        }  
        case 6:
        {
            AssemblyInstruction = CBEQZ (ComInsWord);
            break;            
        }
        case 7:
        {
            AssemblyInstruction = CBNEZ (ComInsWord);
            break;            
        }
    }

    return AssemblyInstruction;
}
