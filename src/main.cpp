#include <iostream>

#include "bit_converter.h"

void bitArrayCopyTest()
{
  unsigned char c1 = 0x15;
  unsigned char c2 = 0x22;
  unsigned char c3 = 0x33;
  unsigned char c4 = 0x44;
  unsigned char c5 = 0x55;
  unsigned char c6 = 0x66;
  unsigned char c7 = 0x77;
  unsigned char c8 = 0x88;
  
  auto bitset1 = std::bitset<8>(c1);
  auto bitset2 = std::bitset<8>(c2);
  std::vector<unsigned char> byteArray = {c1, c2, c3, c4, c5, c6, c7, c8};


  std::vector<unsigned char> copy = BitConverter::BitArrayCopy(byteArray, 3, 20);


  std::bitset<8> b1(c1);
  unsigned char outc = (unsigned char) b1.to_ulong();
  

  std::bitset<8> temp;
  std::cout << "c1 : " << std::hex << (unsigned int)c1 << std::endl; 
  std::cout << "bitset : " << std::hex << b1 << std::endl; 
  std::cout << "bitset[0] : " << std::hex << b1[0] << std::endl; 
  std::cout << "bitset[1] : " << std::hex << b1[1] << std::endl; 
  std::cout << "bitset[2] : " << std::hex << b1[2] << std::endl;
  std::cout << "c1` : " << std::hex << (unsigned int)outc << std::endl; 

  for(auto& iter : byteArray){
    temp = std::bitset<8>(iter);
    std::cout << "output] vector : " << std::hex << (unsigned int)iter << std::endl; 
    std::cout << "output] vector : " << std::hex << temp << std::endl; 
  }

  for(auto& iter : copy){
    temp = std::bitset<8>(iter);
    std::cout << "output] copy : " << std::hex << (unsigned int)iter << std::endl; 
    std::cout << "output] copy : " << std::hex << temp << std::endl; 
  }
}


void bitConverterTest()
{
  unsigned char c1 = 0x15;
  unsigned char c2 = 0x22;
  unsigned char c3 = 0x33;
  unsigned char c4 = 0x44;
  unsigned char c5 = 0x55;
  unsigned char c6 = 0x66;
  unsigned char c7 = 0x77;
  unsigned char c8 = 0x88;
  
  std::vector<unsigned char> byteArray = {c1, c2, c3, c4, c5, c6, c7, c8};
  
  short _short;
  unsigned short _unsigned_short;
  int _int;
  unsigned int _unsigned_int;
  long long _long_long;
  unsigned long long _unsigned_long_long;

  _short = BitConverter::BytesToInt16(byteArray, 0);
  _unsigned_short = BitConverter::BytesToUInt16(byteArray, 0);
  _int = BitConverter::BytesToInt32(byteArray, 1);
  _unsigned_int = BitConverter::BytesToUInt32(byteArray, 1);
  _long_long = BitConverter::BytesToInt64(byteArray, 0);
  _unsigned_long_long = BitConverter::BytesToUInt64(byteArray, 0);


  std::bitset<8> temp;
  std::bitset<8> b1(c1);
  unsigned char outc = (unsigned char) b1.to_ulong();

  std::cout << "c1 : " << std::hex << (unsigned int)c1 << std::endl; 
  std::cout << "bitset : " << std::hex << b1 << std::endl; 
  std::cout << "bitset[0] : " << std::hex << b1[0] << std::endl; 
  std::cout << "bitset[1] : " << std::hex << b1[1] << std::endl; 
  std::cout << "bitset[2] : " << std::hex << b1[2] << std::endl;
  std::cout << "c1` : " << std::hex << (unsigned int)outc << std::endl; 

  for(auto& iter : byteArray){
    temp = std::bitset<8>(iter);
    std::cout << "output] vector : " << std::hex << (unsigned int)iter << std::endl; 
    std::cout << "output] vector : " << std::hex << temp << std::endl; 
  }
  std::cout << "short : " << std::hex << _short << std::endl; 
  std::cout << "unsigned short : " << std::hex << _unsigned_short << std::endl; 
  std::cout << "int : " << std::hex << _int << std::endl; 
  std::cout << "unsigned int : " << std::hex << _int<< std::endl; 
  std::cout << "long long : " << std::hex << _long_long << std::endl; 
  std::cout << "unsigned long long : " << std::hex << _unsigned_long_long << std::endl; 

  std::cout << "hiHI" << std::endl;
  std::vector<unsigned char> ret = BitConverter::GetBytes(_unsigned_int);
  for(auto iter : ret){
    temp = std::bitset<8>(iter);
    std::cout << "bytes] vector : " << std::hex << (unsigned int)iter << std::endl; 
    std::cout << "bytes] vector : " << std::hex << temp << std::endl; 
  }

}


// ========================= MAIN FUNCTION =============================
// Main Function
int main(int argc, char* argv[])
{
  std::cout << "=== Main Program Starts. ===" << std::endl;

  bitConverterTest();
//  bitArrayCopyTest();

  return 0;
}
