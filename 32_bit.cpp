#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <string>
#include <cstring>
#include "ThirtyTwoBit.h"
using namespace std;


void thirtyTwo_bit_inst(unsigned int instWord){
	unsigned int rd, rs1, rs2, funct3, funct7, opcode, j_code, u_code;
	unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
	unsigned int address;

	unsigned int instPC = pc - 4;

	opcode = instWord & 0x0000007F;
	rd = (instWord >> 7) & 0x0000001F;
	funct3 = (instWord >> 12) & 0x00000007;
	rs1 = (instWord >> 15) & 0x0000001F;
	rs2 = (instWord >> 20) & 0x0000001F;
	j_code = opcode & 7;
    u_code = opcode & 0x0000001F;
	// â€” inst[31] â€” inst[30:25] inst[24:21] inst[20]
	I_imm = ((instWord >> 20) & 0x7FF) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));
	if (u_code == 10111){
        UFormat(instWord);
    }
    else if (j_code == 7){
		JFormat(instWord);
	}
	else{
	switch(opcode){
	case 0110011:
		r_type(instWord);
        break;
	case 0010011:
		i_type(instWord,opcode);
        break;
	case 0000011:
		i_type_load(instWord);
        break;
	case 0100011:
		SFormat(instWord);
        break;
	case 1100011:
		BFormat(instWord);
        break;
    case 1100111:
        i_type(instWord,opcode);
        break;
    case 1110011:
        ecall_func();
        break;
	}
	}
}

void ecall_func(){
    string x = "ecall";
}

void r_type(unsigned int instWord){
    string x,b,c,d;
    unsigned int rd = (instWord >> 7) & 0x0000001F;
	unsigned int funct3 = (instWord >> 12) & 0x00000007;
	unsigned int rs1 = (instWord >> 15) & 0x0000001F;
	unsigned int rs2 = (instWord >> 20) & 0x0000001F;
	unsigned int funct7 = (instWord >> 25) & 0x0000007F;
	if (funct3 == 0){
		if (funct7 == 0){
    
                x = "add";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
		}
		else {    
                x = "sub";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
		}
	}
	else if (funct3 == 1){
    
                x = "sll";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 2){
    
                x = "add";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 3){
    
                x = "sltu";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 4){
                x = "xor";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 5){
		if (funct7 == 0){
    
                x = "srl";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
		}
		else {
                x = "sra";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;

		}
	}
	else if (funct3 == 6){
                x = "or";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 7){
    
                x = "and";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else {
            x = "Instruction not found";        
	}
}

void i_type(unsigned int instWord, unsigned int opcode){
    string x,b,c,d;
	unsigned int rd = (instWord >> 7) & 0x0000001F;
	unsigned int funct3 = (instWord >> 12) & 0x00000007;
	unsigned int rs1 = (instWord >> 15) & 0x0000001F;
	signed int imm = (instWord >> 20) & 0x00000FFF;
    if (opcode == 1100111){
        jalr_type(instWord);
    }
    else{
	if (funct3 == 0){
		
   
                x = "andi";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 2){ 
                x = "slti";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 3){
				x = "sltiu";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 4){
				x = "xori";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 6){
				x = "ori";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 7){
				x = "andi";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else {
		x = "Instruction not found";
	}
    }
}



void i_type_load(unsigned int instWord){
    string x,b,c,d;
	unsigned int rd = (instWord >> 7) & 0x0000001F;
	unsigned int funct3 = (instWord >> 12) & 0x00000007;
	unsigned int rs1 = (instWord >> 15) & 0x0000001F;
	unsigned int imm = (instWord >> 20) & 0x0000001F;
    unsigned int funct7 = (instWord >> 25) & 0x0000007F;

	if (funct3 == 1){   
                x = "slli";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
	}
	else if (funct3 == 5){
		if (funct7 == 0){
				x = "srli";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
		}
		else {
				x = "srai";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
		}
	}
	else{
		x = "Instruction not found";
	}
}

void jalr_type(unsigned int instWord){
    string x,b,c,d;
    unsigned int rd = (instWord >> 7) & 0x0000001F;
	unsigned int funct3 = (instWord >> 12) & 0x00000007;
	unsigned int rs1 = (instWord >> 15) & 0x0000001F;
	signed int imm = (instWord >> 20) & 0x00000FFF;
	final.open("output",ios::app);
    x = "jalr";
    b = to_string(rd);
    c = to_string(rs1);
    d = to_string(imm);
    x += "  x" + b + ",x" + c + ",x" + d;
}

void printing(unsigned int pc, string x){
    fstream final;
    final.open("output",ios::app);
    final << pc << x << "\n";
    final.close();
}
