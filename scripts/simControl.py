#!/usr/bin/env python
#coding=utf-8
import rospy
from wrt.msg import simControl

rospy.init_node('simControl_node')

simControl_pub = rospy.Publisher('simControl', simControl, queue_size = 1)

# 频率待定
rate = rospy.Rate(2)

while not rospy.is_shutdown():
    simControl_msg = simControl()
    # 初始化数据...


    simControl_pub.publish(simControl_msg)
    rate.sleep()
