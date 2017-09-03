# -*- coding:utf-8 -*-

import threading
import time
import queue

SHARE_Q = queue.Queue()  # 构造 默认 队列
_WORKER_THREAD_NUM = 3  # 设置线程个数


class MyThread(threading.Thread):
    """"
    Docstring
    """

    def __init__(self, func):
        super().__init__()
        self.func = func

    def run(self):
        self.func()


def worker():
    global SHARE_Q
    while not SHARE_Q.empty():
        item = SHARE_Q.get()  # 获得任务
        print("Processing :", item)
        time.sleep(1)


def main():
    global SHARE_Q
    threads = []
    for task in range(5):  # 向队列中放入任务
        SHARE_Q.put(task)

    for i in range(_WORKER_THREAD_NUM):
        thread = MyThread(worker)
        thread.start()
        threads.append(thread)

    for thread in threads:
        thread.join()


if __name__ == '__main__':
    main()
