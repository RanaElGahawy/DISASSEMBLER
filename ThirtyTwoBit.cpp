#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <cstring>
#include <string>
#include <bits/stdc++.h>
#include"ThirtyTwoBit.h"
using namespace std;

string SFormat(unsigned int InstWord)
{   string x="x";
    string sb="sb";
    string sh="sh";
    string sw="sw";
    string toprint;

     unsigned int rs2= (InstWord>>20) &0x0000001F;
    string register2 =x+to_string(rs2)+",";


     unsigned int Imm1= (InstWord>>7) & 0x0000001F;    //offset 
     unsigned int Imm2= (InstWord>>25) & 0x0000007F;
     unsigned int FinalImm= (Imm2<<5) | Imm1 ;
     string offset=to_string(FinalImm);
    
    
    unsigned int funct3= InstWord & 0x00007000;      //specific instruction
    if (funct3==0x00000000)
     toprint= sb+ register2 +"("+offset+")";
    else if (funct3==0x00001000)
     toprint= sh+ register2 +"("+offset+")";
    else if (funct3==0x00002000)
    toprint= sw+ register2 +"("+offset+")";
     else 
    toprint="Instruction not found!";

    return toprint;




}


string BFormat( unsigned int InstWord,unsigned int PC)
{
   string toprint;
   string x1=x;
   string x2=x;

   unsigned int rs1=(InstWord>>15)& 0x0000001F;//number of rs1
   x1=x1+to_string(rs1); // saving it in form of xnumber as string

   unsigned int rs2=(InstWord>>20) & 0x0000001F;//number of rs2
   x2=x2+tostring(rs2);//saving it in form of xnumber

    unsigned int eleventh= (InstWord>>7) & 0x00000001;     //eleventh bit in unsigned
    unsigned int oneto4=(InstWord>>8) & 0x0000000F;        //storing from one to fourth bit 
    unsigned int fiveto10=(InstWord>>25) & 0x0000003F;     //storing from fifth to tenth bit 
    unsigned int  twelvth=(InstWord>>31) & 0x00000001;       //storing twelvth bit 
    signed int finalImm= oneto4 |(fiveto10<<4) (eleventh<<10) | (twelvth<<11);  //final Immediate value
    signed int address= PC+ finalImm;

   unsigned int funct3=(InstWord>>12) & 0x00000007;// to identify the instruction
   if (funct3==0)
   toprint="beq "+x1+","+x2","+to_string(address);
   else if (funct3==1)
   //cout bne
    toprint="bne "+x1+","+x2","+to_string(address);
   else if (funct3==4)
   //cout blt
    toprint="blt "+x1+","+x2","+to_string(address);
   else if (funct3==5)
   //cout bge
    toprint="bge "+x1+","+x2","+to_string(address);
   else if (funct3==6)
   //cout bltu 
    toprint="bltu "+x1+","+x2","+to_string(address);
   else if (funct3==7)
   //cout bgeu
    toprint="bgeu "+x1+","+x2","+to_string(address);
    else 
    toprint="Instruction not found!";

    return toprint;
  

}     


string UFormat (unsigned int InstWord)

{

    string x="x";
    string lui="lui ";
    string auipc="auipc ";
    string toprint;

    unsigned int rd= (InstWord>>7)& 0x0000001F;//getting destination register number
    x=x+to_string(rd);  //writing it in form of xnumber


    unsigned int Imm= (InstWord>>12)& 0x000FFFFF; // getting immediate

    stringstream ss;
    ss << hex << Imm;     //saving immediate as hexadecimal so that compiler does not change it to decimal
    string res = ss.str();


    unsigned int spec= (InstWord>>5)& 0x00000003;  // saving bits that specify the instruction

    if(spec==0)
    toprint= auipc+x+",0x"+res;    //saving the instruction to be printed in string
    else if(InstWord==1)
    toprint= lui+x+",0x"+res;
     else 
    toprint="Instruction not found!";

    return toprint;


}

/*void PrintPC(int PC)
{
    output.open("output",ios::app)
    stringstream ss;
    ss << hex << PC;
    string res = ss.str();
    output << "0x" << res << endl;
    output.close();
<<<<<<< HEAD
}
*/

string JFormat(unsigned int InstWord,  unsigned int PC)
{
    string x="x";

    unsigned int rd=(InstWord>>7) & 0x0000001f;  //saving number of destination register 
    x=x+to_string(rd);

    unsigned int Imm1to10=(Instword>>21) & 0x000003ff; //bits 1 to 10 of immediate
    unsigned int Imm11=(InstWord>>20) & 0x00000001;    //bit 11
    unsigned int Imm12to19=(InstWord>>12) & 0x000000ff; //bit 12 to 19
    unsigned int Imm20=(InstWord>>31) & 0x00000001;   //bit 20

    signed int FinalImm=Imm1to10 | (Imm11<<10)| (Imm12to19<<11)|(Imm20<<19); //displaying all bits 

    signed int address= PC+ FinalImm*2; //the address to jump to

    string AddressString= to_string(address);  //making the address a string to print later

    string toprint= "JAL "+ x + "," + AddressString;  //saving the instruction to be printed in a string

    return toprint;

    
    /*output.open("output",ios::app)
    output<<"JAL"<<" ";
    output<<RA;
    output.close();
    */

}

/*void Print(unsigned int PC,string toprint )
{
   fstream output;
   output.openfile("output",ios::app);
   stringstream ss;
   ss << hex << PC;
   string res = ss.str();
   output<<"0x"<<res<<"   "<<toprint;
   output.close();
}*/
