#pragma once
#include <bits/stdc++.h>
#include <string>
using namespace std;
string r_type(unsigned int instWord);
string i_type(unsigned int instWord, unsigned int opcode);
string i_type_load(unsigned int instWord);
string thirtyTwo_bit_inst(unsigned int instWord);
string jalr_type(unsigned int instWord);