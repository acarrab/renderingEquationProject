CC = g++
# CC = clang++



OBJ_LOC = ./build
INCLUDE_LOC = ./include
CPP_LOC = ./lib

EXEC = run

#gets the objects
SOURCES = $(shell find $(CPP_LOC)/*.cpp)
TO_OBJS = $(patsubst $(CPP_LOC)/%.cpp, $(OBJ_LOC)/%.o, $(SOURCES))
OBJS = $(patsubst $(OBJ_LOC)/main.o, , $(TO_OBJS))


$(OBJ_LOC)/%.o: $(CPP_LOC)/%.cpp $(INCLUDE_LOC)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPP_LOC)/main.cpp -o $@ $(OBJS) $(LDFLAGS)
test:
	$(shell cat $(CPP_LOC)/gamedata.cpp | gawk 'match($0, /include[ ]*\"(.*)\"/, ary){ print ary[1] }')
clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
	rm -rf $(CPP_LOC)/*~
	rm -rf $(INCLUDE_LOC)/*~
	rm -rf xmlSpec/*~
	rm -rf *~
	rm frames/*.bmp
