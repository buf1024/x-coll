#!/usr/bin/env python

import sys
import os.path

def gen_out(fname, br, prg, arg):
    cnt = 'set logging file ' + fname + '\n'
    cnt = cnt + 'set logging on\n'
    cnt = cnt + 'set br pending on\n'
    if prg != None:
        cnt = cnt + 'file ' + prg + '\n'
    if arg != None:
        cnt = cnt + 'set args ' + arg + '\n'
    for b in br:
        cnt = cnt + 'br ' + b + '\n'
    cnt = cnt + 'r\n'
    print cnt
    fname = fname + '.br'
    f = open(fname, 'w')
    f.write(cnt)
    f.close()
def gen_break(fname):    
    f = open(fname)
    lines = f.readlines()
    f.close()
    
    br = []
    prg = None
    arg = None
    
    for l in lines:
        l = l.strip().strip('\n')
        if len(l) == 0:
            continue
        if l.startswith('Starting program:'):
            fds = l.split(':')
            if len(fds) > 0:
                fd = fds[1].strip()
                idx = fd.find(' ')
                if idx > 0:
                    prg = fd[:idx]
                    arg = fd[idx+1:]
                else:
                    prg = fd
        fds = l.split()
        if len(fds) > 2:
            try:
                fd = int(fds[0])
                if fds[1] == 'breakpoint':
                    if fds[-1] not in br:
                        br.append(fds[-1])
            except:
                continue
    
    if len(br) > 0:
        gen_out(fname, br, prg, arg)
    
def main():
    if len(sys.argv) <= 1:
        print 'needs gdb log file'
        sys.exit(-1)
    f = sys.argv[1]
    if not os.path.exists(f) or not os.path.isfile(f):
        print 'gdb log file ' , f, ' does not exsit or not a file'
        sys.exit(-1)
        
    gen_break(f)
    print 'done'

if __name__ == '__main__':
    main()
