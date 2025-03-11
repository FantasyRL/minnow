#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : 
capacity_( capacity ),
isClosed(false),
fifo(),
pushed(0),
removed(0) {}// 这里还要按顺序来初始化

void Writer::push( string data )
{
  for (char c : data)
  {
    if(!isClosed&& available_capacity()!=0){
      fifo.push(c);// 在当前容量范围内推入流
      pushed++;
    }else{
      break;
    } 
  }
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
  return capacity_ - fifo.size();
}

uint64_t Writer::bytes_pushed() const
{
  return pushed;
}



string_view Reader::peek() const
{
    if (fifo.empty()) {
        return {}; // 返回空的 string_view
    }
    return {&fifo.front(), fifo.size()}; // 返回整个缓冲区的视图
}


void Reader::pop( uint64_t len )
{
  (void)len; // Your code here.
  while(len--){
    fifo.pop();
    removed++;
  }
}

bool Reader::is_finished() const
{
  return (isClosed && fifo.empty()) ? true : false;// 当关闭通道并且读取完毕缓冲区时就标记为finish
}

uint64_t Reader::bytes_buffered() const
{
  return fifo.size();
}

uint64_t Reader::bytes_popped() const
{
  return removed;
}

