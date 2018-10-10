#ifndef BIT_BYTE_UTIL_BYTE_STREAM_H_
#define BIT_BYTE_UTIL_BYTE_STREAM_H_

#include <vector>
#include <cstdint>


namespace ByteUtil {

class ByteArray 
{
public:
  ByteArray();
  ByteArray(int capacity);
  ByteArray(std::vector<unsigned char> &byteArray);
  ByteArray(std::vector<unsigned char> &byteArray, int index, int count);
  ~ByteArray();


  enum class SeekOrigin {
    Begin = 0,
    Current = 1,
    End = 2
  };

  void reserve();
  uint8_t readByte();
  uint8_t read(std::vector<uint8_t> &out, int offset, int count);
  uint32_t seek(uint32_t offset, SeekOrigin);
  void writeByte(uint8_t byte);
  void write(std::vector<uint8_t> &in, int offset, int count);
  std::vector<uint8_t> getBuffer();

private:



private:
  std::vector<uint8_t> _buffer;   // Buffer containing the contents.
  int _position;    // Read/Write head.
  int _length;      // the length of byte stream.
  int _capacity;    // the length of usuable space of buffer.

};

} // ByteUtil
#endif // BIT_BYTE_UTIL_BYTE_STREAM_H_
