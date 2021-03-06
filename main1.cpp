#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <cstring>
#include <bits/stdc++.h>
#include "compressed.h"

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

    if (ComInsWord == 0)
    {
        return "Illegal Instruction!\n";
    }

    switch (opcode)
    {
        case 0:
        {
            return QuadrantZero(ComInsWord);   //opcode 00
            break;
        }
        case 1:
        {
            return QuadrantOne(ComInsWord,pc);    //opcode 01
            break;
        }
        case 2:
        {
            return QuadrantTwo(ComInsWord);    //opcode 10
            break;
        }
        default:
        {
            // return to main?? & re-read the inCstruction
//            cout << "Error Reading machine code \n";
            return "Error Reading machine code \n";
            break;
        }
    }

    return "errorr\n";

}

void RUN (int argc, char *argv[])
{
    unsigned int instWord=0;
    ifstream inFile;
    ofstream outFile;
    string AssemblyInstruction;
    unsigned int pc2 = 0x0;

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
            
            pc2 = pc;

            if ((instWord & 0x0003 ) != 0x0003)
            {
                if (instWord == 0)
                {
                    AssemblyInstruction = "Illegal Instructions!";
                }
//                compression encoding
                    else AssemblyInstruction = CompressedIns(instWord);
                pc += 2;
                
            }
            else
            {
                instWord = instWord | (((unsigned char)memory[pc+2])<<16) |
                (((unsigned char)memory[pc+3])<<24);
//                normal encoding
                AssemblyInstruction = "thirtyTwo_bit_inst(instWord)\n";
                pc += 4;
            }

                outFile << "0x" << hex << pc2 << setw(6) <<  "\t" << AssemblyInstruction;
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