#!/usr/bin/env python3

import json

def main():
    file = 'data.raw'
    result = []
    with open(file, 'r', encoding='utf-8') as fd:
        for line in fd:
            d = retrieveData(line.strip())
            if d:
                result.append(d)

    saveFile = 'menu.json'
    with open(saveFile, 'w') as fd:
        fd.write(json.dumps(result, indent=4))
    print('done')

def retrieveData(line):
    sp = line.split('p')
    if len(sp) > 1:
        return {
            'name': sp[0],
            'page': sp[1]
        }
    return None

if __name__ == '__main__':
    main()