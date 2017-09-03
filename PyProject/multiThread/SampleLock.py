# -*- coding:utf-8 -*-
# 简单锁

import threading
import time
import _thread

threadLock = threading.Lock()


class MyThread(threading.Thread):
    """"
    docstring
    """

    def __init__(self, thread_id, name, counter):
        super().__init__()
        self.thread_id = thread_id
        self.name = name
        self.counter = counter

    # 重写run方法
    def run(self):
        print("Starting " + self.name)
        threadLock.acquire_lock()  # 获取锁
        print_time(self.name, 3, self.counter)
        threadLock.release()  # 释放锁


def print_time(thread_name, delay, counter):
    while counter:
        time.sleep(delay)
        print("%s %s %d" % (thread_name, time.ctime(time.time()), counter))
        counter -= 1


def main():
    # threads = []  # 存放线程对象

    thread1 = MyThread(1, "Thread-1", 1)
    thread2 = MyThread(2, "Thread-2", 2)

    # 启动
    thread1.start()
    thread2.start()

    # for t in threads:
    #   t.join()  # 等待线程直到终止

    print("Exit Main Thread .")


if __name__ == '__main__':
    main()
