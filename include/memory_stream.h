#ifndef BIT_BYTE_UTIL_MEMORY_STREAM_H_
#define BIT_BYTE_UTIL_MEMORY_STREAM_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdint>

namespace BBUtil {
  
enum class Origin {
  BEGIN,
  CURRENT,
  END
};

class MemoryStream 
{
public:
  MemoryStream();
//  MemoryStream(std::string str);
  MemoryStream(std::vector<uint8_t>& array);
  ~MemoryStream();

  void seek(int offset, Origin origin);

//  // For use as a stream.
//  void writeString(std::string& in);
//  std::string getStreamString();

  // For use as a byte array.
  void writeByte(uint8_t byte);
  void write(std::vector<uint8_t>& array, int offset, int size);
  uint8_t readByte();
  uint16_t readUInt16();
  int32_t readInt32();
  uint32_t readUInt32();
  int64_t readInt64();
  uint64_t readUInt64();
  
private:
//  std::stringstream _stream;    // Actual stream buffer to store data
  std::vector<uint8_t> _stream;    // Actual stream buffer to store data
  int _pos;        // Current pointing position in the array
//  int _length;     // Actual length of the storing bytes
//  int _capacity;   // Capacity to store the bytes
};

} // namespace BBUtil
#endif // BIT_BYTE_UTIL_MEMORY_STREAM_H_
