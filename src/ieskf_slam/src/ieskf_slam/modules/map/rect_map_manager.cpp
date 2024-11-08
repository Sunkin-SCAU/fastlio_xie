//
// Created by xie on 24-10-27.
//
#include "ieskf_slam/modules/map/rect_map_manager.h"
#include "pcl/common/transforms.h"
#include "ieskf_slam/math/math.h"


namespace IESKFSlam
{
    RectMapManager::RectMapManager(const std::string &config_file_path, const std::string &prefix): ModuleBase(config_file_path,"RectMapManager")
    {
        local_map_ptr = pcl::make_shared<PCLPointCloud>();
    }

    RectMapManager::~RectMapManager()
    {
    }
    void RectMapManager::addScan(IESKFSlam::PCLPointCloudPtr curr_scan, const Eigen::Quaterniond &att_q,
                                 const Eigen::Vector3d &pos_t) {
        PCLPointCloud scan;
        pcl::transformPointCloud(*curr_scan,scan, compositeTransform(att_q,pos_t).cast<float>());
        *local_map_ptr+=scan;
    }
    void RectMapManager::reset() {
        local_map_ptr->clear();
    }

    PCLPointCloudPtr RectMapManager::getLocalMap() {
        return local_map_ptr;
    }
}