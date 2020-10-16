#!/usr/bin/env python
#coding=utf-8
import math
import rospy
import base64
from wrt.msg import Situation
from wrt.msg import DetectingResult
 

EARTH_REDIUS = 6378.137

selfId = 1
selfPos = Pos()
pub = rospy.Publisher('objectTopic', DetectingResult)

def rad(d):
    return d * math.pi / 180.0

def getDistance(pos1, pos2):
    radLat1 = rad(pos1.latitude)
    radLat2 = rad(pos2.latitude)

    a = radLat1 - radLat2
    b = rad(pos1.longtitude) - rad(pos2.longtitude)

    s = 2 * math.asin(math.sqrt(math.pow(math.sin(a / 2), 2) + math.cos(radLat1) * math.cos(radLat2) * math.pow(math.sin(b / 2), 2)))
    s = s * EARTH_REDIUS
    return s

def situationCallback(situationMsg):
    wrtList = situationMsg.wrt_list
    cargoBoatPos = Pos()
    for wrt in wrtList:
        if wrt.wrt_id == selfId:
            selfPos = wrt.pos
        if wrt.type == 0:
            cargoBoatPos = wrt.pos
    if (getDistance(selfPos, cargoBoatPos) <= 0.5):
        pic = open("/home/xch/demo.jpg", "rb")
        pic_base64 = base64.b64encode(pic.read())
        pic.close()

        
        detectingResult = DetectingResult()
        pub.publish(detectingResult)

    else:
        return
    

rospy.init_node('objectRecognitionNode')
 
sub = rospy.Subscriber('situationTopic', Situation, situationCallback)

rospy.spin()