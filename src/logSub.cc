#include <bits/stdc++.h>
#include <fcntl.h>

#include "ros/ros.h"
#include "wrt/Situation.h"

#define END_TIME 500

using namespace std;

class Log {
private:
    int fd;

public:
    Log(int file) : fd(file) {
    }

    void writeLog(string log) {
        write(fd, log.c_str(), log.size());
    }

    void logAdd(string& log, string desc) {
        desc += " ";
        log += desc;
    }

    void logList(string& log, string desc) {
        desc += ",";
        log += desc;
    }

    void logDelete(string& log) {
        log = log.substr(0, log.size() - 1);
    }

    void logAddBlock(string& log) {
        log += " ";
    }

    void logAddSpace(string& log) {
        log += "\n";
    }
};

string startTime;
string endTime;
int flag = 0;

void logCallback(const wrt::Situation::ConstPtr& msg) {
    int file = open("./log/ros.log", O_CREAT | O_RDWR | O_APPEND | O_CLOEXEC, 0777);
    Log log(file);

    string str;

    wrt::GridMap gridMap = msg->map;
    if (flag == 0) {
        startTime = msg->sysTime;
        //end unix timeStamp
        int endTimeVal = stoi(startTime) + END_TIME;
        endTime = to_string(endTimeVal);
        flag = 1;
    }

    log.logAdd(str, startTime);
    log.logAdd(str, endTime);
    log.logAdd(str, msg->sysTime);

    if (msg->activeTask == 0) {
        string taskName = "侦查" + startTime;
        log.logAdd(str, taskName);
    } else if (msg->activeTask == 1) {
        string taskName = "巡逻警戒" + startTime;
        log.logAdd(str, taskName);
    }

    log.logAdd(str, to_string(gridMap.cols));
    log.logAdd(str, to_string(gridMap.rows));
    log.logAdd(str, to_string(gridMap.topLeftLong));
    log.logAdd(str, to_string(gridMap.topLeftLat));
    log.logAdd(str, to_string(gridMap.gridType));
    log.logAdd(str, to_string(gridMap.gridInterval));
    log.logAdd(str, to_string(gridMap.zoomLevel));

    log.logAdd(str, to_string(msg->activeTask));

    vector<wrt::WRT> wrts = msg->wrt_list;
    wrt::WRT w = wrts[0];

    log.logAdd(str, to_string(w.wrt_id));
    log.logAdd(str, w.name);
    log.logAdd(str, to_string(w.type));
    log.logAdd(str, to_string(w.motorType));
    log.logAdd(str, w.typeName);
    log.logAdd(str, to_string(w.enquiptmenType));
    log.logAdd(str, to_string(w.att));
    log.logAdd(str, to_string(w.yaw));
    log.logAdd(str, to_string(w.visionAngle));
    log.logAdd(str, to_string(w.visionRange));
    log.logAdd(str, to_string(w.isLive));
    log.logAdd(str, to_string(w.healthpoint));
    log.logAdd(str, to_string(w.role));
    log.logAdd(str, to_string(w.state));

    wrt::Pos p = w.pos;

    log.logAdd(str, to_string(p.latitude));
    log.logAdd(str, to_string(p.longitude));
    log.logAdd(str, to_string(p.altitude));
    log.logAdd(str, to_string(p.velocity_x));
    log.logAdd(str, to_string(p.velocity_y));
    log.logAdd(str, to_string(p.velocity_z));

    log.logDelete(str);
    log.logAddBlock(str);

    str += "\n";
    cout << "write: " << str << endl;

    log.writeLog(str);
    close(file);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "logSub");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("situationTopic", 1000, logCallback);

    ros::spin();
}