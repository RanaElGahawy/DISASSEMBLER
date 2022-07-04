#include "compressed.h"
#include <iostream>
#include <string>
#include <cstring>
#include <istream>
using namespace std;

string CLW (unsigned int ComInsWord)  // compressed lw
{
    string AssemblyInstruction;
    unsigned int rd, rs, offset;
    rd = ((ComInsWord >> 2 ) & 0x0007) + 8 ;
    rs = ((ComInsWord >> 7 ) & 0x0007) + 8 ;
    offset = ((((ComInsWord >> 6)& 0x1))|(((ComInsWord >> 10) & 0x7 ) << 1)|(((ComInsWord >> 5 ) &0x1 ) << 4)) *4;  // check offset calculations

    AssemblyInstruction = "lw\t\t\tx" + to_string(rd) + ", " + to_string(offset) + "(x" + to_string(rs) + ")";
//    cout << "lw\tx" << rd << ", " << offset << "(x" << rs << ")\n"; //lw x!, num(x!)
    return AssemblyInstruction;
}

string CSW (unsigned int ComInsWord)  // compressed sw
{
    string AssemblyInstruction;
    unsigned int rs1, rs2, offset;
    rs2 = ((ComInsWord >> 2 ) & 0x0003)+ 8;
    rs1 = ((ComInsWord >> 7 ) & 0x0007)+ 8;
    offset = (((ComInsWord >> 6)& 0x1)|(((ComInsWord >> 10) & 0x7 ) << 1)|(((ComInsWord >> 5 ) &0x1 ) << 4));  // check offset calculations
    AssemblyInstruction = "sw\t\t\tx" + to_string(rs2) + ", " + to_string (offset) + "(x" + to_string(rs1) + ")";
//    cout << "sw\t" << "x" << rs2 << ", " << offset << "(x" << rs1 << ")\n";   // sw x!, num(x!)
    return AssemblyInstruction;
}

string CADDI4SPN (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd, Imm;

    rd = ((ComInsWord >> 2) & 0x0007)+ 8;
    Imm = (((ComInsWord >> 6) & 0x0001) | (((ComInsWord >> 5) & 0x0001) << 1) | (((ComInsWord >> 11) & 0x0003) << 2) | (((ComInsWord >> 7) & 0x000F) << 4))*4;

    if (!Imm) return "Error in offset of ADDI14SPN";
    AssemblyInstruction = "addi\t\tx" + to_string(rd) + ", sp, " + to_string(Imm);
    return AssemblyInstruction;
}

string QuadrantZero (unsigned int ComInsWord) // opcode zero
{
    unsigned int fun3;

    if (ComInsWord == 0) return "Illegal Instructions!";

    fun3 = (ComInsWord >> 13) & 0x0007;

    switch (fun3)
    {
        case 0:
        {
            return CADDI4SPN(ComInsWord);
        }
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
            return "Unsupported Instruction!";
            break;
        }

    }

    return "errorr";

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
    AssemblyInstruction = "Error in loading rd in CSLLI!!";
    else
//        cout << "slli\tx" << rd << ", x" << rd << ", " << Imm << endl;  // slli x!, x!, Imm
    AssemblyInstruction = "slli\t\tx" + to_string(rd) + ", x" + to_string(rd) + ", " + to_string(Imm);

    return AssemblyInstruction;
}


string CJR_MV (unsigned int ComInsWord)
{
    unsigned int rs, rd;
    string AssemblyInstruction;

    rs = ((ComInsWord >> 2) & 0x1F);
    rd = ((ComInsWord >> 7) & 0x1F);

    if (rs)
    {
        //  MV
//        cout << "add\tx" << rd << ", x0, x" << rs << endl;  //  add rd, x0, rs
        AssemblyInstruction = "add\t\t\tx" + to_string(rd) + ", x0, x" + to_string(rs);
    }
    else
    {
        //  JR
//       cout << "jalr\tx0, x" << rd << ", 0\n"; //  jalr x0, rs, 0
    AssemblyInstruction = "jalr\t\tx0, x" + to_string(rd) + ", 0";
    }

    return AssemblyInstruction;
}


string CLWSP (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd, offset;
    rd = ((ComInsWord >> 7 ) & 0x1F);
    offset = (((ComInsWord >> 4) & 0x0007)|(((ComInsWord >> 12) & 0x1) << 3)|(((ComInsWord >> 2 ) & 0x3) << 4))*4; //shift by 2 or not ? x4
//    cout << "lw\tx" << rd << ", " << offset << "(x2)\n"; //lw x!, num(x2)
    AssemblyInstruction = "lw\t\t\tx" + to_string(rd) + ", " + to_string(offset) + "(sp)";

    return AssemblyInstruction;
}


string CSWSP (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rs2, offset;
    rs2 = ((ComInsWord >> 2 ) & 0x1F);
    offset = (((ComInsWord >> 9) & 0x0F) |(((ComInsWord >> 7) & 0x03) << 4))*4; //shift by 2 or not ? x4
//   cout << "sw\t" << "x" << rs2 << ", " << offset << "(x2)\n";   // sw x!, num(x!)
    AssemblyInstruction = "sw\t\t\tx" + to_string(rs2) + ", " + to_string(offset) + "(sp)";
    return AssemblyInstruction;

}

string CJALR_ADD_EBREAK (unsigned int ComInsWord)
{
    unsigned int rs, rd;
    string AssemblyInstruction;

    rs = ((ComInsWord >> 2) & 0x1F);
    rd = ((ComInsWord >> 7) & 0x1F);

    if (rs == 0 & rd ==0)
    {
    AssemblyInstruction = "ebreak";
    }
    else if (rs)
    {
        //  MV
//        cout << "add\tx" << rd << ", x" << rd << ", x" << rs << endl;  //  add rd, rd, rs
    AssemblyInstruction = "add\t\t\tx" + to_string(rd) + ", x" + to_string(rd) + ", x" + to_string(rs);
    }
    else
    {
        //  JR
//        cout << "jalr\tx1, x" << rd << ", 0\n"; //  jalr x1, rd, 0
    AssemblyInstruction = "jalr\t\tx1, x" + to_string(rd) + ", 0";
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
            return "Unsupported Instruction.";
            break;
        }

    }
    
    return "errorr";


}

///////////////////////////////////////////////////////////////////////

// how to get negative offset

string CJ (unsigned int ComInsWord, unsigned int pc, map < unsigned int, string> &Labels)
{
    signed int offset;
    string AssemblyInstruction;
    string Label;
    offset = (((ComInsWord >> 3 ) & 0x0007 )) | (((ComInsWord >> 11) & 0x0001) << 3) | (((ComInsWord >> 2) & 0x0001) << 4)  | (((ComInsWord >> 7) & 0x0001) << 5) | (((ComInsWord >> 6) & 0x0001) << 6) | (((ComInsWord >> 9) & 0x0003) << 7) | (((ComInsWord >> 8 ) & 0x0001) << 9)| (((ComInsWord >> 12) & 0x0001) << 10);  
    if (((ComInsWord >> 12) & 0x0001))
    {
        offset = offset ^ 0x07FF;
        offset = (offset + 1) * (-1) ;
    } 
//    cout << "jal\tx1, " << hex << offset;
    offset = offset * 2 +pc;

    stringstream ss;
    ss << "Label0x" << hex << offset; 
    AssemblyInstruction = "jal\t\t\t," + ss.str();
    Labels[offset] = ss.str();
    return AssemblyInstruction;
}


string CJAL (unsigned int ComInsWord, unsigned int pc, map < unsigned int, string> &Labels)
{
    signed int offset;
    string AssemblyInstruction;

    offset = (((ComInsWord >> 3 ) & 0x0007 )) | (((ComInsWord >> 11) & 0x0001) << 3) | (((ComInsWord >> 2) & 0x0001) << 4)  | (((ComInsWord >> 7) & 0x0001) << 5) | (((ComInsWord >> 6) & 0x0001) << 6) | (((ComInsWord >> 9) & 0x0003) << 7) | (((ComInsWord >> 8 ) & 0x0001) << 9)| (((ComInsWord >> 12) & 0x0001) << 10);  
    if (((ComInsWord >> 12) & 0x0001))
    {
        offset = offset ^ 0x07FF;
        offset = (offset + 1) * (-1) ;
    } 
//    cout << "jal\tx1, " << hex << offset;
    offset = offset * 2 +pc;

    stringstream ss;
    ss << "jal\t\t\tx1, 0x" << hex << offset;
    AssemblyInstruction = ss.str();

    return AssemblyInstruction;
}

string CBEQZ (unsigned int ComInsWord, unsigned int pc, map < unsigned int, string> &Labels)
{
    string AssemblyInstruction;
    unsigned int rs1;
    signed int offset;
    signed int result;

    rs1 = ((ComInsWord >> 7) & 0x0007)+ 8;
    if (((ComInsWord >> 12 ) & 0x0001))
    {
        offset =(((ComInsWord >> 3) & 0x0003) |(((ComInsWord >> 10) & 0x0003) << 2) | (((ComInsWord >> 2 ) & 0x0001) << 4) | (((ComInsWord >> 5) & 0x0003) << 5) | (((ComInsWord >> 12 ) & 0x0001) << 7));    //not multiplied by 2
        offset = offset ^ 0x0ff;
        offset = (offset + 1) * -1;
//        cout << "neg:" << offset << endl << result << endl;
    }
    else 
    {
        offset =(((ComInsWord >> 3) & 0x0003) |(((ComInsWord >> 10) & 0x0003) << 2) | (((ComInsWord >> 2 ) & 0x0001) << 4) | (((ComInsWord >> 5) & 0x0003) << 5) | (((ComInsWord >> 12 ) & 0x0001) << 7));    //not multiplied by 2

    }

    offset = offset*2 + pc;

    stringstream ss;
    ss << "beq\t\tx" << to_string(rs1) << ", x0, 0x" << hex << offset; 
    AssemblyInstruction = ss.str();
    return AssemblyInstruction;
}

string CBNEZ (unsigned int ComInsWord, unsigned int pc, map < unsigned int, string> &Labels )
{
    string AssemblyInstruction;
    unsigned int rs1;
    signed int offset;

    rs1 = ((ComInsWord >> 7) & 0x0007)+ 8;
    if (((ComInsWord >> 12 ) & 0x0001))
    {
        offset =(((ComInsWord >> 3) & 0x0003) |(((ComInsWord >> 10) & 0x0003) << 2) | (((ComInsWord >> 2 ) & 0x0001) << 4) | (((ComInsWord >> 5) & 0x0003) << 5) | (((ComInsWord >> 12 ) & 0x0001) << 7));    //not multiplied by 2
        offset = offset ^ 0x0ff;
        offset = (offset + 1) * -1;
    }
    else 
    {
        offset =(((ComInsWord >> 3) & 0x0003) |(((ComInsWord >> 10) & 0x0003) << 2) | (((ComInsWord >> 2 ) & 0x0001) << 4) | (((ComInsWord >> 5) & 0x0003) << 5) | (((ComInsWord >> 12 ) & 0x0001) << 7));    //not multiplied by 2
    }

    offset = offset*2 + pc;
    stringstream ss;
    ss << "bne\t\tx" << to_string(rs1) << ", x0, 0x" << hex << offset; 
    AssemblyInstruction = ss.str();
    return AssemblyInstruction;
}

string CLI (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd;
    signed int Imm;

    rd = ((ComInsWord >> 7) & 0x001F);

    if(!rd)
    {
        return "Unsupported Instruction!!";
    }
   
    Imm = (((ComInsWord >> 2) & 0x000F ) | ((ComInsWord >> 12) & 0x0001) << 4);
    if (((ComInsWord >> 12) & 0x0001))
    {
        Imm = Imm ^ 0x1f;
        Imm++;
        Imm = Imm * (-1);        
    }
    AssemblyInstruction = "addi\t\tx" + to_string(rd) + ", x0, " + to_string(Imm);

    return AssemblyInstruction;
}

string CLUI_ADDI16SP (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd;
    signed int Imm;

    rd = ((ComInsWord >> 7) & 0x001F);

    if(!rd )
    {
        return "Unsupported Instruction!!";
    }
    else if (rd == 2)
    {
        // ADDI16SP
        Imm = (((ComInsWord >> 6) & 0x0001 ) | (((ComInsWord >> 2) & 0x0001) << 1 ) |  (((ComInsWord >> 5) & 0x0001) << 2 ) |  (((ComInsWord >> 3) & 0x0003) << 3 ) |  (((ComInsWord >> 12) & 0x0001) << 5 )); // << 4
        if ((ComInsWord >> 12) & 0x0001)
        {
            Imm = Imm ^ 0x3f;
            Imm++;
            Imm = Imm * (-1);             
        }

        Imm *= 16;

        AssemblyInstruction = "addi\t\tsp, sp, " + to_string(Imm);
    }
    else 
    {
        // LUI
        Imm = (((ComInsWord >> 2) & 0x001F ) | ((ComInsWord >> 12) & 0x0001) << 5);
        if ((ComInsWord >> 12) & 0x0001)
        {
            Imm = Imm ^ 0x3f;
            Imm++;
            Imm = Imm * (-1);  
        }

        Imm = Imm * 4096;
        AssemblyInstruction = "lui\t\tx" + to_string(rd) + ", x0, " + to_string(Imm);
    }
    return AssemblyInstruction;
}

string CADDI_NOP (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd;
    signed int Imm;

    rd = ((ComInsWord >> 7) & 0x001F);
    Imm = (((ComInsWord >> 2) & 0x000F ) | ((ComInsWord >> 12) & 0x0001) << 4);
    if (((ComInsWord >> 12) & 0x0001))
    {
        Imm = Imm ^ 0x1f;
        Imm++;
        Imm = Imm * (-1);
    }
    if ((rd == 0) & (Imm == 0))
    {
        AssemblyInstruction = "addi\t\tx0, x0, 0";
    }
    else
    {
    AssemblyInstruction = "addi\t\tx" + to_string(rd) + ", x" + to_string(rd) + ", " + to_string(Imm);
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
    rd = ((ComInsWord >> 7) & 0x7)+ 8;
    fun2 = (ComInsWord >> 10) & 0x3;

    if (fun2 == 0)
    {
        AssemblyInstruction = "srli\t\tx" + to_string(rd) + ", x" + to_string(rd) + ", " +  to_string(Imm);
    }
    else if (fun2 == 1)
    {
        AssemblyInstruction = "srai\t\tx" + to_string(rd) + ", x" + to_string(rd) + ", " +  to_string(ImmAnd);
    }
    else if (fun2 == 2)
    {
        if ((ComInsWord >> 12) & 0x1)
        {
            ImmAnd = ImmAnd ^ 0x3f;
            ImmAnd++;
            ImmAnd = ImmAnd * (-1);            
        }
        AssemblyInstruction = "andi\t\tx" + to_string(rd) + ", x" + to_string(rd) + ", " +  to_string(ImmAnd);
    }
    else 
        AssemblyInstruction = "Instruction not supported!";

    return AssemblyInstruction;
}



string CAND_OR_XOR_SUB (unsigned int ComInsWord)
{
    string AssemblyInstruction;
    unsigned int rd, rs, func;
    rd = ((ComInsWord >> 7) & 0x7)+ 8;
    rs = ((ComInsWord >> 2) & 0x7)+ 8;
    func = (ComInsWord >> 5) & 0x3;

    if (func == 0)
    {
        AssemblyInstruction = "sub\t\tx" + to_string(rd) + ", x" + to_string(rd) + ", x" +  to_string(rs);
    }
    else if (func == 1)
    {
        AssemblyInstruction = "xor\t\tx" + to_string(rd) + ", x" + to_string(rd) + ", x" +  to_string(rs);
    }
    else if (func == 2)
    {
        AssemblyInstruction = "or\t\tx" + to_string(rd) + ", x" + to_string(rd) + ", x" +  to_string(rs);
    }
    else if (func == 3)
    {
        AssemblyInstruction = "and\t\tx" + to_string(rd) + ", x" + to_string(rd) + ", x" +  to_string(rs);
    }    
    else 
        AssemblyInstruction = "Instruction not supported!";

    return AssemblyInstruction;

}




string QuadrantOne (unsigned int ComInsWord, unsigned int pc, map < unsigned int, string> &Labels) // opcode two
{
    string AssemblyInstruction;
    unsigned int func, func2;
    func = (ComInsWord >> 13) & 0x7;
    func2 = (ComInsWord >> 10) & 0x3;

    switch (func)
    {
        case 0:
        {
            AssemblyInstruction = CADDI_NOP (ComInsWord);
            break;
        }
        case 1:
        {
            AssemblyInstruction = CJAL (ComInsWord, pc, Labels);
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
            AssemblyInstruction = CJ (ComInsWord, pc, Labels);
            break;            
        }  
        case 6:
        {
            AssemblyInstruction = CBEQZ (ComInsWord, pc, Labels);
            break;            
        }
        case 7:
        {
            AssemblyInstruction = CBNEZ (ComInsWord, pc, Labels);
            break;            
        }
    }

    return AssemblyInstruction;
}