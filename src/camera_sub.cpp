#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>
#include <bits/stdc++.h>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
using namespace std;
int globalFlag = 0;

void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
  try {
    //bgr8
    cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
    globalFlag++;
    cv::Mat img;
    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
    cv_ptr->image.copyTo(img);

    // cv::Mat matrixJprg = cv::imdecode(cv::Mat(data), 1);
    // IplImage iplIamge(img);
    std::string picName = "/home/xch/test/picture/junjian (" + to_string(globalFlag) + ").jpg"; 
    std::string tmpName = picName + "\n";
    FILE* filePtr = fopen("/home/xch/test/log/shipLog.log", "a+");
    fwrite(tmpName.c_str(), strlen(tmpName.c_str()), 1, filePtr);
    imwrite(picName, img);

    cvWaitKey(30);
  } catch (cv_bridge::Exception& e) {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;
  cv::namedWindow("算法集成平台--军舰数据");
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub =
      it.subscribe("camera/image", 1, imageCallback);
  ros::spin();
  cv::destroyWindow("算法集成平台--军舰数据");
}