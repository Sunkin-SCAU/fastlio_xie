//
// Created by xie on 24-10-27.
//

#pragma once
#include <Eigen/Dense>

namespace IESKFSlam
{//传入四元数和变换向量t，返回矩阵
    Eigen::Matrix4d compositeTransform(const Eigen::Quaterniond &q,const Eigen::Vector3d &t)
    {
        Eigen::Matrix4d ans;
        ans.setIdentity();
        ans.block<3,3>(0,0) = q.toRotationMatrix();
        ans.block<3,1>(0,3) = t;
        return ans;
    }
}