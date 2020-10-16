#include <bits/stdc++.h>
#include <ros/ros.h>

#include "wrt/DetectingResult.h"

using namespace std;

int main(int argc, char** argv) {
    ros::init(argc, argv, "detectionResultNode");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<wrt::DetectingResult>("detectionResultTopic", 1000);

    ros::Rate loop_rate(1);
    while (ros::ok()) {
       
        wrt::DetectingResult detect;

        detect.type = rand() % 4;
        cout << detect.type << endl;
        pub.publish(detect);
        ros::spinOnce();
        loop_rate.sleep();
    }
}