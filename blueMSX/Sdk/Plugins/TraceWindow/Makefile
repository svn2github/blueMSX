# Makefile - TraceWindow.dsp
# Created at 01/AGO/2005 by Roger Filipe
#
#

CC=gcc
CFLAGSCXX=g++
CXXFLAGS=$(CFLAGS)
RC=windres -O COFF

CFLAGS+=-W -O2 -finline-functions -march=pentiumpro -D_M_IX86=600 -DWIN32 -DNDEBUG -D_WINDOWS
LD=dllwrap
LDFLAGSTARGET=TraceWindow.dll
LDFLAGS+=-Wl,--subsystem,windows --implib libTraceWindow.a
LIBS+=-lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 -lComCtl32

.PHONY: all
all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.o: %.cxx
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

%.res: %.rc
	$(RC) $(CPPFLAGS) -o $@ -i $<

SRCS= \
	bluemsx.ico \
	BlueMSXToolInterface.h \
	Resource.h \
	ToolDllMain.cpp \
	ToolInterface.h \
	TraceWindow.cpp \
	TraceWindow.def \
	TraceWindow.manifest \
	TraceWindow.rc

OBJS=$(patsubst %.rc,%.res,$(patsubst %.cxx,%.o,$(patsubst %.cpp,%.o,$(patsubst %.cc,%.o,$(patsubst %.c,%.o,$(filter %.c %.cc %.cpp %.cxx %.rc,$(SRCS)))))))

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET) TraceWindow.dep

.PHONY: depends
depends:
	-$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MM $(filter %.c %.cc %.cpp %.cxx,$(SRCS)) > TraceWindow.dep

-include TraceWindow.dep

