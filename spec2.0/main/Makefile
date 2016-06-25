# -I[path of include] (You might need to modify)
INCLUDE =	../gtest/include
CXX =		g++
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -I$(INCLUDE)

TLIBPATH =	-L../gtest/lib
TLIBS =		-lgtest -lgtest_main

# program sources
MAIN_SOURCES =	$(filter-out ./ArcadeGameTests, $(basename $(shell find . -name "*.cpp")))
MAIN_OBJECTS =	$(addsuffix .o,$(MAIN_SOURCES))

TEST_SOURCES =	$(filter-out ./ArcadeGameMain, $(basename $(shell find . -name "*.cpp")))
TEST_OBJECTS =	$(addsuffix .o,$(TEST_SOURCES)) 

# The possible executables
EXEC =		ArcadeGameMain	ArcadeGameTests

# Echos all the test object files
.PHONY : echo
echo : 
	echo $(TEST_OBJECTS)

.PHONY : all
all : $(EXEC)

# cleans the object files and executables
.PHONY : clean
clean :
	find . -name "*.o" -delete
	find . -name "*.d" -delete
	rm -f $(EXEC)
	
#--- compiler targets
ArcadeGameTests : $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJECTS) $(TLIBPATH) $(TLIBS) -pthread

ArcadeGameMain : $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(MAIN_OBJECTS)


	
	
