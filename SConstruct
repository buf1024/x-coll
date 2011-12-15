import os.path
import os

WIN_DEBUG_COMM = '/Od /D "WIN32" /D "_DEBUG" /Gm /EHsc /RTC1 /MDd /W3 /nologo /c /ZI /TP'
WIN_RELEASE_COMM = '/O2 /Oi /GL /D "WIN32" /D "NDEBUG" /FD /EHsc /MD /Gy /W3 /nologo /c /Zi /TP'

GCC_DEBUG_COMM = '-g'
GCC_RELEASE_COMM = '-O2'

platform = Platform()
build_ver = 'release'
for build in COMMAND_LINE_TARGETS:
    if build.lower() == 'debug':
        build_ver = 'debug'
        break

dist_dir = 'dist'
dist_lib_dir  = 'dist/lib'
dist_header_dir = 'dist/include'
dist_bin_dir = 'dist/bin'
  
if not os.path.exists(dist_lib_dir):
    os.makedirs(dist_lib_dir)

if not os.path.exists(dist_header_dir):
    os.makedirs(dist_header_dir)

if not os.path.exists(dist_bin_dir):
    os.makedirs(dist_bin_dir)
    
env = Environment()
env['PLATFORM'] = platform
env['BUILD_VER'] = build_ver

target = ''
if str(platform) == 'win32':
    if build_ver == 'debug':
        env.Append(CXXFLAGS=WIN_DEBUG_COMM)
        target = 'xbasic_statd'
    else:
        env.Append(CXXFLAGS=WIN_RELEASE_COMM)
        target = target + 'xbasic_stat'
else:
    if build_ver == 'debug':
        env.Append(CXXFLAGS=GCC_DEBUG_COMM)
        target = target + 'xbasic_statd'
    else:
        env.Append(CXXFLAGS=GCC_RELEASE_COMM)
        target = target + 'xbasic_stat'

Export('env')

ex_srcs = ['3rd/tinyxml', '3rd/hash', 'Src']
lib_objs = []
for src in ex_srcs:
    subdir = '%s/SConscript' % src
    #vdir = '%s/%s' % (build_dir, src)
    obj = SConscript(subdir)#, variant_dir = vdir, duplicate=0)
    lib_objs.append(obj)

lib = env.StaticLibrary(target, lib_objs)
env.Alias(build_ver, lib)

headers = []
for src in ex_srcs:
    headers.append(Glob(src + '/*.h'))
  
dist_h = env.Install(dist_header_dir, headers)
dist_l = env.Install(dist_lib_dir, lib)
env.Alias('install', dist_dir)
env.Depends(dist_header_dir, dist_lib_dir)

src = 'Test/SConscript'
program = SConscript(src)
env.Depends(program, [dist_l, dist_h])
env.Install(dist_bin_dir, program)
env.Alias('test', program)
env.Alias('install', program)

