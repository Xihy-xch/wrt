#include <ros/ros.h>
#include <string.h>
#include <wrt/GridCell.h>
#include <wrt/WayPointArray.h>
#include <wrt/simControl.h>

#include "std_msgs/String.h"
#include "wrt/GridMap.h"
#include "wrt/WRT.h"

using namespace std;

void simControl_callback(const wrt::simControl& simControl_msg) {
  //处理数据
  cout << "处理simControl" << endl;
}
void trackMsg_callback(const wrt::WayPointArray& track_msg) {
  //处理数据
  cout << "处理trackMsg数据" << endl;
}
int main(int argc, char** argv) {
  ros::init(argc, argv, "sandBox_node");  // 节点名称
  ros::NodeHandle n;
  ros::Subscriber simControl_sub =
      n.subscribe("simControl", 1000, simControl_callback);
  ros::Subscriber trackMsg_sub =
      n.subscribe("track_Msg", 1000, trackMsg_callback);
  ros::Publisher gridMap_pub = n.advertise<wrt::GridMap>("gridMap", 1000);
  ros::Rate loop_rate(10);

  while (ros::ok()) {
    wrt::GridMap gridMap_msg;
    //填充数据

    gridMap_pub.publish(gridMap_msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
