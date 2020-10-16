#!/usr/bin/env python
# coding=utf-8

import rospy
from wrt.msg import Detection2DArray
from wrt.msg import WayPointArray
from sensor_msgs.msg import Image as ROSImage
from cv_bridge import CvBridge
import cv2
import numpy as np
import tensorflow as tf

class Prediction:
    def __init__(self):
        self.trackPrediction_pub = rospy.Publisher('trackPrediction', WayPointArray,queue_size = 1)
        self.detection_sub = rospy.Subscriber('detection2DArray', Detection2DArray,self.detection_callback,queue_size = 1)
        #初始化
    #消息到达时回调函数
    def detection_callback(self,detection_msg):
        # 处理数据
        print ('处理detection数据')
        trackPrediction_msg = WayPointArray()
        #处理数据得出结果
        '''
        '''
        self.trackPrediction_pub.publish(trackPrediction_msg)

rospy.init_node('trackPrediction_node')
track_prediction = Prediction()
rospy.spin()
