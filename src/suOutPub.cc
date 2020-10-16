#include <bits/stdc++.h>
#include <ros/ros.h>

#include "wrt/SU_OUT.h"

using namespace std;

int main(int argc, char** argv) {
    ros::init(argc, argv, "suOutNode");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<wrt::SU_OUT>("suOutTopic", 1000);

    ros::Rate loop_rate(1);
    while (ros::ok()) {
        wrt::SU_OUT suOut;
        wrt::WRT_RUNTIME_INFO wrtInfo;

        wrtInfo.bearing = 90;
        wrtInfo.speed = 100;
        wrtInfo.wrt_id = 1;

        vector<wrt::WRT_RUNTIME_INFO> wrts;
        wrts.push_back(wrtInfo);

        suOut.wrt_info = wrts;
       
        pub.publish(suOut);
        ros::spinOnce();
        loop_rate.sleep();
    }
}