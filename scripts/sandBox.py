#!/usr/bin/env python
# coding=utf-8
from wrt.msg import GridMap
from wrt.msg import WRT
from wrt.msg import GridCell
from wrt.msg import WayPointArray
from wrt.msg import simControl
import rospy
import socket
import sys
sys.path.append('/home/xch/vscode-workspace/catkin_ws/src/wrt/protobuf/out')
import SimData_pb2


def simControl_callback(simControl_msg):
    # 数据处理
    print ('处理simControl数据')


def trackMsg_callback(trackMsg):
    # 数据处理
    print ('处理trackMsg数据')


rospy.init_node('sandBox_node')

simControl_sub = rospy.Subscriber('simControl', simControl,
                                  simControl_callback, queue_size = 1)
trackMsg_sub = rospy.Subscriber('track_Msg', WayPointArray, trackMsg_callback, queue_size = 1)

gridMap_pub = rospy.Publisher('gridMap', GridMap,queue_size = 1)

#rate = rospy.Rate(2)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 创建 socket 对象
host = socket.gethostname()  # 获取本地主机名
port = 50006  # 设置端口
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))  # 绑定端口

s.listen(5)
i = 0
c, addr = s.accept()  # 建立客户端连接
while not rospy.is_shutdown():        
    gridMap_msg = GridMap()
    print (i, '次循环')
    i = i + 1
    data = c.recv(4096)
    if(len(data) == 0):
        c,addr = s.accept()

    gridMapStates = SimData_pb2.GridMapStates()
    gridMapStates.ParseFromString(data)
    # 处理数据
    gridMap_msg.size = gridMapStates.size
    gridMap_msg.topLeftLoc = gridMapStates.topLeftLoc
    gridMap_msg.gridType = gridMapStates.gridType
    gridMap_msg.gridInterval = gridMapStates.gridInterval
    for stateInfo in gridMapStates.stateList:
        gridCell_msg = GridCell()
        gridCell_msg.id = stateInfo.id
        gridCell_msg.type = stateInfo.type
        gridCell_msg.loc = stateInfo.loc
        gridCell_msg.alt = stateInfo.alt
        for entity in stateInfo.entityList:
            wrt_msg = WRT()
            wrt_msg.wrt_id = entity.entityID
            wrt_msg.name = entity.name
            gridCell_msg.wrtList.append(wrt_msg)
        gridMap_msg.cell.append(gridCell_msg)
        '''
        print(gridMap_msg.size)
        print(gridMap_msg.topLeftLoc)
        print(gridMap_msg.gridType)
        print(gridMap_msg.gridInterval)
        for stateInfo in gridMap_msg.cell:
            print(stateInfo)
        '''
    gridMap_pub.publish(gridMap_msg)
s.close()
rospy.spin()
