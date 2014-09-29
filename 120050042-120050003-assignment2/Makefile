OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw3 -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -Wall -lglut
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN2=01_triangle_dep
SRCS2=01_triangle_dep.cpp gl_framework.cpp
INCLUDES=gl_framework.hpp transformer.cpp

all: $(BIN2)


$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o  $(BIN2)
