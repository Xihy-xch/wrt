#!/usr/bin/env python
#coding=utf-8

import requests
import json
"""
2.12沙盒地图
名称：GridMap
结构定义：

Int32 size   //地图矩阵大小 !
Int32 topLeftLoc  //左顶点网格中心点经纬度
Int32 gridType  //网格类型  1 六边形
Int32 gridInterval  //两个相邻网格距离!
GridCell[] cell   //网格列表

2.13沙盒网格
名称：GridCell
结构定义：

Uint64  id   //在地图中的编号 ！
Int32  type  //类型 1 水域 2 陆地  3 山
Float32 lat   //中心经度
Float32 lan   //中心纬度
Int32 alt    //地势海拔


 
"""
gridInterval = 0
gridCell = []
gridCellIds = []
topLeftLong = 0
topLeftLat = 0
wrtList = []
targetLongtitude = 0
targetLat = 0 
gridCellTypes = [] 
rows = 0 #地图矩阵的行数
cols = 0 #地图矩阵的列数

serverUrl = "http://192.168.0.101:9999/common/queryScore"
#serverUrl = "https://www.baidu.com/"


data = {
    "rows":rows,
    "cols":cols
}
headers = {'Content-Type': 'application/json'}
res = requests.get(url=serverUrl, headers=headers, data=json.dumps(data))
#res = requests.get(url = serverUrl, params=urlParams)
#jsonStr = res.json()
#print(jsonStr)
print(res.json)

j = json.dumps(data)
print(json.loads(j)['rows'])