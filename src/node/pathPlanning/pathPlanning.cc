#include <ros/ros.h>
#include <string.h>

#include "wrt/GridMap.h"
#include "wrt/Detection2D.h"
#include "wrt/WayPointArray.h"

void wayPointArrayMsgCallback(const wrt::WayPointArray wayPointArray) {

}

void detectionMsgCallback(const wrt::Detection2D detection) {

}

void gridMapMsgCallback(const wrt::GridMap gridMap) {

}

int main(int argc, char** argv) {
  ros::init(argc, argv, "pathPlanningNode");  

  ros::NodeHandle n;

  ros::Subscriber wayPointArraySub = n.subscribe("wayPointArrayTopic", 1000, wayPointArrayMsgCallback);
  ros::Subscriber detectionSub = n.subscribe("detection2DTopic", 1000, detectionMsgCallback);
  ros::Subscriber gridMapSub = n.subscribe("gridMapTopic", 1000, gridMapMsgCallback);

  ros::Publisher wayPointPub = n.advertise<wrt::WayPointArray>("wayPointArrayTopic", 1000);
  
  ros::Rate loop_rate(10);

  while (ros::ok()) {
    wrt::WayPointArray wayPointArray;
    //填充数据
    
    wayPointPub.publish(wayPointArray);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
