import os.path
import os

WIN_DEBUG_COMM = '/Od /D "WIN32" /D "_DEBUG" /Gm /EHsc /RTC1 /MDd /W3 /nologo /c /ZI /TP'
WIN_RELEASE_COMM = '/O2 /Oi /GL /D "WIN32" /D "NDEBUG" /FD /EHsc /MD /Gy /W3 /nologo /c /Zi /TP'

platform = Platform()
build_ver = ARGUMENTS.get('ver', 'release').lower()
build_type = ARGUMENTS.get('type', 'lib').lower()

build_dir = 'build/%s/%s' % (platform, build_ver)
dist_dir  = 'dist/%s/%s' % (platform, build_ver)

if not os.path.exists(build_dir):
    os.makedirs(build_dir)
    
if not os.path.exists(dist_dir):
    os.makedirs(dist_dir)
    
target = dist_dir

env = Environment()
env['PLATFORM'] = platform
env['BUILD_VER'] = build_ver
env['BUILD_TYPE'] = build_type

if str(platform) == 'win32':
    env.Append(CXXFLAGS='/D "MSWINDOWS"')
    if build_ver == 'debug':
        env.Append(CXXFLAGS=WIN_DEBUG_COMM)        
        if build_type == 'lib':
            env.Append(CXXFLAGS='/D "_LIB" /D "XBASICSTAT"')
            target = target + '/xbasic_statd'
        else:
            env.Append(CXXFLAGS='/D "_USRDLL" /D "_WINDLL" /D "XBASICDLL"')
            target = target + '/xbasicd'
    else:
        env.Append(CXXFLAGS=WIN_RELEASE_COMM)
        if build_type == 'lib':
            env.Append(CXXFLAGS='/D "_LIB" /D "XBASICSTAT"')
            target = target + '/xbasic_stat'
        else:
            env.Append(CXXFLAGS='/D "_USRDLL" /D "_WINDLL" /D "XBASICDLL"')
            target = target + '/xbasic'
else:
    if build_ver == 'debug':
        pass
    else:
        pass

Export('env')

ex_srcs = ['3rd/tinyxml', '3rd/hash', 'Src']

lib_objs = []
for src in ex_srcs:
    subdir = '%s/SConscript' % src;
    vdir = '%s/%s' % (build_dir, src)
    obj = SConscript(subdir, variant_dir = vdir, duplicate=0)
    lib_objs.append(obj)

lib = None
if build_type == 'lib':
    lib = env.StaticLibrary(target, lib_objs)
else:
    lib = env.SharedLibrary(target, lib_objs)
    
    '''
src = 'Src/test'   
vdir = '%s/%s' % (build_dir, src)

obj = SConscript(test, variant_dir = vdir, duplicate=0)
test = env.Program(dist_dir + 'test', obj)

env.Depend(test, lib)'''
