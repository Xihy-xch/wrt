#include <bits/stdc++.h>
#include <ros/ros.h>

#include "std_msgs/String.h"
#include "wrt/CoastLine.h"
#include "wrt/DetectingResult.h"
#include "wrt/Map.h"
#include "wrt/Obstacle.h"
#include "wrt/PredictWayPointArray.h"
#include "wrt/Region.h"
#include "wrt/Situation.h"
#include "wrt/Task.h"
#include "wrt/WRT.h"
#include "wrt/WayPointArray.h"

using namespace std;

/**
 * 1. ren wu guan li
 * 2. yu ce hang ji
 * 3. gui hua hang ji
 * 4. tai shi
 * 5. tan ce jie guo=
 * 6. shi pin tu xiang
 * **/
int main(int argc, char** argv) {
    ros::init(argc, argv, "pkgMsgNode");
    ros::NodeHandle nh;

    ros::Publisher taskPub = nh.advertise<wrt::Task>("taskTopic", 1000);
    ros::Publisher mapPub = nh.advertise<wrt::Map>("mapTopic", 1000);
    ros::Publisher wayPointArrayPub = nh.advertise<wrt::WayPointArray>("wayPointTopic", 1000);
    ros::Publisher predictPub = nh.advertise<wrt::PredictWayPointArray>("predictTopic", 1000);
    ros::Publisher situationPub = nh.advertise<wrt::Situation>("situationTopic", 1000);
    ros::Publisher detectingPub = nh.advertise<wrt::DetectingResult>("detectingTopic", 1000);

    ros::Rate loop_rate(0.1);

    while (ros::ok()) {
        //task
        wrt::Task task;
        wrt::WRT wrt;
        vector<wrt::WRT> wrts;
        wrts.push_back(wrt);
        task.wrt = wrts;
        task.taskDescription = "test";

        taskPub.publish(task);

        //map
        wrt::Map map;
        wrt::CoastLine costLine;
        costLine.start_point.x = 1;
        costLine.start_point.y = 1;
        costLine.start_point.z = 1;
        costLine.end_point.x = 2;
        costLine.end_point.y = 2;
        costLine.end_point.z = 2;
        wrt::CoastLineArray costLineArray;

        //region
        wrt::Region region;
        vector<float> vecs = {1.0, 2.0, 3.0};
        region.radius = vecs;
        vector<wrt::Region> regions;

        //obstacle
        wrt::Obstacle obstacle;
        obstacle.radius = vecs;
        vector<wrt::Obstacle> obstacles;

        vector<wrt::CoastLine> coastLines;
        costLineArray.coast_lines = coastLines;
        map.coast = costLineArray;
        map.iland = regions;
        map.obstacle = obstacles;

        mapPub.publish(map);

        //WayPointArray
        wrt::WayPointArray wayPointArray;
        wayPointArray.wrt = wrt;
        wayPointArray.speed = 1;
        wayPointArray.angle = 1.1;

        wayPointArrayPub.publish(wayPointArray);

        //predict
        wrt::WayPoint point;
        point.altitude = 1;
        point.latitude = 1;
        point.longitude = 1;
        wrt::PredictWayPointArray predictArray;
        vector<wrt::WayPoint> wayPoints{point};
        predictArray.waypoints = wayPoints;
        predictArray.wrt_id = 3;

        predictPub.publish(predictArray);

        //situation
        wrt::Situation situation;
        wrt::GridMap gridMap;
        wrt::GridCell gridCell;
        gridCell.alt = 1;
        gridCell.id = 1;
        gridCell.lan = 1;
        gridCell.lat = 1;
        gridCell.type = 1;
        gridMap.gridInterval = 1;
        gridMap.gridType = 1;
        gridMap.size = "23";
        gridMap.topLeftLoc = "45";
        gridMap.cell.push_back(gridCell);
        situation.map = gridMap;
        situationPub.publish(situation);

        //detecting
        wrt::DetectingResult detect;
        detect.type = 1;
        detectingPub.publish(detect);
        ros::spinOnce();
        loop_rate.sleep();
    }
}