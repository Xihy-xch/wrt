/************************************************************************************************
 * @date 2020-9-22
 * @author Xu HuanYu
 * @brief platform rosbag publish
 * **********************************************************************************************/

#include <bits/stdc++.h>
#include <ros/ros.h>

#include "geometry_msgs/Pose2D.h"
#include "std_msgs/String.h"
#include "wrt/BoundingBox2D.h"
#include "wrt/Classification2D.h"
#include "wrt/CoastLine.h"
#include "wrt/CoastLineArray.h"
#include "wrt/Detection2D.h"
#include "wrt/Detection2DArray.h"
#include "wrt/GridCell.h"
#include "wrt/GridMap.h"
#include "wrt/HealthyState.h"
#include "wrt/Map.h"
#include "wrt/Navi.h"
#include "wrt/ObjectHypothesis.h"
#include "wrt/ObjectHypothesisWithPose.h"
#include "wrt/Obstacle.h"
#include "wrt/Pos.h"
#include "wrt/Region.h"
#include "wrt/RegionArray.h"
#include "wrt/RegionOfInterest2D.h"
#include "wrt/RegionOfInterest2DArray.h"
#include "wrt/Situation.h"
#include "wrt/Task.h"
#include "wrt/WRT.h"
#include "wrt/WayPoint.h"
#include "wrt/WayPointArray.h"
#include "wrt/simControl.h"
#include "wrt/simNode.h"

using namespace std;

wrt::simNode createSimNode(short nodeId, string name, string description,
                           string ip, string port) {
  wrt::simNode node;
  node.nodeID = nodeId;
  node.description = description;
  node.name = name;
  node.IP = ip;
  node.port = port;

  return node;
}

struct Position {
  double latitude;
  double longitude;
  double altitude;

  Position(double x, double y, double z)
      : latitude(x), longitude(y), altitude(z) {}
};

struct Speed {
  float x;
  float y;
  float z;

  Speed(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

wrt::Pos createPos(Position position, Speed speed) {
  wrt::Pos pos;

  pos.altitude = position.altitude;
  pos.latitude = position.latitude;
  pos.longitude = position.longitude;

  pos.velocity_x = speed.x;
  pos.velocity_y = speed.y;
  pos.velocity_z = speed.z;

  return pos;
}

wrt::WRT createWrt() {
  wrt::WRT unManShip;

  unManShip.att = 1;
  unManShip.enquiptmenType = 1;
  unManShip.healthpoint = 100.0;
  unManShip.isLive = 1;
  unManShip.name = "ship";
  unManShip.role = 1;
  unManShip.state = 0;
  unManShip.type = 1;
  unManShip.typeName = "wurenting";
  unManShip.visionAngle = 10.5;
  unManShip.visionRange = 12.0;
  unManShip.wrt_id = 1;
  unManShip.yaw = 23.3;
}

wrt::HealthyState createHealthyState(int id, string desc) {
  wrt::HealthyState state;

  state.desciption = desc;
  state.healthyID = id;
}

wrt::Task createTask(int id, int type, string desc, vector<wrt::WRT> wrts,
                     int wrtHeaderID, int taskState) {
  wrt::Task task;

  task.taskid = id;
  task.taskType = type;
  task.taskDescription = desc;
  task.wrt = wrts;
  task.wrtHeaderID = wrtHeaderID;
  task.taskState = taskState;

  return task;
}

wrt::simControl createSimControl(int command, wrt::Task task,
                                 vector<wrt::simNode> nodes) {
  wrt::simControl control;

  control.activeTask = task;
  control.command = command;
  control.nodes = nodes;

  return control;
}

wrt::WayPoint createWayPoint(double x, double y, double z) {
  wrt::WayPoint point;

  point.latitude = x;
  point.longitude = y;
  point.altitude = z;

  return point;
}

wrt::WayPointArray createWayPoints(wrt::WRT ship,
                                   vector<wrt::WayPoint> points) {
  wrt::WayPointArray array;

  array.wrt = ship;
  array.waypoints = points;

  return array;
}

wrt::BoundingBox2D createBox(double x, double y) {
  geometry_msgs::Pose2D pose;
  wrt::BoundingBox2D box;

  pose.x = 1;
  pose.y = 1;
  pose.theta = 2;

  box.size_x = x;
  box.size_y = y;
  box.center = pose;

  return box;
}

wrt::ObjectHypothesis createObjectHypothesis(int id, double score) {
  wrt::ObjectHypothesis objectHypothesis;

  objectHypothesis.id = id;
  objectHypothesis.score = score;

  return objectHypothesis;
}

wrt::ObjectHypothesisWithPose createObjectHypothesisWithPose(double altitude, int id, double latitude, double longitude, double score) {
  wrt::ObjectHypothesisWithPose objectWithPos;

  objectWithPos.altitude;
  objectWithPos.id;
  objectWithPos.latitude;
  objectWithPos.longitude;
  objectWithPos.score;

  return objectWithPos;
}

wrt::Classification2D createClassification(
    vector<wrt::ObjectHypothesis> object) {
  wrt::Classification2D classification;

  classification.results = object;

  return classification;
}

wrt::Detection2D createDetection(vector<wrt::ObjectHypothesisWithPose> object,
                                 wrt::BoundingBox2D box, int type) {
  wrt::Detection2D detection;

  detection.bbox = box;
  detection.type = type;
  detection.results = object;

  return detection;
}

wrt::Detection2DArray createDetection2DArray(
    vector<wrt::Detection2D> detections) {
  wrt::Detection2DArray array;

  array.detections = detections;

  return array;
}

wrt::RegionOfInterest2D createRegionOfInterest2D(
    string label, float objectness, sensor_msgs::RegionOfInterest roi) {
  wrt::RegionOfInterest2D region;

  region.label = label;
  region.roi = roi;
  region.objectness = objectness;

  return region;
}

wrt::RegionOfInterest2DArray createRegionOfInterest2DArray(
    vector<wrt::RegionOfInterest2D> regions) {
  wrt::RegionOfInterest2DArray arrays;

  arrays.object_rois = regions;

  return arrays;
}

wrt::CoastLine createCoastLine(geometry_msgs::Point start,
                               geometry_msgs::Point end) {
  wrt::CoastLine coastLine;

  coastLine.start_point = start;
  coastLine.end_point = end;

  return coastLine;
}

wrt::CoastLineArray createCoastLineArrays(vector<wrt::CoastLine> lines) {
  wrt::CoastLineArray array;

  array.coast_lines = lines;

  return array;
}

wrt::Obstacle createObstacle(vector<geometry_msgs::Point> points,
                             vector<float> radius) {
  wrt::Obstacle obstacle;

  obstacle.points = points;
  obstacle.radius = radius;

  return obstacle;
}

wrt::Region createRegion(vector<geometry_msgs::Point> points,
                         vector<float> radius) {
  wrt::Region region;

  region.points = points;
  region.radius = radius;

  return region;
}

wrt::RegionArray createRegionArray(vector<wrt::Region> regions) {
  wrt::RegionArray array;

  array.list = regions;

  return array;
}

wrt::Map createMap(wrt::CoastLineArray coast, vector<wrt::Region> islands,
                   vector<wrt::Obstacle> obstacles) {
  wrt::Map map;

  map.coast = coast;
  map.iland = islands;
  map.obstacle = obstacles;

  return map;
}

wrt::Situation createSituation(wrt::Map map, vector<wrt::WRT> wrts) {
  wrt::Situation situation;

  situation.map = map;
  situation.wrt_list = wrts;

  return situation;
}

wrt::Navi createNavi(wrt::WRT ship, float bearing, float speed) {
  wrt::Navi navi;

  navi.bearing = bearing;
  navi.speed = speed;
  navi.wrt = ship;

  return navi;
}

wrt::GridCell createGridCell(int id, int type, string loc,
                             vector<wrt::WRT> ships, int alt) {
  wrt::GridCell gridCell;

  gridCell.alt = alt;
  gridCell.id = id;
  gridCell.loc = loc;
  gridCell.type = type;
  gridCell.wrtList = ships;

  return gridCell;
}

wrt::GridMap createGridMap(int size, int topLeftLoc, int gridType,
                           int gridInterval, vector<wrt::GridCell> cells) {
  wrt::GridMap gridMap;

  gridMap.cell = cells;
  gridMap.gridInterval = gridInterval;
  gridMap.gridType = gridType;
  gridMap.size = size;
  gridMap.topLeftLoc = topLeftLoc;

  return gridMap;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "platform_pub");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<std_msgs::String>("platform", 1000);

  ros::Rate loop_rate(0.1);

  while (nh.ok()) {
    std_msgs::String msg;

    auto simnode = createSimNode(1, "simNode", "simNode", "127.0.0.1", "11111");
    vector<wrt::simNode> nodes;
    nodes.push_back(simnode);
    auto ship = createWrt();
    vector<wrt::WRT> ships;
    ships.push_back(ship);
    auto state = createHealthyState(1, "jianKangGuanLi");
    Position position(10.0, 20.0, 30.0);
    Speed speed(12, 20, 11);
    auto pos = createPos(position, speed);
    auto task = createTask(1, 1, "task", ships, 1, 1);
    auto control = createSimControl(1, task, nodes);

    vector<wrt::WayPoint> pointArray;
    pointArray.push_back(createWayPoint(10, 20, 30));

    auto points = createWayPoints(ship, pointArray);

    geometry_msgs::Pose2D msgPose;
    auto box = createBox(1, 2);

    auto hypothesis = createObjectHypothesis(1, 99.0);
    vector<wrt::ObjectHypothesis> hypothesiss;
    hypothesiss.push_back(hypothesis);
    auto classification = createClassification(hypothesiss);
    wrt::ObjectHypothesisWithPose hypothesisWithPos = createObjectHypothesisWithPose(10.0, 1, 20.0, 30.0, 99.0);
    
    vector<wrt::ObjectHypothesisWithPose> objects;

    auto detection = createDetection(objects, box, 1);
    vector<wrt::Detection2D> detecs;
    detecs.push_back(detection);
    auto detections = createDetection2DArray(detecs);
    sensor_msgs::RegionOfInterest regionOfInterest;
    auto region = createRegionOfInterest2D("label", 1.0, regionOfInterest);

    vector<wrt::RegionOfInterest2D> regionsOfInterest;
    regionsOfInterest.push_back(region);
    auto regions = createRegionOfInterest2DArray(regionsOfInterest);
    
    geometry_msgs::Point start;
    geometry_msgs::Point end;

    auto coastLine = createCoastLine(start, end);

    vector<wrt::CoastLine> lines;
    lines.push_back(coastLine);

    auto coastLineArrays = createCoastLineArrays(lines);
    vector<geometry_msgs::Point> msgPoints;
    geometry_msgs::Point msgPoint;
    msgPoints.push_back(msgPoint);
    vector<float> radius;
    radius.push_back(1.1);

    auto obstacle = createObstacle(msgPoints, radius);

    auto region1 = createRegion(msgPoints, radius);
    vector<wrt::Region> wrtRegions;
    wrtRegions.push_back(region1);
    createRegionArray(wrtRegions);

    vector<wrt::Obstacle> obstacles;
    auto map = createMap(coastLineArrays, wrtRegions, obstacles);

    auto situation = createSituation(map, ships);

    auto navi = createNavi(ship, 2.2, 40);
    auto gridCell = createGridCell(1, 1, "12 13 14", ships, 30);
    vector<wrt::GridCell> gridCells;
    gridCells.push_back(gridCell);

    auto gridMap = createGridMap(1, 1, 1, 1, gridCells);

    pub.publish(gridMap);
    // pub.publish(navi);
    // pub.publish(situation);
    // pub.publish(map);
    // pub.publish(obstacle);
    // pub.publish(coastLineArrays);
    // pub.publish(coastLine);
    // pub.publish(regions);
    // pub.publish(detections);
    // pub.publish(classification);
    // pub.publish(points);
    // pub.publish(box);
    // pub.publish(hypothesis);
    // pub.publish(task);

    ros::spinOnce();
    loop_rate.sleep();
  }
}