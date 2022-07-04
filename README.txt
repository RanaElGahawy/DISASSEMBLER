Project 1:
Members: Rana El Gahawy, Yehya Elkasas, Ali Yassine.

Topic: Disassembler project that takes a binary file as an input and creates an output file containing the risc-v true instructions respectively.

Implementation Details:
In the main file we have a function called "RUN".
What does "RUN" do?
-initializes pc to 0x0;
- specifies maximum size of binary file 
- Suppose the input file is called "test.bin", the output file is supposed to be "test.s".
To achieve this, we read character by character from the name of the input file "test.bin" and stop reading when we reach "."
All what we read is saved in a string and concatinated with ".s". Thus, this is the name of the output file to be created.
- opens binary file  to start reading
- creates while loop that reads from the file and does the below operations (refer to 1,2,3,4,5,6,7 explained below).


In this  project we had two kinds of instructions: The true 32 bit instructions and the c-extension which are true instructions of 16 bit.

The first step was to read the input file:
 
1-In this process we started by reading the first two bits
if (first two bits are not 11)
{
   we got to the compresed function which then reads 16 bits called "CompressedIns"
}

else 
{
  we got to the 32 bit function which reads 32 bits and is called "thirtyTwo_bit_inst"
}

2- What does "CompressedIns" do?





3- What does "thirtyTwo_bit_inst" do?
This function saves the first 7 bits of the instruction word in a unsigned int called "opcode".
Based on the opcide and using case statements, each opcode value takes us to a different function which represents a different instruction format.

4-
We differentiatd these string functions into:
-SFormat
-JFormat
-UFormat
-BFormat
-r_type
-i_type
-i_type_load
-jalr_type
-ecall_func

5-
In each function we mask the values needed according to the format and save them in unsigned integers( or signed integers in case of offset or immediate).
In functions that include "funct3", we mask the respectable values and do switch statements to see which instruction we wil be printing according to the value of funct3.

At the end we use the function "to_string()" to transform integers to string. 
The last step here is to concatinate all strings into one string and save them in what we named "toprint" or"x" or"AssemblyInstruction". (According to each member).
This string value is returned by the function.

6-
In the main function we have an integere variable called "PC" which is incremented by either 2 or 4 each time according to what function we call ( 32 bit function or compressed).

7- We print the pc and the concatinated string in output file each time we loop.
8- The while loop breaks when we read NULL which means there is nothing left to read


              

