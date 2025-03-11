#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include<queue>

class Reader;
class Writer;

class ByteStream
{
public:
  explicit ByteStream( uint64_t capacity );

  // 辅助函数（已提供）用于访问 ByteStream 的 Reader 和 Writer 接口
  Reader& reader();
  const Reader& reader() const;
  Writer& writer();
  const Writer& writer() const;

  void set_error() { error_ = true; };       // 标记流发生错误
  bool has_error() const { return error_; }; // 判断流是否发生过错误

protected:
  // 请将任何额外的状态添加到 ByteStream，而不要添加到 Writer 和 Reader 接口中
  uint64_t capacity_; 
  bool error_ {};
  bool isClosed;
  std::string buffer;
  uint64_t pushed;
  uint64_t removed;
};

class Writer : public ByteStream
{
public:
  void push( std::string data ); // 推送数据到流中，但仅限于当前可用容量允许的范围
  void close();                  // 标记流已关闭，表示不会再有新的写入

  bool is_closed() const;              // 判断流是否已关闭
  uint64_t available_capacity() const; // 查询当前可用的流容量（还可推送多少字节）
  uint64_t bytes_pushed() const;       // 查询累计推送到流中的总字节数
};

class Reader : public ByteStream
{
public:
  std::string_view peek() const; // 查看缓冲区中的下一个字节（但不移除）
  void pop( uint64_t len );      // 移除缓冲区中的 `len` 个字节

  bool is_finished() const;        // 判断流是否已结束（已关闭且所有数据已被读取）
  uint64_t bytes_buffered() const; // 查询当前缓冲区中尚未读取的字节数
  uint64_t bytes_popped() const;   // 查询累计从流中移除的字节总数
};

/*
 * read: 一个（已提供的）辅助函数，允许从 ByteStream Reader 读取最多 `max_len` 字节，
 * 并将其存入字符串 `out` 中。
 */
void read( Reader& reader, uint64_t max_len, std::string& out );


