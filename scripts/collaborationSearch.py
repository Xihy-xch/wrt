#!/usr/bin/env python
#coding=utf-8
import rospy

from wrt.msg import WayPointArray

class CollaborationSearch:
    def __init__(self):
        self.trackPrediction_sub = rospy.Subscriber('trackPrediction', WayPointArray,self.trackPrediction_callback, queue_size = 1)
        self.trackMsg_pub = rospy.Publisher('track_Msg', WayPointArray,queue_size = 1)
    def trackPrediction_callback(self,trackPrediction_msg):
        #处理数据
        print ('处理trackPrediction数据')
        trackMsg_msg = WayPointArray()
        #处理数据
        self.trackMsg_pub.publish(trackMsg_msg)


rospy.init_node('collaborationSearch_node')
collaborationSearch = CollaborationSearch()
rospy.spin()