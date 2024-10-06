#pragma once
#include <iostream>
#include "ieskf_slam/modules/modules_base.h"
#include "ieskf_slam/type/imu.h"
#include "ieskf_slam/type/base_type.h"//pointcloud
#include "ieskf_slam/type/pose.h"
// #include <deque>

namespace IESKFSlam
{
  class FrontEnd:private ModuleBase//私有继承，所有基类的成员在此都为private属性
  {
    public:
      using Ptr = std::shared_ptr<FrontEnd>;
      FrontEnd(const std::string &config_file_path,const std::string &prefix);
      ~FrontEnd();
      //传入数据

      void addImu(const IMU& imu);
      void addPointCloud(const PointCloud& pointcloud);
      void addPose(const Pose& pose);


      //跟踪
      bool track();
      //点云读取
      const PCLPointCloud &readCurrentPointCloud();



    private:
      std::deque<IMU> imu_deque;
      std::deque<PointCloud> pointcloud_deque;
      std::deque<Pose> pose_deque;
      PCLPointCloud current_pointcloud;

  };
} // namespace IESKFSlam
