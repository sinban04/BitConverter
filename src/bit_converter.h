#ifndef BIT_CONVERTER_BIT_CONVERTER_H_
#define BIT_CONVERTER_BIT_CONVERTER_H_

#include <iostream>
#include <vector>
#include <memory>

namespace BitConveter {

// Platform-Independent DataTypes
// 
//


bool BytesToBoolean(std::vector<unsigned char>& input, int offset);
double BytesToDouble(std::vector<unsigned char>& input, int offset);
// This function gets byte array with its offset(first index) as an input, and
// returns several datatypes. 
short BytesToInt16(std::vector<unsigned char>& input, int offset);
unsigned short BytesToUInt16(std::vector<unsigned char>& input, int offset);
int BytesToInt32(std::vector<unsigned char>& input, int offset);
unsigned int BytesToUInt32(std::vector<unsigned char>& input, int offset);
long long BytesToInt64(std::vector<unsigned char>& input, int offset);
unsigned long long BytesToUInt64(std::vector<unsigned char>& input, int offset);


} // namespace BitConverter
#endif // BIT_CONVERTER_BIT_CONVERTER_H_
