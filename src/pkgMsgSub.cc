#include <bits/stdc++.h>
#include <fcntl.h>

#include "ros/ros.h"
#include "writeLog.h"
#include "wrt/CoastLine.h"
#include "wrt/DetectingResult.h"
#include "wrt/GridMap.h"
#include "wrt/Map.h"
#include "wrt/Obstacle.h"
#include "wrt/PredictWayPointArray.h"
#include "wrt/Region.h"
#include "wrt/Situation.h"
#include "wrt/Task.h"
#include "wrt/WRT.h"
#include "wrt/WayPointArray.h"

using namespace std;

// void callback(const std_msgs::String::ConstPtr& msg) {
//     FILE* filePtr = fopen("/home/xch/trapy27/data1.csv", "wr+");
//     string res = msg->data.c_str();
//     cout << res << endl;
//     fwrite(res.c_str(), strlen(res.c_str()), 1, filePtr);
// }

/**
 * 名称：Task
结构定义：
Int16 taskid
Int16 taskType   
String taskDescription  //任务描述
WRT[] wrt  //艇群
Int16 wrtHeaderID   //首艇id
Int16 taskState  //任务状态

wrt:
Int16 wrt_id
String name
Int16 type  //0 货船， 1 无人艇
int16 motorType //0电动  1 柴动
String typeName  //类型名称
Int32 enquiptmenType //所属装备类型
Int32 att  //所属阵营
Float32 yaw  //首向角度
Float32  visionAngle //视角大小
Float32 visionRange  //视角范围
Bool isLive  //是否存活
Float32 healthpoint  //当前血量
Int16 role  //角色：0 群首，1 组员
Int 16 state  //0 ready, 1 running, 2 stop 
int16 engineType  //0 电动   1 柴动
 * 
 * */
void taskCallback(const wrt::Task::ConstPtr& msg) {
    int file = open("/home/xunshuidezhu/log/task.log", O_CREAT | O_RDWR | O_APPEND, 0777);
    string log;
    string desc = msg->taskDescription;
    log += desc;
    log += " ";
    string id = to_string(msg->taskid);
    log += id;
    log += " ";
    string state = to_string(msg->taskState);
    log += state;
    log += " ";
    string type = to_string(msg->taskType);
    log += type;
    log += " ";
    vector<wrt::WRT> wrts = msg->wrt;
    string att = to_string(wrts[0].att);
    log += att;
    log += " ";
    string engineType = to_string(wrts[0].motorType);
    log += engineType;
    log += " ";
    string healthPoint = to_string(wrts[0].healthpoint);
    log += healthPoint;
    log += " ";
    string name = wrts[0].name;
    log += name;
    log += " ";
    string role = to_string(wrts[0].role);
    log += role;
    log += " ";
    string headerId = to_string(msg->wrtHeaderID);
    log += headerId;
    log += " ";
    cout << "write log" << endl;
    cout << "task log: " << log << endl;
    write(file, log.c_str(), log.size());
    close(file);
}

/**
 * 2.8#规划航迹
名称：WayPointArray
结构定义：
WRT wrt
Int speed
Float angle

 * **/
void wayPointCallback(const wrt::WayPointArray::ConstPtr& msg) {
    int file = open("/home/xunshuidezhu/log/task.log", O_CREAT | O_RDWR | O_APPEND, 0777);
    string log;
    string speed = to_string(msg->speed);
    log += speed;
    log += " ";
    string angle = to_string(msg->angle);
    log += angle;
    log += " ";
    write(file, log.c_str(), log.size());
    cout << "write log" << endl;
    cout << "wayPointArray log: " << log << endl;
    close(file);
}
/**
2.8-1#预测航迹
名称：PredictWayPointArray
结构定义：
WRT wrt
WayPoint[] waypoints

2.7 航迹点
名称：WayPoint
结构定义：
float64 latitude
float64 longitude
float64 altitude
**/
void predictCallback(const wrt::PredictWayPointArray::ConstPtr& msg) {
    int file = open("/home/xunshuidezhu/log/task.log", O_CREAT | O_RDWR | O_APPEND, 0777);
    string log;
    vector<wrt::WayPoint> wayPoints = msg->waypoints;
    string latitude = to_string(wayPoints[0].latitude);
    log += latitude;
    log += " ";
    string longitude = to_string(wayPoints[0].longitude);
    log += longitude;
    log += " ";
    string altitude = to_string(wayPoints[0].altitude);
    log += altitude;
    log += " ";
    cout << "write log" << endl;
    cout << "predictCallback log: " << log << endl;
    write(file, log.c_str(), log.size());
    close(file);
}

/**
 * 2.23# 态势
名称：Situation
结构定义：
GridMap map
WRT[] wrt_list
Task task
2.25沙盒地图
名称：GridMap
结构定义：

Int32 size   //地图矩阵大小
Int32 topLeftLoc  //做顶点网格中心点经纬度
Int32 gridType  //网格类型  1 六边形
Int32 gridInterval  //两个相邻网格距离
GridCell[] cell   //网格列表

2.26沙盒网格
名称：GridCell
结构定义：

Uint64  id   //在地图中的编号
Int32  type  //类型 1 水域 2 陆地  3 山
Float32 lat   //中心经度
Float32 lan   //中心纬度
Int32 alt    //地势海拔
 * 
 * */

void situationCallback(const wrt::Situation::ConstPtr& msg) {
    int file = open("/home/xunshuidezhu/log/task.log", O_CREAT | O_RDWR | O_APPEND, 0777);
    string log;
    wrt::GridMap gridMap = msg->map;
    auto cells = gridMap.cell;
    string id = to_string(cells[0].id);
    log += id;
    log += " ";
    string type = to_string(cells[0].type);
    log += type;
    log += " ";
    string lat = to_string(cells[0].lat);
    log += lat;
    log += " ";
    string lan = to_string(cells[0].lan);
    log += lan;
    log += " ";
    string alt = to_string(cells[0].alt);
    log += alt;
    log += " ";
    /**Int32 size   //地图矩阵大小
Int32 topLeftLoc  //做顶点网格中心点经纬度
Int32 gridType  //网格类型  1 六边形
Int32 gridInterval  //两个相邻网格距离
     * */
    log += gridMap.topLeftLoc;
    log += " ";
    log += to_string(gridMap.gridType);
    log += " ";
    log += to_string(gridMap.gridInterval);
    log += " ";
    log += gridMap.size;
    log += " ";
    cout << "write log" << endl;
    cout << "situation log: " << log << endl;
    write(file, log.c_str(), log.size());
    close(file);
}
// void mapCallback(const wrt::Map::ConstPtr& msg) {
//     int file = open("/home/xunshuidezhu/log/map.log", O_CREAT | O_APPEND | O_RDWR, 0777);
//     string log;
//     vector<wrt::CoastLine> coastLines = msg->coast.coast_lines;
//     log += to_string(coastLines[0].start_point.x);
//     log += " ";
//     log += to_string(coastLines[0].start_point.y);
//     log += " ";
//     msg->iland;
//     msg->obstacle;
// }

/**
 * 2.10探测结果
名称：DetectingResult
结构定义：
Int type  //0军舰  1民船  2岛礁  3灯塔  4浮标
 * */

struct Data {
    string startTime = "2020-10-09 13:20:22 ";
    string endTime = "2020-10-09 13:30:22 ";
    string localTime = "2020-10-10 12:12:12 ";
    string wrtId = "1 ";
    //duofangxiang
    string duoFangXiang = "1 ";
    //duojiaodu
    string duoJiaoDu = "1 ";
    string bearing = "1 ";  //方向
    string speed = "1 ";    //航速
    //健康状态
    string health = "- ";
    //油料状态
    string oil = "- ";
    //雷达状态
    string lidar = "- ";
    //电池状态
    string battery = "- ";
    //摄像头状态
    string camera = "- ";
    //当前时间 摄像头拍摄的图片地址
    string url = "/images ";
};

void detecingCallback(const wrt::DetectingResult::ConstPtr& msg) {
    int file = open("/home/xunshuidezhu/log/task.log", O_CREAT | O_RDWR | O_APPEND, 0777);
    string log;
    log += to_string(msg->type);
    log += " ";

    Data data;
    log += data.startTime;
    log += data.endTime;
    log += data.localTime;
    log += data.wrtId;
    log += data.duoFangXiang;
    log += data.duoJiaoDu;
    log += data.bearing;
    log += data.speed;
    log += data.health;
    log += data.oil;
    log += data.lidar;
    log += data.battery;
    log += data.camera;
    log += data.url;

    cout << "write log" << endl;
    cout << "detecting log " << log << endl;

    log += "\n";
    write(file, log.c_str(), log.size());
    close(file);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "pkgMsgSub");
    ros::NodeHandle nh;

    int file = open("/home/xunshuidezhu/log/task.log", O_CREAT | O_APPEND | O_RDWR, 0777);

    ros::Subscriber taskSub = nh.subscribe("taskTopic", 1000, taskCallback);
    ros::Subscriber predictSub = nh.subscribe("predictTopic", 1000, predictCallback);
    ros::Subscriber wayPointSub = nh.subscribe("wayPointTopic", 1000, wayPointCallback);
    ros::Subscriber situationSub = nh.subscribe("situationTopic", 1000, situationCallback);
    ros::Subscriber detecingSub = nh.subscribe("detectingTopic", 1000, detecingCallback);
    
    //ros::Subscriber mapSub = nh.subscribe("mapTopic", 1000, mapCallback);
    ros::spin();
    return 0;
}