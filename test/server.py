#!/usr/bin/env python
# coding=utf-8
import time
import socket  # 导入 socket 模块
import sys
sys.path.append('/home/xch/vscode-workspace/catkin_ws/src/wrt/protobuf/out')
import SimData_pb2
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # 创建 socket 对象
host = socket.gethostname()  # 获取本地主机名
port = 50007  # 设置端口
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))  # 绑定端口

s.listen(5)
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
while True:
    print (i, '次循环')
    i = i + 1
    c, addr = s.accept()  # 建立客户端连接
    print ('连接地址:', addr)
    while 1:
        print(data)
        c.send(data)
        time.sleep(2)
c.close()
s.close()