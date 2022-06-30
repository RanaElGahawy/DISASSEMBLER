#pragma once
#include <string>
using namespace std;

string QuadrantZero (unsigned int ComInsWord);
string QuadrantOne (unsigned int ComInsWord);
string QuadrantTwo (unsigned int ComInsWord);
string CLW (unsigned int ComInsWord);
string CSW (unsigned int ComInsWord);
string CLWSP (unsigned int ComInsWord);
string CSWSP (unsigned int ComInsWord);
string CSLLI (unsigned int ComInsWord);
string CJR_MV (unsigned int ComInsWord);
string CJALR_ADD_EBREAK (unsigned int ComInsWord);
string CJ (unsigned int ComInsWord);
string CJAL (unsigned int ComInsWord);
string CBEQZ (unsigned int ComInsWord);
string CBNEZ (unsigned int ComInsWord);
string CLI (unsigned int ComInsWord);
string CLUI_ADDI16SP (unsigned int ComInsWord);
string CADDI_NOP (unsigned int ComInsWord);
string CADDI4SPN (unsigned int ComInsWord);
string CSRLI_SRAI_ANDI (unsigned int ComInsWord);
string CAND_OR_XOR_SUB (unsigned int ComInsWord);

// add illegal instructions