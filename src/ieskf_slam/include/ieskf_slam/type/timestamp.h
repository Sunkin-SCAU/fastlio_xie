#pragma once
#include <iostream>

namespace IESKFSlam
{
  class TimeStamp
  {
  private:
    uint16_t nsec_;
    double sec_;

    public:
    TimeStamp(uint64_t insec = 0)//构造函数
    {
      nsec_ = insec;
      sec_ = static_cast<double>(insec)/1e9;
    }

    void fromSec(double isec){
      sec_ = isec;
      nsec_ = static_cast<uint64_t>(isec)*1e9;
    }

    void fromNsec(uint64_t insec = 0)
    {
      nsec_ = insec;
      sec_ = static_cast<double>(insec)/1e9;
    }

    const uint64_t& nsec()const {return nsec_;}//函数返回类型前的 const：这表明返回的引用指向的值是不可修改的。例如，你不能写 obj.nsec() = 10; 这样的代码，因为 nsec() 返回的是 nsec_ 的常量引用。
    const double& sec()const {return sec_;}
  
  };
} // namespace IESKFSlam
