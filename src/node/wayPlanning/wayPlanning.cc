#include <ros/ros.h>
#include <string.h>

#include "wrt/GridMap.h"
#include "wrt/simControl.h"
#include "wrt/Situation.h"
#include "wrt/PredictWayPointArray.h"

void gridMapMsgCallback(const wrt::GridMap gridMap) {

}


int main(int argc, char** argv) {
  ros::init(argc, argv, "wayPlanningNode");  

  ros::NodeHandle n;

  ros::Subscriber gridMapSub = n.subscribe("gridMapTopic", 1000, gridMapMsgCallback);
  
  ros::Publisher wayPointArrayPub = n.advertise<wrt::PredictWayPointArray>("wayPointArrayTopic", 1000);
  
  ros::Rate loop_rate(10);

  while (ros::ok()) {
    wrt::PredictWayPointArray wayPointArray;
    
    
    wayPointArrayPub.publish(wayPointArray);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
