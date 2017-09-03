# 服务器端
# -*- coding:utf-8 -*-

import sys
import socket

BUF_SIZE = 1024

server_addr = ('127.0.0.1', 8888)


def main():
    try:
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error as msg:
        print("Creating Socket Failure. Error Code : " + str(msg[0]))
        print("Error message: ", msg[1])
        sys.exit()
    # 连接服务器
    client.connect(server_addr)
    while True:  # 死循环 影响响应效率
        data = input(r"Please input something >").encode('utf-8')
        if not data:
            print("Input can not empety, Please input again...")
            continue
        client.sendall(data)  # 发送数据到服务器
        data = client.recv(BUF_SIZE)  # 接收数据
        print(data)

    client.close()


if __name__ == '__main__':
    main()
