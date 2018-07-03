#
#
BIN_DIR = ./bin

LIB_NAME = cppkafka
EXE_NAME = buffered_producer_example \
	   consumer_dispatcher_example \
	   consumer_example \
	   consumers_information_example \
	   metadata_example \
	   producer_example

RM :=rm -f 

LIB_SRCS = $(wildcard src/*.cpp src/utils/*.cpp)
LIB_OBJS = $(patsubst %.cpp,%.o,$(LIB_SRCS) )
EXE_SRCS = $(wildcard examples/*.cpp)
EXE_OBJS = $(patsubst %.cpp,%.o,$(EXE_SRCS) )

LIB_ARC = lib$(LIB_NAME).a

CXXFLAGS = -std=c++11 -g -Wall -fPIC
CPPFLAGS = -I./include -I./include/cppkafka
LINK_LIBS =-L./lib -L./bin/debug -lrdkafka -lboost_program_options  -lssl -lcrypto -lpthread -lz -ldl -lrt

all: dir $(LIB_ARC) $(EXE_NAME)

dir:
	if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR) ; fi;

$(LIB_ARC):$(LIB_OBJS)
	ar -cr $(BIN_DIR)/$@  $^

buffered_producer_example : examples/buffered_producer_example.o
	g++ $(CXXFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@  $^ -L$(BIN_DIR) -l$(LIB_NAME) $(LINK_LIBS)

consumer_dispatcher_example : examples/consumer_dispatcher_example.o
	g++ $(CXXFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@  $^ -L$(BIN_DIR) -l$(LIB_NAME) $(LINK_LIBS)

consumer_example : examples/consumer_example.o
	g++ $(CXXFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@  $^ -L$(BIN_DIR) -l$(LIB_NAME) $(LINK_LIBS)

consumers_information_example:examples/consumers_information_example.o
	g++ $(CXXFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@  $^ -L$(BIN_DIR) -l$(LIB_NAME) $(LINK_LIBS)

metadata_example:examples/metadata_example.o
	g++ $(CXXFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@  $^ -L$(BIN_DIR) -l$(LIB_NAME) $(LINK_LIBS)

producer_example:examples/producer_example.o
	g++ $(CXXFLAGS) $(CPPFLAGS) -o $(BIN_DIR)/$@  $^ -L$(BIN_DIR) -l$(LIB_NAME) $(LINK_LIBS)

clean:
	$(RM) $(LIB_OBJS) $(EXE_OBJS) $(EXE_OBJS)
	$(RM) $(BIN_DIR)/$(LIB_ARC)
	for x in $(EXE_NAME); do ($(RM) $(BIN_DIR)/$$x); done
#
#
