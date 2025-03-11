#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : 
capacity_( capacity ),
isClosed(false),
buffer(),
pushed(0),
removed(0) {}// 这里还要按顺序来初始化

void Writer::push( string data )
{
  

  // for (char c : data)
  // {
  //   if(!isClosed&& available_capacity()!=0){
  //     buffer.push_back(c);// 在当前容量范围内推入流
  //     pushed++;
  //   }else{
  //     return;
  //   } 
  // }

  if (isClosed||available_capacity()==0) {
    return;
  }
  
  uint64_t wc=min(available_capacity(),data.size());
  buffer.append(data.data(),wc);
  pushed+=wc;
}


void Writer::close()
{
  isClosed=true;
}

bool Writer::is_closed() const
{
  return isClosed;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer.size();
}

uint64_t Writer::bytes_pushed() const
{
  return pushed;
}



string_view Reader::peek() const
{
    if (buffer.empty()) {
        return {}; // 返回空的 string_view
    }
    return buffer; // 返回整个缓冲区的视图
}


void Reader::pop( uint64_t len )
{
  uint64_t actual_len = ( len > buffer.size() ) ? buffer.size() : len;

  // 移除 buffer_ 前 actual_len 个字符
  buffer.erase( 0, actual_len );
  removed += actual_len;
}

bool Reader::is_finished() const
{
  return isClosed && buffer.empty();// 当关闭通道并且读取完毕缓冲区时就标记为finish
}

uint64_t Reader::bytes_buffered() const
{
  return buffer.size();
}

uint64_t Reader::bytes_popped() const
{
  return removed;
}

