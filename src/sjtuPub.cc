#include <bits/stdc++.h>
#include <ros/ros.h>

#include "wrt/SJTU_OUT.h"

using namespace std;

int main(int argc, char** argv) {
    ros::init(argc, argv, "sjtuOutNode");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<wrt::SJTU_OUT>("sjtuOutTopic", 1000);

    ros::Rate loop_rate(1);
    while (ros::ok()) {
        wrt::SJTU_OUT sjtuOut;
        wrt::WRT_RUNTIME_INFO wrtInfo;

        wrtInfo.bearing = 90;
        wrtInfo.speed = 100;
        wrtInfo.wrt_id = 1;

        vector<wrt::WRT_RUNTIME_INFO> wrts;
        wrts.push_back(wrtInfo);

        sjtuOut.wrt_info = wrts;
       
        pub.publish(sjtuOut);
        ros::spinOnce();
        loop_rate.sleep();
    }
}