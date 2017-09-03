# -*- coding:utf-8 -*-

__author__ = "Yang Ning"

import urllib.request as ur
import re
import os
import tool


# 抓取类
class Spider:
    # 初始化
    def __init__(self):
        self.siteURL = 'http://mm.taobao.com/json/request_top_list.htm'
        self.tool = tool.Tool()

    # 获取索引页面的内容
    def getPage(self, pageIndex):
        url = self.siteURL + "?page=" + str(pageIndex)
        request = ur.Request(url)
        response = ur.urlopen(request)
        return response.read().decode('gbk')

    # 获取索引界面所有的信息， list格式
    def getContents(self, pageIndex):
        page = self.getPage(pageIndex)
        pattern = re.compile(
            '<div class="list-item".*?pic-word.*?<a href="(.*?)".*?<img src="(.*?)".*?<a class="lady-name.*?>(.*?)</a>.*?<strong>(.*?)</strong>.*?<span>(.*?)</span>',
            re.S)
        items = re.findall(pattern, page)
        contents = []
        for item in items:
            contents.append([item[0], item[1], item[2], item[3], item[4]])

        return contents

    # 获取详情页面
    def getDetailPage(self, infoURL):
        response = ur.urlopen(infoURL)
        return response.read().decode('gbk')

    # 获取个人文字简介
    def getBrief(self, page):
        pattern = re.compile('<div class="mm-aixiu-content".*?>(.*?)<!--', re.S)
        result = re.search(pattern, page)
        return self.tool.replace(result.group(1))

    # 获取所有图片
    def getAllImg(self, page):
        pattern = re.compile('<div class="mm-aixiu-content".*?>(.*?)<!--', re.S)
        # 个人信息页面所有代码
        content = re.search(pattern, page)
        # 从代码中提取图片
        patternImg = re.compile('<img.*?src="(.*?)"', re.S)
        images = re.findall(patternImg, content.group(1))
        return images

    # 保存图片
    def saveImgs(self, images, name):
        number = 1
        print(u"发现", name, u"共有", len(images), u"张照片")
        for imageURL in images:
            splitPath = imageURL.split('.')
            fTail = splitPath.pop()
            if len(fTail) > 3:
                fTail = 'jpg'

            fileName = name + "/" + str(number) + "." + fTail
            self.saveImg(imageURL, fileName)
            number += 1

    # 保存头像
    def saveIcon(self, iconURL, name):
        splitPath = iconURL.split('.')
        fTail = splitPath.pop()
        fileName = name + "/icon." + fTail
        self.saveImg(iconURL, fileName)

    # 保存个人简介
    def saveBrief(self, content, name):
        fileName = name + "/" + name + ".txt"
        f = open(fileName, "w+")  # 加入异常处理机制
        print(u"正在偷偷保存她的个人信息为", fileName)
        f.write(content.encode('utf-8'))

    # 传入图片URL，文件名 保存单张图片
    def saveImg(self, imageURL, fileName):
        u = ur.urlopen(imageURL)
        data = u.read()

        f = open(fileName, "wb")
        f.write(data)
        print("Save an image in", fileName)
        f.close()

    # 创建目录
    def mkdir(self, path):
        path = path.strip()

        isExists = os.path.exists(path)
        if not isExists:
            print(u"创建文件夹夹", path)
            os.makedirs(path)
            return True
        else:
            print(u"文件夹存在", path)
            return False

    # 将一页信息保存
    def savePageInfo(self, pageIndex):
        contents = self.getContents(pageIndex)
        for item in contents:
            # item[0]个人详情URL,item[1]头像URL,item[2]姓名,item[3]年龄,item[4]居住地
            print(u"发现一位模特,名字叫", item[2], u"芳龄", item[3], u",她在", item[4])
            print(u"正在偷偷地保存", item[2], "的信息")
            print(u"又意外地发现她的个人地址是", item[0])
            # 个人详情页面的URL
            detailURL = item[0]
            # 得到个人详情页面代码
            detailPage = self.getDetailPage(detailURL)
            # 获取个人简介
            brief = self.getBrief(detailPage)
            # 获取所有图片列表
            images = self.getAllImg(detailPage)
            self.mkdir(item[2])
            # 保存个人简介
            self.saveBrief(brief, item[2])
            # 保存头像
            self.saveIcon(item[1], item[2])
            # 保存图片
            self.saveImgs(images, item[2])

    # 保存页码范围内的信息
    def savePagesInfo(self, start, end):
        for i in range(start, end + 1):
            self.savePageInfo(i)


def main():
    spider = Spider()
    spider.savePageInfo(1, 3)


if __name__ == '__main__':
    main()
