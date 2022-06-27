#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <string>
#include <cstring>
#include "32_bit.h"
using namespace std;
fstream final;


void normal_inst(unsigned int instWord){
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
        u_type(instWord);
    }
    else if (j_code == 7){
		j_type(instWord);
	}
	else{
	switch(opcode){
	case 0110011:
		r_type(instWord);
	case 0010011:
		i_type(instWord);
	case 0000011:
		i_type_load(instWord);
	case 0100011:
		SFormat(instWord);
	case 1100011:
		BFormat(instWord);
	}
	}
}

void r_type(unsigned int instWord){
    string x,b,c,d;
    unsigned int rd = (instWord >> 7) & 0x0000001F;
	unsigned int funct3 = (instWord >> 12) & 0x00000007;
	unsigned int rs1 = (instWord >> 15) & 0x0000001F;
	unsigned int rs2 = (instWord >> 20) & 0x0000001F;
	unsigned int funct7 = (instWord >> 25) & 0x0000007F;
    final.open("output",ios::app);
	if (funct3 == 0){
		if (funct7 == 0){
    
                x = "add";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
		}
		else {    
                x = "sub";
                b = to_string(rd);
                c = to_string(rs1);
                d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
		}
	}
	else if (funct3 == 1){
    
                x = "sll";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else if (funct3 == 2){
    
                string x = "add";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
                final.close();
	}
	else if (funct3 == 3){
    
                string x = "sltu";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else if (funct3 == 4){
                string x = "xor";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else if (funct3 == 5){
		if (funct7 == 0){
    
                string x = "srl";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
		}
		else {
                string x = "sra";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;

		}
	}
	else if (funct3 == 6){
                string x = "or";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
                final.close();
	}
	else if (funct3 == 7){
    
                string x = "and";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(rs2);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else {
    
                string x = "Instruction not found";
                final <<x<<endl;
                
	}
    final.close();
}

void i_type(unsigned int instWord){
	unsigned int rd = (instWord >> 7) & 0x0000001F;
	unsigned int funct3 = (instWord >> 12) & 0x00000007;
	unsigned int rs1 = (instWord >> 15) & 0x0000001F;
	signed int imm = (instWord >> 20) & 0x00000FFF;
	final.open("output",ios::app);
	if (funct3 == 0){
		
    
                string x = "andi";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else if (funct3 == 2){ 
                string x = "slti";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else if (funct3 == 3){
				string x = "sltiu";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else if (funct3 == 4){
				string x = "xori";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else if (funct3 == 6){
				string x = "ori";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else if (funct3 == 7){
				string x = "andi";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else {
		//instruction not found
	}
	final.close();
}



void i_type_load(unsigned int instWord){
	unsigned int rd = (instWord >> 7) & 0x0000001F;
	unsigned int funct3 = (instWord >> 12) & 0x00000007;
	unsigned int rs1 = (instWord >> 15) & 0x0000001F;
	unsigned int imm = (instWord >> 20) & 0x0000001F;
    unsigned int funct7 = (instWord >> 25) & 0x0000007F;

	if (funct3 == 1){   
                string x = "slli";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
	}
	else if (funct3 == 5){
		if (funct7 == 0){
				string x = "srli";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
		}
		else {
				string x = "srai";
                string b = to_string(rd);
                string c = to_string(rs1);
                string d = to_string(imm);
                x += "  x" + b + ",x" + c + ",x" + d;
                final <<x<<endl;
		}
	}
	else{
		//instruction not found
	}
}