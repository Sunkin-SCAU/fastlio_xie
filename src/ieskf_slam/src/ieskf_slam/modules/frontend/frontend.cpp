#include "ieskf_slam/modules/frontend/frontend.h"
#include "pcl/common/transforms.h"


namespace IESKFSlam
{
  FrontEnd::FrontEnd(const std::string &config_file_path,const std::string & prefix):ModuleBase(config_file_path,"Front End Module")//实例化FronEnd之前初始化父类ModulBase ，传入两个参数
  {

  }
  FrontEnd::~FrontEnd()
  {

  }


  void FrontEnd::addImu(const IMU& imu)//添加imu数据
  {
    imu_deque.push_back(imu);
  }


  void FrontEnd::addPointCloud(const PointCloud& pointcloud)
  {
    pointcloud_deque.push_back(pointcloud);
    std::cout<<"receive cloud"<<std::endl;
  }

  void FrontEnd::addPose(const Pose& pose)
  {
    pose_deque.push_back(pose);
    std::cout<<"receive pose"<<std::endl;
  }

  bool FrontEnd::track()
  {
    if(pointcloud_deque.empty()||pose_deque.empty())//检查队列合法性
    {
      return false;
    }

    //寻找同一时刻的点云数据    越大证明时间越晚                  这里是比较pose和cloud两个队列，把队列中较早的数据丢弃
    
    while(!pose_deque.empty()&& pose_deque.front().time_stamp.nsec()<pointcloud_deque.front().time_stamp.nsec())
    {
      pose_deque.pop_front();
      std::cout<<"pose time older than pointcloud time, pop pose"<<std::endl;
    }
    if(pose_deque.empty())
    {
      return false;
    }

    while(!pointcloud_deque.empty()&& pose_deque.front().time_stamp.nsec()>pointcloud_deque.front().time_stamp.nsec())
    {
      pointcloud_deque.pop_front();
      std::cout<<"pointcloud time older than pose time, pop pointcloud"<<std::endl;
    }
    if(pointcloud_deque.empty())
    {
      return false;
    }

    //滤波---
    VoxelFilter vf;
    vf.setLeafSize(0.5,0.5,0.5);
    vf.setInputCloud(pointcloud_deque.front().cloud_ptr);
    vf.filter(*pointcloud_deque.front().cloud_ptr);


    Eigen::Matrix4f trans;
    trans.setIdentity();
    trans.block<3,3>(0,0) = pose_deque.front().rotation.toRotationMatrix().cast<float>();//是四元数
    trans.block<3,1>(0,3) = pose_deque.front().position.cast<float>();//position是向量
    pcl::transformPointCloud(*pointcloud_deque.front().cloud_ptr,current_pointcloud,trans);//转换点云的位姿  in,out,trans

    pointcloud_deque.pop_front();
    pose_deque.pop_front();
    return true;
  }


  const PCLPointCloud& FrontEnd::readCurrentPointCloud()
  {
    return current_pointcloud;//返回经过转换的位姿
  }
} // namespace IESKF_Slam
