#!/usr/bin/env python
#coding=utf-8
import rospy
from wrt.msg import GridMap
from wrt.msg import Detection2DArray

class ObjectRecongnition:
    def __init__(self):
        self.gridMap_sub = rospy.Subscriber('gridMap',GridMap,self.gridMap_callback,queue_size = 1)
        self.detection_pub = rospy.Publisher('detection2DArray', Detection2DArray, queue_size = 1)
    def gridMap_callback(self,gridMap_msg):
        #处理数据
        print ('objectRecongnition')
        print(gridMap_msg.size)
        print(gridMap_msg.topLeftLoc)
        print(gridMap_msg.gridType)
        print(gridMap_msg.gridInterval)
        for stateInfo in gridMap_msg.cell:
            print(stateInfo)
        detection_msg = Detection2DArray()
         #处理数据
    
        self.detection_pub.publish(detection_msg)


rospy.init_node('objRecognition_node')
objectRecongnition = ObjectRecongnition()
rospy.spin()