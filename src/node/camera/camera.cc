#include <ros/ros.h>
#include <string.h>

#include "wrt/Image.h"

int main(int argc, char** argv) {
  ros::init(argc, argv, "cameraNode");  // 节点名称
  ros::NodeHandle n;
  ros::Publisher imagePub = n.advertise<wrt::Image>("cameraImageTopic", 1000);
  ros::Rate loop_rate(10);

  while (ros::ok()) {
    wrt::Image imageMsg;
    //填充数据

    imagePub.publish(imageMsg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
