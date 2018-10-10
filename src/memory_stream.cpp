#include "memory_stream.h"

#include "bit_converter.h"


namespace BBUtil {

MemoryStream::MemoryStream()
  : _pos(0), _length(0), _capacity(0)
{
}

//MemoryStream::~MemoryStream(std::string str)
//{
//}

MemoryStream::MemoryStream(std::vector<uint8_t>& array)
{
  _stream = array;
}

MemoryStream::~MemoryStream()
{
}

//void MemoryStream::writeString(std::string& in)
//{
//}

void MemoryStream::writeByte(uint8_t byte)
{
  _stream.push_back(byte);
}

void MemoryStream::write(std::vector<uint8_t>& array, int offset, int size)
{
  std::copy(array.begin() + offset, array.begin() + offset + size, _stream.end());
}

uint8_t MemoryStream::readByte()
{
  return _stream[_pos++]; 
}

uint16_t MemoryStream::readUInt16()
{
  auto ret = BytesToUInt16(_stream, _pos);
  _pos += 2;
  return ret;
}

int32_t MemoryStream::readInt32()
{
  auto ret = BytesToInt32(_stream, _pos);
  _pos += 4;
  return ret;
}

uint32_t readUInt32()
{
  auto ret = BytesToUInt32(_stream, _pos);
  _pos += 4;
  return ret;
}

int64_t readInt64()
{
  auto ret = BytesToInt64(_stream, _pos);
  _pos += 8;
  return ret;
}

uint64_t readUInt64()
{
  auto ret = BytesToUInt64(_stream, _pos);
  _pos += 8;
  return ret;
}
} // namespace BBUtil
