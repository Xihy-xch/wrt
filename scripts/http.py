#!/usr/bin/env python
#coding=utf-8

import requests
import json


#serverUrl = "http://192.168.0.101:9999/common/queryScore"
serverUrl = "http://127.0.0.1:12345/response.php"

data = {
    "rows": str([1,2,3,4])
}

print(data)
res = requests.get(url=serverUrl, params=data)
#res = requests.get(url = serverUrl, params=urlParams)
#jsonStr = res.json()
#j = json.dumps(data)
#print(json.loads(j)['rows'])
#print(jsonStr)
print(res)
print(json.loads(res.text)['rows'])


