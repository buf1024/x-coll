#!/usr/bin/env python

import sys
import os

def read_ver(file):
    f = os.popen('svn info ' + file)
    lines = f.read().split('\n')
    f.close()
    ver = None
    for line in lines:
        if line.startswith('Last Changed Rev'):
            ver = line.split(':')[1].strip()
            break
    return ver

def proc(dir):
    if not os.path.exists(dir + '.svn'):
        return
    files = os.listdir(dir)
    dirs = []
    for file in files:
        file = dir + file
        if os.path.isdir(file):
            dirs.append(file + '/')
        if file.endswith('.cpp') or file.endswith('.h'):            
            ver = read_ver(file)
            print file, ' => ', ver
    for dir in dirs:
        proc(dir)
    
def main():
    dir = './'
    if len(sys.argv) > 1:
        dir = sys.argv[1]
    if not dir.endswith('/'):
        dir = dir + '/'
    if not os.path.exists(dir):
        print 'path ', dir, ' not exits'
    proc(dir)

if __name__ == '__main__':
    main()
