OPENGLLIB= -lGL -lGLU
GLEWLIB= -lGLEW
GLFWLIB = -lglfw3 -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -Wall -lglut
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN2=transformer
SRCS2=main.cpp gl_framework.cpp transformer.cpp environment.cpp
INCLUDES=gl_framework.hpp transformer.hpp environment.hpp Imageloader.hpp

all: $(BIN2)
old:
	g++ $(CPPFLAGS) $(SRCS2) -o transformer_old $(LDFLAGS) $(LIBS)


$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o  $(BIN2) *.tar.gz transformer_old
