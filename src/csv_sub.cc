#include "ros/ros.h"
#include "std_msgs/String.h"

#include <bits/stdc++.h>

using namespace std;

void callback(const std_msgs::String::ConstPtr& msg) {
  FILE* filePtr = fopen("/home/xch/trapy27/data1.csv", "wr+");
  string res = msg->data.c_str();
  cout << res << endl;
  fwrite(res.c_str(), strlen(res.c_str()), 1, filePtr);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "csv_sub");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("csv", 1000, callback);

  ros::spin();
  return 0;
}