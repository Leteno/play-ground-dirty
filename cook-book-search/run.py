#!/usr/bin/env python3

import json
import random
import os
import sys

def main():
    menu = getMenu()
    cookedList = getCooked()
    while 1:
        index = random.randrange(len(menu))
        if not contains(cookedList, index):
            if queryYes(menu[index]):
                cookedList.append(index)
                saveCooked(cookedList)
                break

def getMenu():
    file = 'menu.json'
    with open(file, 'r', encoding='utf-8') as fd:
        return json.load(fd)

def getCooked():
    file = 'cooked.list'
    if os.path.exists(file):
        with open(file, 'r') as fd:
            return json.load(fd)
    return []

def contains(cookedList, index):
    if cookedList:
        return index in cookedList
    return False

def queryYes(menuItem):
    name, page = menuItem['name'], menuItem['page']
    query = 'Would you take this? %s, page %s (Y for yes, Q for quit)' % (name, page)
    answer = input(query)
    if 'Y' in answer or 'y' in answer:
        return True
    elif 'Q' in answer or 'q' in answer:
        sys.exit(0)
    return False

def saveCooked(cookedList):
    file = 'cooked.list'
    with open(file, 'w') as fd:
        fd.write(json.dumps(cookedList))

if __name__ == '__main__':
    main()