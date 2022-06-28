#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <cstring>
#include <string>
#include <bits/stdc++.h>
using namespace std;



void SFormat(int unsigned InstWord)
{   string x="x";
    string sb="sb";
    string sh="sh";
    string sw="sw";
    string toprint;

    int unsigned rs2= (InstWord>>20) &0x0000001F;
    string register2 =x+to_string(rs2)+",";
    output<<x<<",";


     int unsigned Imm1= (InstWord>>7) & 0x0000001F;    //offset 
     int unsigned Imm2= (InstWord>>25) & 0x0000007F;
     int unsigned FinalImm= (Imm2<<5) | Imm1 ;
     string offset=to_string(FinalImm);
    
    
    int unsigned funct3= InstWord & 0x00007000;      //specific instruction
    if (funct3==0x00000000)
     toprint= sb+ register2 +"("+offset+")";
    else if (funct3==0x00001000)
     toprint= sh+ register2 +"("+offset+")";
    else if (funct3==0x00002000)
    toprint= sw+ register2 +"("+offset+")";
     else 
    toprint="Instruction not found!";



}


void BFormat(int unsigned InstWord)
{
   string toprint;
   string x1=x;
   string x2=x;
   int unsigned rs1=(InstWord>>15)& 0x0000001F;
   x1=x1+to_string(rs1);

   int unsigned rs2=(InstWord>>20) & 0x0000001F;
   x2=x2+tostring(rs2);

   int unsigned eleventh= (InstWord>>7) & 0x00000001;     //eleventh bit in unsigned
   int unsigned oneto4=(InstWord>>8) & 0x0000000F;        //storing from one to fourth bit 
   int unsigned fiveto10=(InstWord>>25) & 0x0000003F;     //storing from fifth to tenth bit 
   int unsigned twelvth=(InstWord>>31) & 0x00000001;       //storing twelvth bit 
   int unsigned finalImm= oneto4 |(fiveto10<<4) (eleventh<<10) | (twelvth<<11);  //final Immediate value


   int unsigned funct3=(InstWord>>12) & 0x00000007;
   if (funct3==0)
   toprint="beq "+x1+","+x2","+to_string(finalImm);
   else if (funct3==1)
   //cout bne
    toprint="bne "+x1+","+x2","+to_string(finalImm);
   else if (funct3==4)
   //cout blt
    toprint="blt "+x1+","+x2","+to_string(finalImm);
   else if (funct3==5)
   //cout bge
    toprint="bge "+x1+","+x2","+to_string(finalImm);
   else if (funct3==6)
   //cout bltu 
    toprint="bltu "+x1+","+x2","+to_string(finalImm);
   else if (funct3==7)
   //cout bgeu
    toprint="bgeu "+x1+","+x2","+to_string(finalImm);
    else 
    toprint="Instruction not found!";
  

}     


void UFormat (int unsigned InstWord)

{
    int unsigned rd= (InstWord>>7)& 0x0000001F;
    int unsigned Imm= (InstWord>>12)& 0x000FFFFF;
    string x="x";
    string lui="lui ";
    string auipc="auipc ";
    string toprint;

   int unsigned rd= (InstWord>>7)& 0x0000001F;
    x=x+to_string(rd);
    output<<x<<",";

    int unsigned Imm= (InstWord>>12)& 0x000FFFFF;
    stringstream ss;
    ss << hex << Imm;
    string res = ss.str();


    int unsigned spec= (Instword>>5)& 0x00000003;
    if(spec==0)
    toprint= auipc+x+",0x"+res;
    else if(InstWord==1)
    toprint= lui+x+",0x"+res;
     else 
    toprint="Instruction not found!";




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


void JFormat(int unsigned InstWord, int unsigned PC)
{
    string x="x";
    int unsigned rd=(InstWord>>7) & 0x0000001f;
    x=x+to_string(rd);

    int unsigned Imm1to10=(Instword>>21) & 0x000003ff;
    int unsigned Imm11=(InstWord>>20) & 0x00000001;
    int unsigned Imm12to19=(InstWord>>12) & 0x000000ff;
    int unsigned Imm20=(InstWord>>31) & 0x00000001;
    int unsigned FinalImm=Imm1to10 | (Imm11<<10)| (Imm12to19<<11)|(Imm20<<19);
    int unsigned RA= PC+ FinalImm*2;
    string RAA= to_string(RA);

    string toprint= "JAL "+ x + "," + RAA;

    
    /*output.open("output",ios::app)
    output<<"JAL"<<" ";
    output<<RA;
    output.close();
    */

}

void Print(int unsigned PC,string toprint )
{
   fstream output;
   output.openfile("output",ios::app);
   stringstream ss;
   ss << hex << PC;
   string res = ss.str();
   output<<"0x"<<res<<"   "<<toprint;
   output.close();
}
