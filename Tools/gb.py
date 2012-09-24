#!/usr/bin/python
import sys
import os.path

def gen_out(fname, br, br_dis, prg, arg):
    cnt = 'set logging file ' + fname + '\n'    
    cnt = cnt + 'set logging overwrite on\n'
    cnt = cnt + 'set logging on\n'
    cnt = cnt + 'set br pending on\n'
    if prg != None:
        cnt = cnt + 'file ' + prg + '\n'
    if arg != None:
        cnt = cnt + 'set args ' + arg + '\n'
    for i in range(len(br)):
        b = br[i]
        cnt = cnt + 'br ' + b + '\n'
        if b in br_dis:
            cnt = cnt + 'disa br ' + str(i+1) + '\n'
    cnt = cnt + 'run\n'
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
    br_dis = []
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
                        if l.find('keep n') != -1:
                            br_dis.append(fds[-1])
                        else:
                            if fds[-1] in br_dis:
                                br_dis.remove(fds[-1])
                    else:
                        if l.find('keep n') != -1:
                            br_dis.append(fds[-1])
                        else:
                            if fds[-1] in br_dis:
                                br_dis.remove(fds[-1])
            except:
                continue
    
    if len(br) > 0:
        gen_out(fname, br, br_dis, prg, arg)
    
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
