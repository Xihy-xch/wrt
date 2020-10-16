#include <bits/stdc++.h>
#include <ros/ros.h>
#include "std_msgs/String.h"

using namespace std;

int main(int argc, char** argv) {
  ros::init(argc, argv, "predict_pub");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<std_msgs::String>("predict", 1000);

  ros::Rate loop_rate(1);

  while (nh.ok()) {
    string res;

    for (int row = 0; row < 27; row++) {
      for (int i = 0; i < 10; i++) {
        string tmp = to_string(rand() % 100);
        tmp += " ";
        res += tmp;
      }
      res += '\n';
    }

    std_msgs::String msg;
    msg.data = res;
    
    pub.publish(msg);
    cout << "start predict" << endl;
    cout << msg << endl;
    ros::spinOnce();
    loop_rate.sleep();
  }
}