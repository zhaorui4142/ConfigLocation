
#包含头文件的搜索路径

#工程中包含的头文件
HEADERS += $$PWD/cpuusage.h

#工程中包含的源文件
SOURCES += $$PWD/cpuusage.cpp

LIBS += -lIphlpapi
