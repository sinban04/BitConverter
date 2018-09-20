#ifndef BIT_CONVERTER_BIT_CONVERTER_H_
#define BIT_CONVERTER_BIT_CONVERTER_H_

#include <iostream>
#include <vector>
#include <memory>
#include <bitset>

namespace BitConverter {

// Platform-Independent DataTypes
// 
//

// Endianness of the system.
static bool isLittleEndian = true; // temporary


bool IsLittleEndian();

// BitArray (std::vector<unsigned int>)
// This functions copies the source byte array to new byte array, 
// from the sourceIndex by amount of copyCount;
std::vector<unsigned char> BitArrayCopy(
    std::vector<unsigned char>& source, int sourceIndex, int copyCount);


//bool BytesToBoolean(std::vector<unsigned char>& input, int startOffset);
//double BytesToDouble(std::vector<unsigned char>& input, int startOffset);

// These functions gets byte array with its startOffset(first index) as an input, 
// and returns several datatypes. 
short BytesToInt16(std::vector<unsigned char>& input, int startOffset);
unsigned short BytesToUInt16(std::vector<unsigned char>& input, int startOffset);
int BytesToInt32(std::vector<unsigned char>& input, int startOffset);
unsigned int BytesToUInt32(std::vector<unsigned char>& input, int startOffset);
long long BytesToInt64(std::vector<unsigned char>& input, int startOffset);
unsigned long long BytesToUInt64(std::vector<unsigned char>& input, int startOffset);


} // namespace BitConverter
#endif // BIT_CONVERTER_BIT_CONVERTER_H_
