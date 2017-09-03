# 常用多线程写法
# -*- coding:utf-8 -*-

import threading
import _thread
import time


class MyThread(threading.Thread):
    """"
    docstring for MyThread
    other functions
    """

    def __init__(self, thread_id, name, counter):
        super(MyThread, self).__init__()  # super()内参数
        self.thread_id = thread_id
        self.name = name
        self.counter = counter

    def run(self):
        print("Strating ", self.name)
        print_time(self.name, 1, self.counter)
        print("Exiting " + self.name)


# 外部function 供线程执行调度
def print_time(thread_name, delay, counter):
    while counter:
        time.sleep(delay)
        print("%s %s %d" % (thread_name, time.ctime(time.time()), counter))
        counter -= 1


def main():
    thread1 = MyThread(1, "Thread-1", 2)
    thread2 = MyThread(2, "Thread-2", 3)

    thread1.start()
    thread2.start()

    thread1.join()
    thread2.join()
    print("Exit Main Thread .")


if __name__ == '__main__':
    main()
