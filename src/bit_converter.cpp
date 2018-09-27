#include "bit_converter.h"


namespace BitConverter {


//bool BytesToBoolean(std::vector<unsigned char>& input, int startOffset);
//double BytesToDouble(std::vector<unsigned char>& input, int startOffset);

bool IsLittleEndian(){
  return isLittleEndian;
}

std::vector<unsigned char> GetBytes(bool value)
{
  std::vector<unsigned char> ret;
  ret.reserve(1);
  ret[0] = (value? (unsigned char) true : (unsigned char) false);

  return ret;
}

std::vector<unsigned char> GetBytes(short value)
{
  std::vector<unsigned char> ret;
  ret.reserve(2);

  *(short*)(&ret[0]) = value;

  return ret;
}

std::vector<unsigned char> GetBytes(unsigned short value)
{
  return GetBytes((short) value);
}

std::vector<unsigned char> GetBytes(int value)
{
  std::vector<unsigned char> ret;
  ret.reserve(4);

  *(int*)(&ret[0]) = value;

  return ret;
}

std::vector<unsigned char> GetBytes(unsigned int value)
{
  return GetBytes((int) value);
}

std::vector<unsigned char> GetBytes(long long value)
{
  std::vector<unsigned char> ret;
  ret.reserve(8);

  *(long long*)(&ret[0]) = value;

  return ret;
}

std::vector<unsigned char> GetBytes(unsigned long long value)
{
  return GetBytes((long long) value);
}

// ============ Bit Array ======
std::vector<unsigned char> BitArrayCopy(
    std::vector<unsigned char>& source, int sourceIndex, int copyCount)
{
  // First chunk info
  const int firstChunkIdx = sourceIndex / 8;
  const int firstChunkOffset = sourceIndex % 8;
  const int validBitsFirst = 8 - firstChunkOffset;
  // Last chunk info
  const int lastIndex = sourceIndex + copyCount - 1;
  const int lastChunkIdx = lastIndex / 8;
  const int lastChunkOffset = lastIndex % 8;
  const int chunkNum = lastChunkIdx - firstChunkIdx + 1;
  const int validBitsLast = lastChunkOffset + 1;

  // Logging for debug
  std::cout << "FirstIndex: " << sourceIndex << std::endl;
  std::cout << "FirstChunkIndex: " << firstChunkIdx << std::endl;
  std::cout << "FirstChunkOffset: " << firstChunkOffset << std::endl;

  std::cout << "lastIndex: " << lastIndex << std::endl;
  std::cout << "lastChunkIndex: " << lastChunkIdx << std::endl;
  std::cout << "lastChunkOffset: " << lastChunkOffset << std::endl;
  std::cout << "chunkNum: " << chunkNum << std::endl;
  std::cout << std::endl << std::endl;


  std::vector<unsigned char> ret;
  ret.reserve(chunkNum);
  std::vector<bool> retBits;
  // Expected to be filled with 0.
  retBits.reserve(chunkNum*8);

  if(copyCount <= 0){
    std::cout << "Nothing to copy. It seems unnatural";
    return ret;
  }

  int i,j;
  unsigned char temp;
  std::bitset<8> tempBits;
  // Simple Case (copycount <= 8)
  if(1 == chunkNum){
    tempBits = std::bitset<8>(source[firstChunkIdx]);
    std::cout << "sourceBits: " << tempBits << std::endl;

    std::cout << "copies one by one:(reversed) ";
    for(int i = firstChunkOffset; i < lastChunkOffset+1; i++){
      // Copy the bits
      if(tempBits[i]){
        retBits.push_back(true);
      }
      else {
        retBits.push_back(false);
      }
      std::cout << tempBits[i];
    }
    std::cout << std::endl;
  }
  else { 
    // Complex Case (copyCount > 8)
    std::cout << "It's complex case" << std::endl;
    for(i = firstChunkIdx; i < lastChunkIdx+1; i++){
      tempBits = std::bitset<8>(source[i]);
      std::cout << "sourceBits: " << tempBits << std::endl;
      if(firstChunkIdx == i){ // For the first chunk
        for(j = firstChunkOffset; j < 8; j++){
          // Copy the bits
          if(tempBits[j]){
            retBits.push_back(true);
          }
          else {
            retBits.push_back(false);
          }
        } // end for
      }
      else if(lastChunkIdx == i){ // For the last chunk
        for(j = 0; j < lastChunkOffset+1; j++){
          // Copy the bits
          if(tempBits[j]){
            retBits.push_back(true);
          }
          else {
            retBits.push_back(false);
          }
        } // end for
      }
      else {
        for(j = 0; j < 8; j++){
          // Copy the bits
          if(tempBits[j]){
            retBits.push_back(true);
          }
          else {
            retBits.push_back(false);
          }
        }
      } // end else
    }
  } 


  // Copy the chunk except the last chunk
  for(i = 0; i < chunkNum-1; i++){
    temp = 0x00;
    tempBits = std::bitset<8>();
    std::cout << "copy Chunk (reversed) :";
    for(j = 0; j < 8; j++){
      std::cout << retBits[8*i+j]; 
      if(retBits[8*i + j]){
        tempBits.set(j);
      }
      else {
        tempBits.reset(j);
      }
    }
    std::cout << std::endl;
    temp = (unsigned char) tempBits.to_ulong();
    ret.push_back(temp);
    std::cout << "temp: " << std::hex << (unsigned int)temp << std::endl;
  }



  std::cout << "size: " << std::dec << retBits.size() << std::endl;
  
  // Copy the last chunk
  tempBits = std::bitset<8>();
  for(j = 0; j< retBits.size() % 8; j++){ 
    if(retBits[8*(chunkNum-1) + j]){
      tempBits.set(j);
    }
    else {
      tempBits.reset(j);
    }
  } 

  temp = (unsigned char) tempBits.to_ulong();
  ret.push_back(temp);


  std::cout << "copy Last Chunk :" << tempBits << std::endl;
  std::cout << "temp: " << std::hex << (unsigned int)temp << std::endl;
      
  for(auto& iter : ret){
    auto print = std::bitset<8>(iter);
    std::cout << "return: " << std::hex << print << std::endl;
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
