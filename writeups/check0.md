Checkpoint 0 Writeup
====================

My name: FanR

I collaborated with: **GPT Translation** and **GPT C++ Reference**

This lab took me about [3] hours to do. I **did** attend the lab session.

My secret code from section 2.1 was: [code here]

I was surprised by or edified to learn that: [describe]

Describe ByteStream implementation. [Describe data structures and
approach taken. Describe alternative designs considered or tested.
Describe benefits and weaknesses of your design compared with
alternatives -- perhaps in terms of simplicity/complexity, risk of
bugs, asymptotic performance, empirical performance, required
implementation time and difficulty, and other factors. Include any
measurements if applicable.]

- Describe ByteStream implementation
  
  Data structure: string
  Writer.push: string.append
  Reader.pop: string.erase
  Reader.peek: string_view provides a zero-copy access for string(may be it is a hint that I should use string as buffer?)

- alternative designs considered or tested
在最开始，我是打算通过**queue**去实现FIFO的，可是在第8个测试压力测试中由于只能逐个char处理跟不上速度

之后，我便换用了**string**，通过emplace_back erase append方法实现了能直接处理string的FIFO

- Optional: I had unexpected difficulty with: [describe]
  
在ubuntu22编译gcc与g++，用ppa很慢所以手动编译了


还有一个是学校上的c++屁用没有，面对这种小项目都有点犯晕

在写byteStream时，由于对C++的不熟悉，很多语法上的东西都是问gpt的，好在并没有让其提供思路，也算是独立思考完成了

但相比6.824来说，这个还是太简单了

- Optional: I think you could make this lab better by: [describe]

- Optional: I'm not sure about: [describe]

- Optional: I contributed a new test case that catches a plausible bug
  not otherwise caught: [provide Pull Request URL]