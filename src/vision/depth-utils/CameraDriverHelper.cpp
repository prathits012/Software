#include "vision/depth-utils/CameraDriverHelper.hpp"

#include "common/messages/depth_image_t.hpp"
#include "common/messages/point_cloud_t.hpp"
#include "common/messages/point_t.hpp"
#include "common/messages/rgb_image_t.hpp"

#include "vision/depth-utils/utilities.hpp"

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <iostream>
#include <vector>

using maav::vision::wrapInDepthMat;
using maav::vision::wrapInRGBMat;
using std::string;
using std::thread;
using std::vector;
using std::chrono::milliseconds;

using pcl::PointCloud;
using pcl::PointXYZ;

namespace maav::vision
{
const string CameraDriverHelper::FORMAT_IPC = "ipc";

CameraDriverHelper::CameraDriverHelper(YAML::Node config, const string& zcm_format,
    const string& rgbd_channel_in, const string& pointcloud_channel_in, bool rgbd, bool pointcloud)
    : public_rgbd_(rgbd),
      publish_pc_(pointcloud),
      zcm_{zcm_format},
      camera_(config),
      running_(false),
      rgbd_channel_(rgbd_channel_in),
      pointcloud_channel_(pointcloud_channel_in)
{
    if (!zcm_.good()) std::cout << "ZCM bad" << std::endl;
}

void CameraDriverHelper::beginRecording()
{
    running_ = true;

    publish_thread_ = thread(publish, this);
}

void CameraDriverHelper::endRecording()
{
    if (running_)
    {
        running_ = false;
        publish_thread_.join();
    }
}
void CameraDriverHelper::publish(CameraDriverHelper* cd_ptr)
{
    while (cd_ptr->isRunning())
    {
        cd_ptr->camera_.loadNext();
        if (cd_ptr->public_rgbd_) rgbdPublish(cd_ptr);
        if (cd_ptr->publish_pc_) pointcloudPublish(cd_ptr);
    }
}

void CameraDriverHelper::rgbdPublish(CameraDriverHelper* cd_ptr)
{
    rgbd_image_t rgbd;

    rgbd.rgb_image.width = cd_ptr->camera_.getStreamWidth();
    rgbd.rgb_image.height = cd_ptr->camera_.getStreamHeight();
    rgbd.rgb_image.size = rgbd.rgb_image.width * rgbd.rgb_image.height * 3;
    const int8_t* raw_color = reinterpret_cast<const int8_t*>(cd_ptr->camera_.getRawColor());
    rgbd.rgb_image.raw_image.assign(raw_color, raw_color + rgbd.rgb_image.size);

    rgbd.depth_image.width = cd_ptr->camera_.getStreamWidth();
    rgbd.depth_image.height = cd_ptr->camera_.getStreamHeight();
    rgbd.depth_image.size = rgbd.depth_image.width * rgbd.depth_image.height;
    const int16_t* raw_depth = reinterpret_cast<const int16_t*>(cd_ptr->camera_.getRawDepth());
    rgbd.depth_image.raw_image.assign(raw_depth, raw_depth + rgbd.depth_image.size);

    rgbd.utime = cd_ptr->camera_.getUTime();

    cd_ptr->zcm_.publish(cd_ptr->rgbd_channel_, &rgbd);
}

void CameraDriverHelper::pointcloudPublish(CameraDriverHelper* cd_ptr)
{
    PointCloud<PointXYZ>::Ptr cloud;
    cloud = cd_ptr->camera_.getPointCloudBasic();

    point_cloud_t pcd;
    pcd.size = static_cast<int>(cloud->size());
    pcd.point_cloud.reserve(cloud->size());

    for (PointXYZ& p : *cloud)
    {
        point_t np;
        np.x = p.x;
        np.y = p.y;
        np.z = p.z;

        pcd.point_cloud.push_back(np);
    }

    pcd.utime = cd_ptr->camera_.getUTime();

    cd_ptr->zcm_.publish(cd_ptr->pointcloud_channel_, &pcd);
}
}  // namespace maav::vision