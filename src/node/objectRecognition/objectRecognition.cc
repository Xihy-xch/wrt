#include <ros/ros.h>
#include <string.h>

#include "wrt/Detection2D.h"
#include "wrt/Image.h"


//
void imageMsgCallback(const wrt::Image& imageMsg) {
  //处理数据
  std::cout << "处理imageMsg" << std::endl;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "objectRecognitionNode");  // 节点名称
  ros::NodeHandle n;
  ros::Subscriber cameraSub =
      n.subscribe("cameraImageTopic", 1000, imageMsgCallback);
  ros::Publisher detection2DPub =
      n.advertise<wrt::Detection2D>("detection2DTopic", 1000);
  ros::Rate loop_rate(10);

  while (ros::ok()) {
    wrt::Detection2D detection2DMsg;
    //填充数据

    detection2DPub.publish(detection2DMsg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
