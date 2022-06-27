#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <cstring>

using namespace std;

unsigned int pc = 0x0;

unsigned char memory[8*1024];    // only 8KB of memory located at address 0

void emitError(char *s)
{
    cout << s;
    exit(0);
}


void RUN (int argc, char *argv[])
{
     unsigned int instWord=0;
    ifstream inFile;
    ofstream outFile;

	memset(memory, 0, sizeof(8*1024));
    if(argc<2) emitError("use: rvcdiss <machine_code_file_name>\n");

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
                
                pc += 2;
            }
            else
            {
                instWord = instWord | (((unsigned char)memory[pc+2])<<16) |
                (((unsigned char)memory[pc+3])<<24);
//                normal encoding
                pc += 4;
            }

                // remove the following line once you have a complete simulator
                if( &memory[pc] == NULL) break;            
        }
    } else emitError("Cannot access input file\n");
}



int main(int argc, char *argv[])
{
    RUN (argc, argv);
    return 0;
}