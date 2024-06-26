/**
 * @file    SensorsCalibApp.cpp
 *
 * @author  btran
 *
 */

#include <iostream>

#include <pcl/io/pcd_io.h>

#include <sensors_calib/sensors_calib.hpp>

namespace
{
using PointCloudType = pcl::PointXYZI;
using PointCloud = pcl::PointCloud<PointCloudType>;
using PointCloudPtr = PointCloud::Ptr;
}  // namespace

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: [app] [path/to/calibration/handler/data]" << std::endl;
        return EXIT_FAILURE;
    }

    // printf("here \n");
    const std::string PARAM_PATH = argv[1];

    // printf("here1 \n");
    perception::CalibrationHandlerParam param = perception::getCalibrationHandlerParam(PARAM_PATH);
    // printf("here2 \n");
    perception::CalibrationHandler<PointCloudType>::Ptr calibrationHandler(
        new perception::CalibrationHandler<PointCloudType>(param));

    // printf("here3 \n");
    auto transform = calibrationHandler->optimize();
    // printf("here4 \n");
    const auto visualizedImgs = calibrationHandler->drawPointCloudOnImagePlane(transform);
    // printf("here5 \n");
    const auto projectedClouds = calibrationHandler->projectOnPointCloud(transform);
    // printf("here6 \n");

    printf("x: %f[m], y: %f[m], z: %f[m], r: %f[deg], p: %f[deg], y_deg: %f[deg]\n", transform(0), transform(1),
           transform(2), transform(3) * boost::math::double_constants::radian,
           transform(4) * boost::math::double_constants::radian, transform(5) * boost::math::double_constants::radian);

    for (std::size_t i = 0; i < visualizedImgs.size(); ++i) {
        const auto& curImg = visualizedImgs[i];
        cv::imwrite("img" + std::to_string(i) + ".png", curImg);
    }

    for (std::size_t i = 0; i < projectedClouds.size(); ++i) {
        const auto& curCloud = projectedClouds[i];
        pcl::io::savePCDFileASCII("cloud" + std::to_string(i) + ".pcd", *curCloud);
    }

    return EXIT_SUCCESS;
}
