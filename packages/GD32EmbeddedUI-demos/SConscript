import os
from building import *

cwd = GetCurrentDir()
src = []
inc = [cwd, os.path.join(cwd, 'port')]

# Keep this script outside the directories replaced by the code generator.
# Screens, events, C images and C fonts are discovered on every invocation.
for folder in ('generated', 'custom'):
    for root, dirs, files in os.walk(os.path.join(cwd, folder)):
        dirs.sort()
        inc.append(root)
        src += sorted(Glob(os.path.join(root, '*.c')))

group = DefineGroup('GD32EmbeddedUI', src, depend=['PKG_USING_LVGL'], CPPPATH=inc)

Return('group')
