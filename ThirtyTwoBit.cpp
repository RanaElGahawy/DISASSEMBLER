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
    


     int unsigned Imm1= (InstWord>>7) & 0x0000001F;
     int unsigned Imm2= (InstWord>>25) & 0x0000007F;
     int unsigned FinalImm= (Imm2<<5) | Imm1 ;
     to_string(FinalImm);
     output<<FinalImm;

    
    int unsigned rs1= (InstWord>>12) & 0x0000001F;
    x="x";
    x=x+to_string(rs1);
    output<<"("<<x<<")"<<endl;
    output.close();
}


void BFormat(int unsigned InstWord)
{
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


   int unsigned eleventh= (InstWord>>7) & 0x00000001;     //eleventh bit in unsigned
   int unsigned oneto4=(InstWord>>8) & 0x0000000F;        //storing from one to fourth bit 
   int unsigned fiveto10=(InstWord>>25) & 0x0000003F;     //storing from fifth to tenth bit 
   int unsigned twelvth=(InstWord>>31) & 0x00000001;       //storing twelvth bit 
   int unsigned finalImm=(fiveto10<<4) | oneto4 | (eleventh<<10) | (twelvth<<11);  //final Immediate value
   //cout label  and then endl

   output.close();
}     


void UFormat (int unsigned InstWord)

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
}


void JFormat(int unsigned InstWord)
{
   
}