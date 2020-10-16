#include "ros/ros.h"
#include "std_msgs/String.h"

#include <bits/stdc++.h>

using namespace std;

void callback(const std_msgs::String::ConstPtr& msg) {
  FILE* filePtr = fopen("/home/xch/trapy27/data1.csv", "wr+");
  string res = msg->data.c_str();
  cout << res << endl;
  fwrite(res.c_str(), strlen(res.c_str()), 1, filePtr);
  system("cd /home/xch/trapy27 && gnome-terminal -e ./predict.sh | less");
  sleep(30);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "predict_sub");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("predict", 1000, callback);

  ros::spin();
  return 0;
}