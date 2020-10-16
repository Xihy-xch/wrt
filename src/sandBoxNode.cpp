#include <ros/ros.h>
#include <string.h>
#include <wrt/GridCell.h>
#include <wrt/WayPointArray.h>
#include <wrt/simControl.h>

#include "std_msgs/String.h"
#include "wrt/GridMap.h"
#include "wrt/WRT.h"

using namespace std;

void simControlCallback(const wrt::simControl& simControlMsg) {
  //处理数据
  cout << "处理simControl" << endl;
}
void trackMsgCallback(const wrt::WayPointArray& trackMsg) {
  //处理数据
  cout << "处理trackMsg数据" << endl;
}
int main(int argc, char** argv) {
  ros::init(argc, argv, "sandBoxNode");  // 节点名称
  ros::NodeHandle n;
  ros::Subscriber simControl_sub =
      n.subscribe("simControl", 1000, simControlCallback);
  ros::Subscriber trackMsg_sub =
      n.subscribe("trackMsg", 1000, trackMsgCallback);
  ros::Publisher gridMap_pub = n.advertise<wrt::GridMap>("gridMap", 1000);
  ros::Rate loop_rate(10);

  while (ros::ok()) {
    wrt::GridMap gridMapMsg;
    //填充数据

    gridMap_pub.publish(gridMapMsg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
