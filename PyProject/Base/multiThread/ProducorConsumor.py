# -*- coding:utf-8 -*-
# 生产者- 消费者

import threading
import random
import time
import queue

MAX_SIZE = 5
SHARE_Q = []  # 共享队列
CONDITION = threading.Condition()  # 作用


class Producer(threading.Thread):
    """
    docstring
    """

    def run(self):
        products = range(5)
        global SHARE_Q
        while True:
            CONDITION.acquire()
            if len(SHARE_Q) == 5:
                print("Queue is full ...")
                CONDITION.wait()
                print("Consumer have consumed something ...")

            product = random.choice(products)
            SHARE_Q.append(product)
            print("Producer : ", product)
            CONDITION.notify()
            CONDITION.release()
            time.sleep(random.random())


class Consumer(threading.Thread):
    """
    docstring
    """

    def run(self):
        global SHARE_Q
        while True:
            CONDITION.acquire()
            if not SHARE_Q:
                print("Queue is Empty ...")
                CONDITION.wait()
                print("Producer have producted something ...")
            product = SHARE_Q.pop(0)
            print("Consumer : consuming ", product)
            CONDITION.notify()
            CONDITION.release()
            time.sleep(random.random())


def main():
    producer = Producer()
    consumer = Consumer()
    producer.start()
    consumer.start()


# Condition 作用
# 添加调试 过程具体
if __name__ == '__main__':
    main()
