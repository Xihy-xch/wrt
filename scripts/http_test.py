import urllib.parse
from urllib import request

# URL地址：http://平台地址/common/queryScore
url = "http://192.168.0.101:9999/common/queryScore"
# http://192.168.0.101:9999/
# 定义请求数据，并且对数据进行赋值
values={}
values['id']= '1'
values['score']= '100'
values['type']= '1'

time = 0
while time < 1000:
    # 对请求数据进行编码
    data = urllib.parse.urlencode(values)
    # 将数据与url进行拼接
    req = url + '?' + data
    print(req)
    # 打开请求，获取对象
    try:
        response = request.urlopen(req)
        # 打印Http状态码
        print(response.status) # 打印200
    except (IOError):
        print("Get Error")

    time = time + 1