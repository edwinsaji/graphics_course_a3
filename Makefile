CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./src/


BIN=bin/a3view
SRCS=src/main.cpp src/gl_framework.cpp src/earth.cpp src/texture.cpp src/shader_util.cpp src/camera.cpp src/matrices.cpp src/ONAS_state.cpp src/scene.cpp src/sky.cpp src/space.cpp
INCLUDES=src/main.hpp src/gl_framework.hpp src/earth.hpp src/texture.hpp src/shader_util.hpp src/camera.hpp src/matrices.hpp src/ONAS_state.hpp src/scene.hpp src/sky.hpp src/space.hpp

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES) | bin
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

bin:
	mkdir $@

clean:
	rm -rf *~ *.o $(BIN) bin 
