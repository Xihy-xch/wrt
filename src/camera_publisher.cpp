#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>

#include <opencv2/highgui/highgui.hpp>
#include <string>

using std::string;

int main(int argc, char** argv) {

  int a = 0;
  ros::init(a, nullptr, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);

  string junJianName = "/home/xch/yanzhengji/junjian (";

  ros::Rate loop_rate(1);

  while (nh.ok()) {
    for (int i = 1; i <= 70; i++) {
      string name = junJianName + std::to_string(i) + ").jpg";
      cv::Mat image = cv::imread(name, CV_LOAD_IMAGE_COLOR);
      sensor_msgs::ImagePtr msg =
          cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
      pub.publish(msg);
      ros::spinOnce();
      loop_rate.sleep();
    }
  }
}