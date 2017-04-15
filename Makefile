CC = clang++ -std=c++11 -I/usr/include -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib -L/usr/lib64 -O0
# # CC = clang++
LDFLAGS = -lGLEW -lGL -lGLU -lX11 -lpthread -lXrandr -lglut -lXi -lXmu -lm -lexpat
CXXFLAGS= -g -W -Wall -std=c++11 -Weffc++ -Wextra -pedantic

OBJ_LOC = ./build
INCLUDE_LOC = ./include
CPP_LOC = ./lib

EXEC = run

#gets the objects
SOURCES = $(shell find $(CPP_LOC)/*.cpp)
TO_OBJS = $(patsubst $(CPP_LOC)/%.cpp, $(OBJ_LOC)/%.o, $(SOURCES))
OBJS = $(patsubst $(OBJ_LOC)/main.o, , $(TO_OBJS))

$(OBJ_LOC)/%.o: $(CPP_LOC)/%.cpp $(INCLUDE_LOC)/%.h
	$(CC) $(CXXFLAGS) -c $< -o $@

compile: $(OBJS)
	$(CC) $(CXXFLAGS) $(CPP_LOC)/main.cpp -o $(EXEC) $(OBJS) $(LDFLAGS)

$(EXEC): compile
	./run

test: $(OBJS)
	echo $(src)
clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
	rm -rf $(CPP_LOC)/*~
	rm -rf $(INCLUDE_LOC)/*~
	rm -rf xmlSpec/*~
	rm -rf *~
