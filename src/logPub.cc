#include <bits/stdc++.h>
#include <ros/ros.h>

#include "wrt/Situation.h"

using namespace std;

int main(int argc, char** argv) {
    ros::init(argc, argv, "pkgMsgNode");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<wrt::Situation>("situationTopic", 1000);

    ros::Rate loop_rate(1);
    while (ros::ok()) {
       
        wrt::Situation situation;

        pub.publish(situation);
        ros::spinOnce();
        loop_rate.sleep();
    }
}