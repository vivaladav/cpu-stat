# 3 build modes
vars = Variables()
vars.Add(EnumVariable('mode', 'Building mode', 'debug', allowed_values=('debug', 'profile', 'release')))

env = Environment(variables = vars)
Help(vars.GenerateHelpText(env))

# basic flags according to build mode
if env['mode'] == 'debug':
    env.Append(CCFLAGS = ['-Wall', '-g', '-O0', '-DDEBUG'])
elif env['mode'] == 'release':
    env.Append(CCFLAGS = ['-Wall', '-O3', '-DNDEBUG'])
    env.Append(LINKFLAGS = ['-s'])
elif env['mode'] == 'profile':
    env.Append(CCFLAGS = ['-Wall', '-pg', '-O0', '-DNDEBUG'])

env.Append(CCFLAGS = ['-std=c++11'])

# cpu-stat
SConscript('src/SConscript', exports = 'env', variant_dir = 'build/' + env['mode'], src_dir= 'src/', duplicate = 0)
