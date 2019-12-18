

BUILD_ROOT := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

LOCAL_CPP_INCLUDES += -I$(BUILD_ROOT)/include
CC := g++
CPP_FLAGS += -g -std=c++11 -Wall
EXE := yatcc
SRC_FILES += $(BUILD_ROOT)/yatcc.cpp

all: build

build: $(EXE)

clean:
	rm -f $(EXE)

test-%:
	cd $(BUILD_ROOT)/testing; ./test_compiler.sh $(BUILD_ROOT)/$(EXE) $*

$(EXE): $(SRC_FILES)
	$(CC) $(CPP_FLAGS) $(LOCAL_CPP_INCLUDES) $(SRC_FILES) -o $(EXE)