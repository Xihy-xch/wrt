#!/usr/bin/env python
# coding=utf-8
import time
import socket
import sys
sys.path.append('/home/xch/vscode-workspace/catkin_ws/src/wrt/protobuf/out')
import SimData_pb2
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
HOST = socket.gethostname()
PORT = 50006
# 定义socket类型，网络通信，TCP

s.connect((HOST, PORT))  # 要连接的IP与端口
print ('ok')
gridMapstates = SimData_pb2.GridMapStates()  # 等待客户端连接
gridMapstates.size = "50"
gridMapstates.topLeftLoc = "100"
gridMapstates.gridType = 10
gridMapstates.gridInterval = 5
stateInfo = gridMapstates.stateList.add()
stateInfo.id = 2
stateInfo.type = 1
stateInfo.loc = "10,20"
stateInfo.alt = 15
entity = stateInfo.entityList.add()
entity.entityID = 1
entity.name = 'chuan'
stateInfo = gridMapstates.stateList.add()
stateInfo.id = 1
stateInfo.type = 2
stateInfo.loc = "15,30"
stateInfo.alt = 10
entity = stateInfo.entityList.add()
entity.entityID = 2
entity.name = 'xiaochuan'
data = gridMapstates.SerializeToString()
i = 0
while 1:
    print( i, '次循环')
    i = i + 1
    s.send(data)
    time.sleep(2)
s.close()
