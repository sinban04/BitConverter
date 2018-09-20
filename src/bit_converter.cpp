#include "bit_converter.h"


namespace BitConverter {


//bool BytesToBoolean(std::vector<unsigned char>& input, int startOffset);
//double BytesToDouble(std::vector<unsigned char>& input, int startOffset);

bool IsLittleEndian(){
  return isLittleEndian;
}

// ============ Bit Array ======
std::vector<unsigned char> BitArrayCopy(
    std::vector<unsigned char>& source, int sourceIndex, int copyCount)
{
  std::vector<unsigned char> ret;
  if(copyCount <= 0){
    std::cout << "Nothing to copy. It seems unnatural";
    return ret;
  }

  std::bitset<8> temp;
  unsigned char tempChar;
  // First chunk info
  int firstChunkIdx = sourceIndex / 8;
  int firstChunkOffset = sourceIndex % 8;
  // Last chunk info
  int lastIndex = sourceIndex + copyCount - 1;
  int lastChunkIdx = lastIndex / 8;
  int lastChunkOffset = lastIndex % 8;
  int chunkNum = lastChunkIdx - firstChunkIdx + 1;

  std::cout << "FirstIndex: " << sourceIndex << std::endl;
  std::cout << "FirstChunkIndex: " << firstChunkIdx << std::endl;
  std::cout << "FirstChunkOffset: " << firstChunkOffset << std::endl;

  std::cout << "lastIndex: " << lastIndex << std::endl;
  std::cout << "lastChunkIndex: " << lastChunkIdx << std::endl;
  std::cout << "lastChunkOffset: " << lastChunkOffset << std::endl;
  std::cout << "chunkNum: " << chunkNum << std::endl;
  std::cout << std::endl << std::endl;

  int i,j;
  // For simple case (copyCount < 8)
  if(chunkNum == 1){
    std::cout << "It's simple case" << std::endl;
    tempChar = source[firstChunkIdx];
    // Valid bits: 8-firstChunkOffset;
    tempChar = tempChar >> firstChunkOffset; 
    
    ret.push_back(tempChar);

    for(auto& iter : ret){
      auto print = std::bitset<8>(iter);
      std::cout << "return: " << std::hex << print << std::endl;
//      std::cout << "return: " << std::hex << (unsigned int)iter << std::endl;
    }
    return ret;
  }

  std::cout << "It's complex case" << std::endl;

  // Full case (copyCount >= 8)
  // Working on bit stream chunk by chunk (8 bit size)
  std::bitset<8> first, last;
  std::vector<unsigned char> tempVec;
  for(i = firstChunkIdx; i < lastChunkIdx+1; i++){
    // Get first chunk(unsigned char) from source stream vector.
    tempChar = source[i];

    if(i == firstChunkIdx){   // Valid bits: 8-firstChunkOffset
      tempChar = tempChar >> firstChunkOffset;
      first = std::bitset<8-firstChunkOffset>(tempChar);
    }
    else if(i == lastChunkIdx){   // Valid bits: lastChunkOffset+1 
      // The bit on lastChunkOffset should be preserved.
      tempChar << 8-lastChunkOffset-1; 
      tempChar >> 8-lastChunkOffset-1;
      last = std::bitset<lastChunkOffset+1>(tempChar);
    }

    std::cout << "chunk: " << std::hex << (unsigned int)tempChar << std::endl;
    tempVec.push_back(tempChar);
  }

  // Concatenation of the bits with the alignment
  std::bitset<copyCount> retBits;
  std::string firstBits = first.to_string();  // 8-firstChunkOffset bits
  std::string lastBits = last.to_string();    // lastChunkOffset+1 bits
  for(auto& iter : tempVec){
    temp = std::bitset<8>(iter);
    firstBits += temp.to_string();            // 8 bits
  }
  firstBits += lastBits;

  retBits = std::bitset<copyCount>(firstBits);
  for(i = 0; i < (copyCount/32)+1; i++){
     
  }



  for(auto& iter : ret){
    auto print = std::bitset<8>(iter);
    std::cout << "return: " << std::hex << print << std::endl;
    std::cout << std::endl;
//    std::cout << "return: " << std::hex << (unsigned int)iter << std::endl;
  }
  return ret;
}


// ============= Bit Converter ======
short BytesToInt16(std::vector<unsigned char>& input, int startOffset)
{
  if(input.empty()){
    std::cerr << "FATAL: Null input byte vector";
    return 0;
  }
  if((unsigned int) startOffset >= input.size()){
    std::cerr << "FATAL: Out of Range";
    return 0;
  }
  if(startOffset > input.size() - 2){
    std::cerr << "FATAL: Input byte vector is too small";
    return 0;
  }

  // 0x0000
  if(isLittleEndian){       // MSB is loacted in higher address.
    return (input[startOffset]) | (input[startOffset+1] << 8);
  } 
  else {                    // MSB is located in lower address.
    return (input[startOffset] << 8) | (input[startOffset]);
  }
}

unsigned short BytesToUInt16(std::vector<unsigned char>& input, int startOffset)
{
  if(input.empty()){
    std::cerr << "FATAL: Null input byte vector";
    return 0;
  }
  if((unsigned int) startOffset >= input.size()){
    std::cerr << "FATAL: Out of Range";
    return 0;
  }
  if(startOffset > input.size() - 2){
    std::cerr << "FATAL: Input byte vector is too small";
    return 0;
  }

  return (unsigned short) BytesToInt16(input, startOffset);
}

int BytesToInt32(std::vector<unsigned char>& input, int startOffset)
{
  if(input.empty()){
    std::cerr << "FATAL: Null input byte vector";
    return 0;
  }
  if((unsigned int) startOffset >= input.size()){
    std::cerr << "FATAL: Out of Range";
    return 0;
  }
  if(startOffset > input.size() - 4){
    std::cerr << "FATAL: Input byte vector is too small";
    return 0;
  }

  // 0x00000000
  if(isLittleEndian){       // MSB is loacted in higher address.
    return (input[startOffset]) | (input[startOffset+1] << 8) |
      (input[startOffset+2] << 16) | (input[startOffset+3] << 24);
  } 
  else {                    // MSB is located in lower address.
    return (input[startOffset] << 24) | (input[startOffset] << 16) |
      (input[startOffset] << 8) | (input[startOffset]);
  }
}

unsigned int BytesToUInt32(std::vector<unsigned char>& input, int startOffset)
{
  if(input.empty()){
    std::cerr << "FATAL: Null input byte vecotr";
    return 0;
  }
  if((unsigned int) startOffset >= input.size()){
    std::cerr << "FATAL: Out of Range";
    return 0;
  }
  if(startOffset > input.size() - 4){
    std::cerr << "FATAL: Input byte vector is too small";
    return 0;
  }

  return (unsigned int) BytesToInt32(input, startOffset);
}

long long BytesToInt64(std::vector<unsigned char>& input, int startOffset)
{
  if(input.empty()){
    std::cerr << "FATAL: Null input byte vecotr";
    return 0;
  }
  if((unsigned int) startOffset >= input.size()){
    std::cerr << "FATAL: Out of Range";
    return 0;
  }
  if(startOffset > input.size() - 8){
    std::cerr << "FATAL: Input byte vector is too small";
    return 0;
  }

  int first, second;
  // 0x00000000 00000000
  if(isLittleEndian){       // MSB is loacted in higher address.
    first = (input[startOffset]) | (input[startOffset+1] << 8) |
      (input[startOffset+2] << 16) | (input[startOffset+3] << 24);
    second = (input[startOffset+4]) | (input[startOffset+5] << 8) |
      (input[startOffset+6] << 16) | (input[startOffset+7] << 24);
    return (long long)((unsigned int) first | ((unsigned long long) second << 32));
  } 
  else {                    // MSB is located in lower address.
    first = (input[startOffset] << 24) | (input[startOffset+1] << 16) |
      (input[startOffset+2] << 8) | (input[startOffset+3]);
    second = (input[startOffset+4] << 24) | (input[startOffset+5] << 16) |
      (input[startOffset+6] << 8) | (input[startOffset+7]);
    return (long long)((unsigned int) second | (unsigned long long) first << 32);
  }
}

unsigned long long BytesToUInt64(std::vector<unsigned char>& input, int startOffset)
{
  if(input.empty()){
    std::cerr << "FATAL: Null input byte vecotr";
    return 0;
  }
  if((unsigned int) startOffset >= input.size()){
    std::cerr << "FATAL: Out of Range";
    return 0;
  }
  if(startOffset > input.size() - 8){
    std::cerr << "FATAL: Input byte vector is too small";
    return 0;
  }
  return (unsigned long long) BytesToInt64(input, startOffset);
}

} // namespace BitConverter
