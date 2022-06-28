<<<<<<< HEAD
#include <bits/stdc++.h>
using namespace std;
unsigned int pc = 0x0;

char memory[8*1024];	// only 8KB of memory located at address 0

void emitError(char *s)
{
	cout << s;
	exit(0);
}

void normal_inst(unsigned int instWord){
	unsigned int rd, rs1, rs2, funct3, funct7, opcode, j_code;
	unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
	unsigned int address;

	unsigned int instPC = pc - 4;

	opcode = instWord & 0x0000007F;
	rd = (instWord >> 7) & 0x0000001F;
	funct3 = (instWord >> 12) & 0x00000007;
	rs1 = (instWord >> 15) & 0x0000001F;
	rs2 = (instWord >> 20) & 0x0000001F;
	j_code = opcode & 7;
	// â€” inst[31] â€” inst[30:25] inst[24:21] inst[20]
	I_imm = ((instWord >> 20) & 0x7FF) | (((instWord >> 31) ? 0xFFFFF800 : 0x0));
	if (j_code == 7){
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
	case 0110111:
		u_type(instWord);
	}
	}
}

void r_type(unsigned int instWord){
	unsigned int rd = (instWord >> 7) & 0x0000001F;
	unsigned int funct3 = (instWord >> 12) & 0x00000007;
	unsigned int rs1 = (instWord >> 15) & 0x0000001F;
	unsigned int rs2 = (instWord >> 20) & 0x0000001F;
	unsigned int funct7 = (instWord >> 25) & 0x0000007F;

	if (funct3 == 0){
		if (funct7 == 0){

		}
		else {

		}
	}
	else if (funct3 == 1){

	}
	else if (funct3 == 2){

	}
	else if (funct3 == 3){

	}
	else if (funct3 == 4){
		
	}
	else if (funct3 == 5){
		if (funct7 == 0){

		}
		else {

		}
	}
	else if (funct3 == 6){
		
	}
	else if (funct3 == 7){
		
	}
	else {
		//instruction not found
	}
}

void i_type(unsigned int instWord){
	unsigned int rd = (instWord >> 7) & 0x0000001F;
	unsigned int funct3 = (instWord >> 12) & 0x00000007;
	unsigned int rs1 = (instWord >> 15) & 0x0000001F;
	unsigned int imm = (instWord >> 20) & 0x00000FFF;
	if (funct3 == 0){
		
	}
	else if (funct3 == 1){

	}
	else if (funct3 == 2){

	}
	else if (funct3 == 3){

	}
	else if (funct3 == 4){
		
	}
	else if (funct3 == 5){
		
	}
	else if (funct3 == 6){
		
	}
	else if (funct3 == 7){
		
	}
	else {
		//instruction not found
	}
}

void i_type_load(unsigned int instWord){
	unsigned int rd = (instWord >> 7) & 0x0000001F;
	unsigned int funct3 = (instWord >> 12) & 0x00000007;
	unsigned int rs1 = (instWord >> 15) & 0x0000001F;
	unsigned int imm = (instWord >> 20) & 0x00000FFF;

	if (funct3 == 0){
		
	}
	else if (funct3 == 1){

	}
	else if (funct3 == 2){

	}
	else if (funct3 == 3){

	}
	else if (funct3 == 4){
		
	}
	else if (funct3 == 5){
		
	}
	else{
		//instruction not found
	}
}

void SFormat(int unsigned InstWord)
{
    int unsigned funct3= InstWord & 0x00007000;
    if (funct3==0x00000000)
    // cout sb 
    else if (funct3==0x00001000)
    //cout sh
    else if (funct3==0x00002000)
    //cout sw


    int unsigned rs1= (InstWord)>>12 & 0x0000001F;
    // cout xrs1

    int unsigned rs2= (InstWord>>20) &0x0000001F;
    // cout xrs2
=======
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <cstring>
#include <string>
#include <bits/stdc++.h>
using namespace std;
fstream output;


void SFormat(int unsigned InstWord)
{   string x="x";
    string sb="sb";
    string sh="sh";
    string sw="sw";

    int unsigned funct3= InstWord & 0x00007000;
    output.open("final",ios::app);
    if (funct3==0x00000000)
    output<<sb<<" ";
    else if (funct3==0x00001000)
    output<<sh<<" ";
    else if (funct3==0x00002000)
    output<<sw<<" ";


   
    int unsigned rs2= (InstWord>>20) &0x0000001F;
    x=x+to_string(rs2);
    output<<x<<",";
    

>>>>>>> 64f4c799acecf402ce48d7cc212bb8b7c39d7125

     int unsigned Imm1= (InstWord>>7) & 0x0000001F;
     int unsigned Imm2= (InstWord>>25) & 0x0000007F;
     int unsigned FinalImm= (Imm2<<5) | Imm1 ;
<<<<<<< HEAD
     //cout FinalImm
=======
     to_string(FinalImm);
     output<<FinalImm;

    
    int unsigned rs1= (InstWord>>12) & 0x0000001F;
    x="x";
    x=x+to_string(rs1);
    output<<"("<<x<<")"<<endl;
    output.close();
>>>>>>> 64f4c799acecf402ce48d7cc212bb8b7c39d7125
}


void BFormat(int unsigned InstWord)
{
<<<<<<< HEAD
   int unsigned funct3=(InstWord>>12) & 0x00000007;
   if (funct3==0)
   //cout beq
   else if (funct3==1)
   //cout bne
   else if (funct3==4)
   //cout blt
   else if (funct3==5)
   //cout bge
   else if (funct3==6)
   //cout bltu 
   else if (funct3==7)
   //cout bgeu

   int unsigned rs1=(InstWord>>15)& 0x0000001F;
   int unsigned rs2=(InstWord>>20) & 0x0000001F;
=======
   string x="x";
   string beq="beq";
   string bne="bne";
   string blt="blt";
   string bge="bge";
   string bltu="bltu";
   string bgeu="bgeu";


   output.open("output",ios::app);

   int unsigned funct3=(InstWord>>12) & 0x00000007;
   if (funct3==0)
   output<<beq<<" ";
   else if (funct3==1)
   output<<bge<<" ";
   else if (funct3==4)
   output<<blt <<" ";
   else if (funct3==5)
    output<<bge<<" ";
   else if (funct3==6)
   output<<bltu<<" ";
   else if (funct3==7)
   output<<bgeu<<" ";

  

   int unsigned rs1=(InstWord>>15)& 0x0000001F;
    x=x+to_string(rs1);
    output<<x<<",";

   int unsigned rs2=(InstWord>>20) & 0x0000001F;
   x="x";
   x=x+to_string(rs2);
   output<<x<<",";


>>>>>>> 64f4c799acecf402ce48d7cc212bb8b7c39d7125
   int unsigned eleventh= (InstWord>>7) & 0x00000001;     //eleventh bit in unsigned
   int unsigned oneto4=(InstWord>>8) & 0x0000000F;        //storing from one to fourth bit 
   int unsigned fiveto10=(InstWord>>25) & 0x0000003F;     //storing from fifth to tenth bit 
   int unsigned twelvth=(InstWord>>31) & 0x00000001;       //storing twelvth bit 
   int unsigned finalImm=(fiveto10<<4) | oneto4 | (eleventh<<10) | (twelvth<<11);  //final Immediate value
<<<<<<< HEAD

=======
   //cout label  and then endl

   output.close();
>>>>>>> 64f4c799acecf402ce48d7cc212bb8b7c39d7125
}     


void UFormat (int unsigned InstWord)
<<<<<<< HEAD
{
    int unsigned rd= (InstWord>>7)& 0x0000001F;
    int unsigned Imm= (InstWord>>12)& 0x000FFFFF;


=======

{   
    string x="x";
    string lui="lui";
    string auipc="auipc";

    output.open("output",ios::app)

    int unsigned spec= (Instword>>5)& 0x00000003;
    if(InstWord==0)
    output<<auipc<<" ";
    else if(InstWord==1)
    output<<lui<<" ";

    int unsigned rd= (InstWord>>7)& 0x0000001F;
    x=x+to_string(rd);
    output<<x<<",";

    int unsigned Imm= (InstWord>>12)& 0x000FFFFF;
    stringstream ss;
    ss << hex << Imm;
    string res = ss.str();
    output << "0x" << res << endl;
    output.close();
}

void PrintPC(int PC)
{
    output.open("output",ios::app)
    stringstream ss;
    ss << hex << PC;
    string res = ss.str();
    output << "0x" << res << endl;
    output.close();
<<<<<<< HEAD
}


void JFormat(int unsigned InstWord)
{
   
=======
>>>>>>> 64f4c799acecf402ce48d7cc212bb8b7c39d7125
>>>>>>> fac47be5e5d0ab407c7e363f67bec94276f9b4c4
}