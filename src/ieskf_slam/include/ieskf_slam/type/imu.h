#pragma once
#include <Eigen/Dense>
#include <ieskf_slam/type/timestamp.h>

namespace IESKFSlam
{
  class IMU
  {
    public:
      Eigen::Vector3d acceleration = Eigen::Vector3d::Zero();//加速度
      Eigen::Vector3d gyroscale = Eigen::Vector3d::Zero();//角速度
      TimeStamp time_stamp;

      void clear()
      {
        acceleration = Eigen::Vector3d::Zero();
        gyroscale = Eigen::Vector3d::Zero();
        time_stamp = 0;
      }

      IMU operator +(const IMU& imu){
        IMU res;
        res.acceleration = this->acceleration+imu.acceleration;
        res.gyroscale = this->gyroscale+imu.gyroscale;
        return res;
      }
      //这里是重载加法运算符，a+b 那么this指向的是a，传入的imu指向b  谁调用，this指向谁 “+”前的为调用对象

      IMU operator *(double k){
        IMU res;
        res.acceleration = this->acceleration * k;
        res.gyroscale = this->gyroscale * k;
        return res;
      }

      IMU operator /(double k){
        IMU res;
        res.acceleration = this->acceleration / k;
        res.gyroscale = this->gyroscale / k;
        return res;
      }

      friend std::ostream& operator <<(std::ostream& ostream,const IMU& imu)
      {
        ostream<<"imu_time"<<imu.time_stamp.sec()<<"s | imu_acc: "<<imu.acceleration.transpose()<<" |imu_gyro: "<<imu.gyroscale.transpose();
        return ostream;
      }


  };
} // namespace IESKFSlam
