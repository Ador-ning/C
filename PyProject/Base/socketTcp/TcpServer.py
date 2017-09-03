# 服务器端
# -*- coding:utf-8 -*-

import sys
import socket

BUF_SIZE = 1024

server_addr = ("127.0.0.1", 8888)


def main():
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error as msg:
        print("Creating Socket failure, Error code : ", str(msg[0]))
        print("Error message : ", msg[1])
        sys.exit()

    print("Socket Created !")
    # 设置地址复用
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    try:  # 绑定地址
        server.bind(server_addr)
    except socket.error as msg:
        print("Binding failure, Error code : ", str(msg[0]))
        print("Error message : ", msg[1])

    print("Socket binding !")
    # 设置监听数
    server.listen(5)
    print("Socket Listening !")

    while True:
        client, client_addr = server.accept()
        print("Connected by :", client_addr)
        while True:
            data = client.recv(BUF_SIZE)  # 接受数据
            print(data)
            client.send(data)
    # 关闭
    server.close()


if __name__ == '__main__':
    main()
