# **
# * Lab 4 makefile
# *
# * @author Jeff Stubler
# * @date 29 Jan 2012
# * 

SOURCE_PATH=src/
BUILD_PATH=bin/
EXEC = graph

CC = g++
CFLAGS = -c -Wall
LDFLAGS= -I/opt/local/include -L/opt/local/lib -lX11

SOURCES = $(wildcard $(SOURCE_PATH)*.cpp)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

all: $(SOURCES) $(BUILD_PATH)$(EXEC)

help:
	@echo "rules: all help clean"
	@echo $(SOURCES)
	@echo $(OBJECTS)

$(BUILD_PATH)$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(SOURCE_PATH)%.o: $(SOURCE_PATH)%.cpp
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f $(BUILD_PATH)*
	rm -f $(SOURCE_PATH)*.o
