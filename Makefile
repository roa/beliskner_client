WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS =  `pkg-config --cflags OGRE` -fexceptions
RESINC = 
LIBDIR =  -L/bin/Debug -L/bin/Release
LIB =  -lGL
LDFLAGS =  `pkg-config --libs OGRE`

INC_DEBUG =  $(INC) -Isrc/base -Isrc/scenes -Isrc/net
CFLAGS_DEBUG =  $(CFLAGS) -g -Wall
RESINC_DEBUG =  $(RESINC)
RCFLAGS_DEBUG =  $(RCFLAGS)
LIBDIR_DEBUG =  $(LIBDIR)
LIB_DEBUG = $(LIB) -lOgreMain -lOIS -llua -lCEGUIBase -lCEGUIOgreRenderer -lboost_thread
LDFLAGS_DEBUG =  $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = ./bin/Debug/beliskner_client

INC_RELEASE =  $(INC) -Isrc/base -Isrc/net -Isrc/scenes
CFLAGS_RELEASE =  $(CFLAGS) -O2
RESINC_RELEASE =  $(RESINC)
RCFLAGS_RELEASE =  $(RCFLAGS)
LIBDIR_RELEASE =  $(LIBDIR)
LIB_RELEASE = $(LIB) -lOgreMain -lOIS -llua -lCEGUIBase -lCEGUIOgreRenderer -lboost_thread
LDFLAGS_RELEASE =  $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = ./bin/Release/beliskner_client

OBJ_DEBUG = $(OBJDIR_DEBUG)/src/scenes/WorldScene.o $(OBJDIR_DEBUG)/src/scenes/FightScene.o $(OBJDIR_DEBUG)/src/net/Sender.o $(OBJDIR_DEBUG)/src/net/Receiver.o $(OBJDIR_DEBUG)/src/net/BaseNetwork.o $(OBJDIR_DEBUG)/src/base/main.o $(OBJDIR_DEBUG)/src/base/BaseRoot.o $(OBJDIR_DEBUG)/src/base/SceneManager.o $(OBJDIR_DEBUG)/src/base/Player.o $(OBJDIR_DEBUG)/src/base/Monster.o $(OBJDIR_DEBUG)/src/base/FrameListener.o $(OBJDIR_DEBUG)/src/base/DemoApp.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/src/scenes/WorldScene.o $(OBJDIR_RELEASE)/src/scenes/FightScene.o $(OBJDIR_RELEASE)/src/net/Sender.o $(OBJDIR_RELEASE)/src/net/Receiver.o $(OBJDIR_RELEASE)/src/net/BaseNetwork.o $(OBJDIR_RELEASE)/src/base/main.o $(OBJDIR_RELEASE)/src/base/BaseRoot.o $(OBJDIR_RELEASE)/src/base/SceneManager.o $(OBJDIR_RELEASE)/src/base/Player.o $(OBJDIR_RELEASE)/src/base/Monster.o $(OBJDIR_RELEASE)/src/base/FrameListener.o $(OBJDIR_RELEASE)/src/base/DemoApp.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d ./bin/Debug || mkdir -p ./bin/Debug
	test -d $(OBJDIR_DEBUG)/src/scenes || mkdir -p $(OBJDIR_DEBUG)/src/scenes
	test -d $(OBJDIR_DEBUG)/src/net || mkdir -p $(OBJDIR_DEBUG)/src/net
	test -d $(OBJDIR_DEBUG)/src/base || mkdir -p $(OBJDIR_DEBUG)/src/base

after_debug: 

debug: before_debug out_debug after_debug

out_debug: $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LDFLAGS_DEBUG) $(LIBDIR_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG) -o $(OUT_DEBUG)

$(OBJDIR_DEBUG)/src/scenes/WorldScene.o: src/scenes/WorldScene.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/scenes/WorldScene.cpp -o $(OBJDIR_DEBUG)/src/scenes/WorldScene.o

$(OBJDIR_DEBUG)/src/scenes/FightScene.o: src/scenes/FightScene.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/scenes/FightScene.cpp -o $(OBJDIR_DEBUG)/src/scenes/FightScene.o

$(OBJDIR_DEBUG)/src/net/Sender.o: src/net/Sender.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/net/Sender.cpp -o $(OBJDIR_DEBUG)/src/net/Sender.o

$(OBJDIR_DEBUG)/src/net/Receiver.o: src/net/Receiver.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/net/Receiver.cpp -o $(OBJDIR_DEBUG)/src/net/Receiver.o

$(OBJDIR_DEBUG)/src/net/BaseNetwork.o: src/net/BaseNetwork.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/net/BaseNetwork.cpp -o $(OBJDIR_DEBUG)/src/net/BaseNetwork.o

$(OBJDIR_DEBUG)/src/base/main.o: src/base/main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/main.cpp -o $(OBJDIR_DEBUG)/src/base/main.o

$(OBJDIR_DEBUG)/src/base/BaseRoot.o: src/base/BaseRoot.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/BaseRoot.cpp -o $(OBJDIR_DEBUG)/src/base/BaseRoot.o

$(OBJDIR_DEBUG)/src/base/SceneManager.o: src/base/SceneManager.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/SceneManager.cpp -o $(OBJDIR_DEBUG)/src/base/SceneManager.o

$(OBJDIR_DEBUG)/src/base/Player.o: src/base/Player.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/Player.cpp -o $(OBJDIR_DEBUG)/src/base/Player.o

$(OBJDIR_DEBUG)/src/base/Monster.o: src/base/Monster.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/Monster.cpp -o $(OBJDIR_DEBUG)/src/base/Monster.o

$(OBJDIR_DEBUG)/src/base/FrameListener.o: src/base/FrameListener.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/FrameListener.cpp -o $(OBJDIR_DEBUG)/src/base/FrameListener.o

$(OBJDIR_DEBUG)/src/base/DemoApp.o: src/base/DemoApp.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/base/DemoApp.cpp -o $(OBJDIR_DEBUG)/src/base/DemoApp.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf ./bin/Debug
	rm -rf $(OBJDIR_DEBUG)/src/scenes
	rm -rf $(OBJDIR_DEBUG)/src/net
	rm -rf $(OBJDIR_DEBUG)/src/base

before_release: 
	test -d ./bin/Release || mkdir -p ./bin/Release
	test -d $(OBJDIR_RELEASE)/src/scenes || mkdir -p $(OBJDIR_RELEASE)/src/scenes
	test -d $(OBJDIR_RELEASE)/src/net || mkdir -p $(OBJDIR_RELEASE)/src/net
	test -d $(OBJDIR_RELEASE)/src/base || mkdir -p $(OBJDIR_RELEASE)/src/base

after_release: 

release: before_release out_release after_release

out_release: $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LDFLAGS_RELEASE) $(LIBDIR_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE) -o $(OUT_RELEASE)

$(OBJDIR_RELEASE)/src/scenes/WorldScene.o: src/scenes/WorldScene.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/scenes/WorldScene.cpp -o $(OBJDIR_RELEASE)/src/scenes/WorldScene.o

$(OBJDIR_RELEASE)/src/scenes/FightScene.o: src/scenes/FightScene.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/scenes/FightScene.cpp -o $(OBJDIR_RELEASE)/src/scenes/FightScene.o

$(OBJDIR_RELEASE)/src/net/Sender.o: src/net/Sender.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/net/Sender.cpp -o $(OBJDIR_RELEASE)/src/net/Sender.o

$(OBJDIR_RELEASE)/src/net/Receiver.o: src/net/Receiver.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/net/Receiver.cpp -o $(OBJDIR_RELEASE)/src/net/Receiver.o

$(OBJDIR_RELEASE)/src/net/BaseNetwork.o: src/net/BaseNetwork.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/net/BaseNetwork.cpp -o $(OBJDIR_RELEASE)/src/net/BaseNetwork.o

$(OBJDIR_RELEASE)/src/base/main.o: src/base/main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/main.cpp -o $(OBJDIR_RELEASE)/src/base/main.o

$(OBJDIR_RELEASE)/src/base/BaseRoot.o: src/base/BaseRoot.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/BaseRoot.cpp -o $(OBJDIR_RELEASE)/src/base/BaseRoot.o

$(OBJDIR_RELEASE)/src/base/SceneManager.o: src/base/SceneManager.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/SceneManager.cpp -o $(OBJDIR_RELEASE)/src/base/SceneManager.o

$(OBJDIR_RELEASE)/src/base/Player.o: src/base/Player.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/Player.cpp -o $(OBJDIR_RELEASE)/src/base/Player.o

$(OBJDIR_RELEASE)/src/base/Monster.o: src/base/Monster.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/Monster.cpp -o $(OBJDIR_RELEASE)/src/base/Monster.o

$(OBJDIR_RELEASE)/src/base/FrameListener.o: src/base/FrameListener.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/FrameListener.cpp -o $(OBJDIR_RELEASE)/src/base/FrameListener.o

$(OBJDIR_RELEASE)/src/base/DemoApp.o: src/base/DemoApp.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/base/DemoApp.cpp -o $(OBJDIR_RELEASE)/src/base/DemoApp.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf ./bin/Release
	rm -rf $(OBJDIR_RELEASE)/src/scenes
	rm -rf $(OBJDIR_RELEASE)/src/net
	rm -rf $(OBJDIR_RELEASE)/src/base

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

