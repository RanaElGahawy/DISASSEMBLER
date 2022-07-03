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
    string toprint,register2,offset,register1;
    unsigned int rs2,rs1,Imm1,Imm2,FinalImm,funct3;
    int trial;
    rs2= (InstWord>>20) &0x0000001F;
    register2 =x+to_string(rs2)+",";

    rs1=(InstWord>>15)&0x0000001F;
    register1=x+to_string(rs1);

    Imm1= (InstWord>>7) & 0x0000001F;    //offset 
    Imm2= (InstWord>>25) & 0x0000007F;
    FinalImm= (Imm2<<5) | Imm1 ;
    offset=to_string(FinalImm);
    
    
    funct3= InstWord & 0x00007000;      //specific instruction
    
    if (funct3==0x00000000)
     toprint= sb+ register2 +","+offset+"("+register1+")";
    else if (funct3==0x00001000)
     toprint= sh+ register2 +","+offset+"("+register1+")";
    else if (funct3==0x00002000)
    toprint= sw+ register2+ ","+offset+"("+register1+")";
     else 
    toprint="Instruction not found!";

    return toprint;




}


string BFormat( unsigned int InstWord,signed int PC)
{
   string x="x";
   string toprint;
   string x1;
   string x2;
   unsigned int rs1,rs2,eleventh,oneto4,fiveto10,twelvth,funct3;
   signed int finalImm;

   rs1=(InstWord>>15)& 0x0000001F;//number of rs1
   x1=x+to_string(rs1); // saving it in form of xnumber as string

   rs2=(InstWord>>20) & 0x0000001F;//number of rs2
   x2=x+to_string(rs2);//saving it in form of xnumber

   eleventh= (InstWord>>7) & 0x00000001;     //eleventh bit in unsigned
   signed int xeleventh= (InstWord>>7) ^ 0x00000001; 
   oneto4=(InstWord>>8) & 0x0000000F;        //storing from one to fourth bit 
   signed int xoneto4 = (InstWord>>8) ^ 0x0000000F;
   fiveto10=(InstWord>>25) & 0x0000003F;     //storing from fifth to tenth bit 
   signed int xfiveto10=(InstWord>>25) ^ 0x0000003F;
   twelvth=(InstWord>>31) & 0x00000001;       //storing twelvth bit 

    signed int xfinalImm= xoneto4 |(xfiveto10<<4) |(xeleventh<<10) | (twelvth<<11)+PC;
   if (twelvth){
    finalImm = xfinalImm + 0x1;
    finalImm = finalImm * -1;
   }
   else{
   finalImm= oneto4 |(fiveto10<<4) |(eleventh<<10) | (twelvth<<11)+PC;  //final Immediate value
   finalImm= (oneto4 |(fiveto10<<4) |(eleventh<<10) | (twelvth<<11))*2+PC;  //final Immediate value
   }

   stringstream ss;
   ss << hex <<finalImm;     //saving immediate as hexadecimal so that compiler does not change it to decimal
   string res = ss.str();

   
   


   funct3=(InstWord>>12) & 0x00000007;// to identify the instruction
   if (funct3==0)
   toprint="beq "+x1+","+x2+","+"0x"+res;
   else if (funct3==1)
   //cout bne
    toprint="bne "+x1+","+x2+","+"0x"+res;
   else if (funct3==4)
   //cout blt
    toprint="blt "+x1+","+x2+","+"0x"+res;
   else if (funct3==5)
   //cout bge
    toprint="bge "+x1+","+x2+","+"0x"+res;
   else if (funct3==6)
   //cout bltu 
    toprint="bltu "+x1+","+x2+","+"0x"+res;
   else if (funct3==7)
   //cout bgeu
    toprint="bgeu "+x1+","+x2+","+"0x"+res;
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
    unsigned int rd,Imm,spec;

    rd= (InstWord>>7)& 0x0000001F;//getting destination register number
    x=x+to_string(rd);  //writing it in form of xnumber


    Imm= (InstWord>>12)& 0x000FFFFF; // getting immediate

    stringstream ss;
    ss << hex << Imm;     //saving immediate as hexadecimal so that compiler does not change it to decimal
    string res = ss.str();


    spec= (InstWord>>5)& 0x00000003;  // saving bits that specify the instruction

    if(spec==0)
    toprint= auipc+x+",0x"+res;    //saving the instruction to be printed in string
    else if(spec==1)
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
    string toprint;
    string AddressString;
    unsigned int rd, Imm1to10,Imm11,Imm12to19,Imm20;
    signed int FinalImm,address;

    rd=(InstWord>>7) & 0x0000001F;  //saving number of destination register 
    x=x+to_string(rd);

    Imm1to10=(InstWord>>21) & 0x000003FF; //bits 1 to 10 of immediate
    Imm11=(InstWord>>20) & 0x00000001;    //bit 11
    Imm12to19=(InstWord>>12) & 0x000000FF; //bit 12 to 19
    Imm20=(InstWord>>31) & 0x00000001;   //bit 20

    FinalImm=(Imm1to10 | (Imm11<<10)| (Imm12to19<<11)|(Imm20<<19))*2+PC; //displaying all bits
     
    stringstream ss;
    ss << hex << FinalImm;
    string res = ss.str();


    //AddressString= to_string(res);  //making the address a string to print later

    toprint= "jal "+ x + "," +"0x"+ res;  //saving the instruction to be printed in a string

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
