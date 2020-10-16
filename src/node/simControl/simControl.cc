#include <ros/ros.h>
#include <string.h>

#include "wrt/simControl.h"



int main(int argc, char** argv) {
  ros::init(argc, argv, "simControlNode");  // 节点名称
  ros::NodeHandle n;
  ros::Publisher simControlPub =
      n.advertise<wrt::simControl>("simControlTopic", 1000);
  ros::Rate loop_rate(10);

  while (ros::ok()) {
    wrt::simControl simControlMsg;
    //填充数据

    simControlPub.publish(simControlMsg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
