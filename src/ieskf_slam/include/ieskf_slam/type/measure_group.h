//
// Created by xie on 24-10-27.
//

#pragma once
#include "ieskf_slam/type/imu.h"
#include "ieskf_slam/type/pointcloud.h"
#include <deque>

namespace IESKFSlam
{
    struct MeasureGroup{
        double lidar_begin_time;
        double lidar_end_time;
        std::deque<IMU> imus;
        PointCloud cloud;//结构体
    };
}