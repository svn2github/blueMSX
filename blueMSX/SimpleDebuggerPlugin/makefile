# Makefile - SimpleDebugger.dsp
# created 01/AGO/2005 by Roger Filipe
#
#

CC=gcc
CFLAGSCXX=g++
CXXFLAGS=$(CFLAGS)
RC=windres -O COFF

CFLAGS+=-W -O2 -finline-functions -march=pentiumpro -D_M_IX86=600 -DWIN32 -DNDEBUG -D_WINDOWS
LD=dllwrap
LDFLAGSTARGET=SimpleDebugger.dll
LDFLAGS+=-Wl,--subsystem,windows --implib libSimpleDebugger.a
LIBS+=-lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32 ComCtl32.Lib

ifndef TARGET
TARGET=SimpleDebugger.dll
endif

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
	Callstack.cpp \
	Callstack.h \
	CpuRegisters.cpp \
	CpuRegisters.h \
	DasmIcons.bmp \
	debugger.manifest \
	Disassembly.cpp \
	Disassembly.h \
	Language.cpp \
	Language.h \
	Memory.cpp \
	Memory.h \
	Resource.h \
	resrc1.h \
	SimpleDebugger.cpp \
	SimpleDebugger.def \
	SimpleDebugger.rc \
	Stack.cpp \
	Stack.h \
	StatusBar.cpp \
	StatusBar.h \
	SymbolInfo.cpp \
	SymbolInfo.h \
	Toolbar.bmp \
	ToolBar.cpp \
	ToolBar.h \
	ToolbarBg.bmp \
	ToolDllMain.cpp \
	ToolInterface.h \
	EditControls.cpp \
	EditControls.h

OBJS=$(patsubst %.rc,%.res,$(patsubst %.cxx,%.o,$(patsubst %.cpp,%.o,$(patsubst %.cc,%.o,$(patsubst %.c,%.o,$(filter %.c %.cc %.cpp %.cxx %.rc,$(SRCS)))))))

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	-rm -f $(OBJS) $(TARGET) Debugger.dep

.PHONY: depends
depends:
	-$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MM $(filter %.c %.cc %.cpp %.cxx,$(SRCS)) > Debugger.dep

-include Debugger.dep

