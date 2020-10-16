#include <ros/ros.h>
#include <string.h>

#include "wrt/WayPointArray.h"
#include "wrt/simControl.h"
#include "wrt/Situation.h"

void wayPointArrayMsgCallback(const wrt::WayPointArray wayPointArray) {

}

void simControlMgsCallback(const wrt::simControl control) {

}

int main(int argc, char** argv) {
  ros::init(argc, argv, "sandBoxNode");  

  ros::NodeHandle n;

  ros::Subscriber wayPointArraySub = n.subscribe("wayPointArrayTopic", 1000, wayPointArrayMsgCallback);
  ros::Subscriber simControl = n.subscribe("simControlTopic", 1000, simControlMgsCallback);
  
  ros::Publisher situationPub = n.advertise<wrt::Situation>("situationTopic", 1000);
  
  ros::Rate loop_rate(10);

  while (ros::ok()) {
    wrt::Situation situationMsg;
    //填充数据
    
    situationPub.publish(situationMsg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
