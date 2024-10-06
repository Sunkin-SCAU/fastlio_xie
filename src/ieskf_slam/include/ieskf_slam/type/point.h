#pragma once
#ifndef PCL_NO_PRECOMPILE
#define PCL_NO_PRECOMPILE 
#endif

#include <pcl/impl/pcl_base.hpp>
#include <pcl/pcl_base.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>



namespace IESKFSlam{
  struct EIGEN_ALIGN16 Point{//第一步：自定义点云结构，EIGEN_ALIGN16用于确保结构或类的实例在内存中以16字节为边界对齐。
    PCL_ADD_POINT4D;//x y z w 最后一个一般是代表缩放 用于填充齐次坐标
    float intensity;
    std::uint32_t offset_time;
    std::int32_t ring;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;//这是一个宏，用来确保自定义类型能够适用于Eigen需要的内存对齐。
  };
}

POINT_CLOUD_REGISTER_POINT_STRUCT(IESKFSlam::Point,//第二步： 注册这个点结构

    (float, x, x)
    (float, y, y)
    (float, z, z)
    (float, intensity, intensity)
    (std::uint32_t, offset_time, offset_time)
    (std::int32_t, ring, ring)
)