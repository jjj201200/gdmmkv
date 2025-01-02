#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# 添加 MMKV 的路径（替换为实际路径）
MMKV_INCLUDE_PATH = "src/MMKV/Win32/x64/Release/include"  # MMKV 头文件路径
MMKV_LIB_PATH = "src/MMKV/Win32/x64/Release"                   # mmkv.lib 所在目录
MMKV_LIB_NAME = "mmkv"                      # 不需要加后缀，SCons 会自动识别

# tweak this if you want to use different folders, or more folders, to store your source code in.
# 添加源文件目录
env.Append(CPPPATH=["src/", MMKV_INCLUDE_PATH])  # 添加 MMKV 的头文件路径
env.Append(LIBPATH=[MMKV_LIB_PATH])             # 添加 mmkv.lib 的目录路径
env.Append(LIBS=[MMKV_LIB_NAME])                # 链接 mmkv.lib
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "demo/bin/libgdmmkv.{}.{}.framework/libgdmmkv.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "demo/bin/libgdmmkv{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)

if env["target"] in ["editor", "template_debug"]:
    try:
        doc_data = env.GodotCPPDocData("src/gen/doc_data.gen.cpp", source=Glob("doc_classes/*.xml"))
        sources.append(doc_data)
    except AttributeError:
        print("Not including class reference as we're targeting a pre-4.3 baseline.")