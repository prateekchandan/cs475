OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw3 -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -Wall
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN=toylogo
SRCS=parser.cpp turtle.cpp render_drawing.cpp gl_framework.cpp toylogo.cpp 
INCLUDES=parser.hpp turtle.hpp turtle_defs.hpp render_drawing.hpp gl_framework.hpp



all: $(BIN)


$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(BIN)
	rm -f *.o
	rm -f *~


