#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <cstring>
#include <bits/stdc++.h>
#include "compressed.h"
#include "32_bit.h"
#include "ThirtyTwoBit.h"
using namespace std;

unsigned int pc = 0x0;

unsigned char memory[8*1024];    // only 8KB of memory located at address 0

void emitError(char *s)
{
    cout << s;
    exit(0);
}


string CompressedIns ( unsigned int ComInsWord)
{
    unsigned int opcode = ComInsWord & 0x0003;

    switch (opcode)
    {
        case 0:
        {
            return QuadrantZero(ComInsWord);   //opcode 00
            break;
        }
        case 1:
        {
            return QuadrantOne(ComInsWord);    //opcode 01
            break;
        }
        case 2:
        {
            return QuadrantTwo(ComInsWord);    //opcode 10
            break;
        }
        default:
        {
            // return to main?? & re-read the instruction
//            cout << "Error Reading machine code \n";
            return "Error Reading machine code \n";
            break;
        }
    }

}

string thirtyTwo_bit_inst(unsigned int instWord){
	unsigned int opcode, j_code, u_code;


	unsigned int instPC = pc - 4;
    string x;
	opcode = instWord & 0x0000007F;

	j_code = opcode & 7;
    u_code = opcode & 0x0000001F;
	// â€” inst[31] â€” inst[30:25] inst[24:21] inst[20]

	if (u_code == 10111){
        return UFormat(instWord);
    }
    else if (j_code == 7){
		return JFormat(instWord, pc);
	}
	else{
	switch(opcode){
	case 0110011:{
		return r_type(instWord);
        break;
    }
	case 0010011:{
		return i_type(instWord,opcode);
        break;
    }
	case 0000011:{
		return i_type_load(instWord);
        break;
    }
	case 0100011:{
		return SFormat(instWord);
        break;
    }
	case 1100011:{
		return BFormat(instWord, pc);
        break;
    }
    case 1100111:{
        return i_type(instWord,opcode);
        break;
    }
    case 1110011:{
        return ecall_func();
        break;
    }
	}
	}

}

void RUN (int argc, char *argv[])
{
    unsigned int instWord=0;
    ifstream inFile;
    ofstream outFile;
    string AssemblyInstruction;

	memset(memory, 0, sizeof(8*1024));
    if(argc<2) emitError("use: rvcdiss <machine_code_file_name>\n");

    string outputFilename = argv[1];
    string::size_type pos = outputFilename.find('.');

    if (pos != std::string::npos)
    {
        outputFilename = outputFilename.substr(0, pos);
    }

    outputFilename = outputFilename + ".s\n";     
    outFile.open (outputFilename, ios::out);
    inFile.open(argv[1], ios::in | ios::binary | ios::ate);

    if(inFile.is_open())
    {
        int fsize = inFile.tellg();

        inFile.seekg (0, inFile.beg);
        if(!inFile.read((char *)memory, fsize)) emitError("Cannot read from input file\n");

        while(true){
                instWord = (unsigned char)memory[pc] | (((unsigned char)memory[pc+1])<<8);
            
            if ((instWord & 0x0003 ) != 0x0003)
            {
//                compression encoding
            AssemblyInstruction = CompressedIns(instWord);
                
                pc += 2;
            }
            else
            {
                instWord = instWord | (((unsigned char)memory[pc+2])<<16) |
                (((unsigned char)memory[pc+3])<<24);
//                normal encoding
            AssemblyInstruction = thirtyTwo_bit_inst(instWord);
                pc += 4;
            }

                // remove the following line once you have a complete simulator
                outFile << "0x" << hex << pc << "\t" << AssemblyInstruction;
                if( memory[pc] == NULL) break;            
        }
    } else emitError("Cannot access input file\n");
    
    inFile.close();
    outFile.close();

}



int main(int argc, char *argv[])
{
    RUN (argc, argv);
    return 0;
}