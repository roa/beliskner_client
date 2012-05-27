WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS =  -Wall `pkg-config --cflags OGRE` -fexceptions
RESINC = 
LIBDIR =  -L/bin/Debug -L/bin/Release
LIB =  -lGL
LDFLAGS =  `pkg-config --libs OGRE`

INC_DEBUG =  $(INC)
CFLAGS_DEBUG =  $(CFLAGS) -g
RESINC_DEBUG =  $(RESINC)
RCFLAGS_DEBUG =  $(RCFLAGS)
LIBDIR_DEBUG =  $(LIBDIR)
LIB_DEBUG = $(LIB) -lOgreMain -lOIS
LDFLAGS_DEBUG =  $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = ./bin/Debug/beliskner_client

INC_RELEASE =  $(INC)
CFLAGS_RELEASE =  $(CFLAGS) -O2
RESINC_RELEASE =  $(RESINC)
RCFLAGS_RELEASE =  $(RCFLAGS)
LIBDIR_RELEASE =  $(LIBDIR)
LIB_RELEASE = $(LIB) -lOgreMain -lOIS
LDFLAGS_RELEASE =  $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = ./bin/Release/beliskner_client

OBJ_DEBUG = $(OBJDIR_DEBUG)/src/BaseRoot.o $(OBJDIR_DEBUG)/src/DemoApp.o $(OBJDIR_DEBUG)/src/FrameListener.o $(OBJDIR_DEBUG)/src/MainScene.o $(OBJDIR_DEBUG)/src/NextScene.o $(OBJDIR_DEBUG)/src/SceneManager.o $(OBJDIR_DEBUG)/src/main.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/src/BaseRoot.o $(OBJDIR_RELEASE)/src/DemoApp.o $(OBJDIR_RELEASE)/src/FrameListener.o $(OBJDIR_RELEASE)/src/MainScene.o $(OBJDIR_RELEASE)/src/NextScene.o $(OBJDIR_RELEASE)/src/SceneManager.o $(OBJDIR_RELEASE)/src/main.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d ./bin/Debug || mkdir -p ./bin/Debug
	test -d $(OBJDIR_DEBUG)/src || mkdir -p $(OBJDIR_DEBUG)/src

after_debug: 

debug: before_debug out_debug after_debug

out_debug: $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LDFLAGS_DEBUG) $(LIBDIR_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG) -o $(OUT_DEBUG)

$(OBJDIR_DEBUG)/src/BaseRoot.o: src/BaseRoot.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/BaseRoot.cpp -o $(OBJDIR_DEBUG)/src/BaseRoot.o

$(OBJDIR_DEBUG)/src/DemoApp.o: src/DemoApp.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/DemoApp.cpp -o $(OBJDIR_DEBUG)/src/DemoApp.o

$(OBJDIR_DEBUG)/src/FrameListener.o: src/FrameListener.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/FrameListener.cpp -o $(OBJDIR_DEBUG)/src/FrameListener.o

$(OBJDIR_DEBUG)/src/MainScene.o: src/MainScene.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/MainScene.cpp -o $(OBJDIR_DEBUG)/src/MainScene.o

$(OBJDIR_DEBUG)/src/NextScene.o: src/NextScene.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/NextScene.cpp -o $(OBJDIR_DEBUG)/src/NextScene.o

$(OBJDIR_DEBUG)/src/SceneManager.o: src/SceneManager.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/SceneManager.cpp -o $(OBJDIR_DEBUG)/src/SceneManager.o

$(OBJDIR_DEBUG)/src/main.o: src/main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/main.cpp -o $(OBJDIR_DEBUG)/src/main.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf ./bin/Debug
	rm -rf $(OBJDIR_DEBUG)/src

before_release: 
	test -d ./bin/Release || mkdir -p ./bin/Release
	test -d $(OBJDIR_RELEASE)/src || mkdir -p $(OBJDIR_RELEASE)/src

after_release: 

release: before_release out_release after_release

out_release: $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LDFLAGS_RELEASE) $(LIBDIR_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE) -o $(OUT_RELEASE)

$(OBJDIR_RELEASE)/src/BaseRoot.o: src/BaseRoot.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/BaseRoot.cpp -o $(OBJDIR_RELEASE)/src/BaseRoot.o

$(OBJDIR_RELEASE)/src/DemoApp.o: src/DemoApp.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/DemoApp.cpp -o $(OBJDIR_RELEASE)/src/DemoApp.o

$(OBJDIR_RELEASE)/src/FrameListener.o: src/FrameListener.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/FrameListener.cpp -o $(OBJDIR_RELEASE)/src/FrameListener.o

$(OBJDIR_RELEASE)/src/MainScene.o: src/MainScene.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/MainScene.cpp -o $(OBJDIR_RELEASE)/src/MainScene.o

$(OBJDIR_RELEASE)/src/NextScene.o: src/NextScene.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/NextScene.cpp -o $(OBJDIR_RELEASE)/src/NextScene.o

$(OBJDIR_RELEASE)/src/SceneManager.o: src/SceneManager.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/SceneManager.cpp -o $(OBJDIR_RELEASE)/src/SceneManager.o

$(OBJDIR_RELEASE)/src/main.o: src/main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/main.cpp -o $(OBJDIR_RELEASE)/src/main.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf ./bin/Release
	rm -rf $(OBJDIR_RELEASE)/src

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

