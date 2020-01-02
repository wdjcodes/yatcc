BUILD_ROOT := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

include $(BUILD_ROOT)/build-support/functions.mk

SRC_DIR := $(BUILD_ROOT)/src
OUT_DIR := $(BUILD_ROOT)/out
OBJ_DIR := $(OUT_DIR)/objs
EXE := yatcc
SRCS := $(call rwildcard,$(SRC_DIR),*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(SRCS))

CC := g++
CPP_FLAGS += -g -std=c++11 -Wall
LOCAL_CPP_INCLUDES += -I$(BUILD_ROOT)/include

all: build

build: $(OUT_DIR)/$(EXE)

clean:
	rm -rf $(OUT_DIR)

test-%:
	cd $(BUILD_ROOT)/testing; ./test_compiler.sh $(BUILD_ROOT)/$(EXE) $*

$(OUT_DIR)/$(EXE): $(OBJS)
	$(CC) $(CPP_FLAGS) $(LOCAL_CPP_INCLUDES) $(OBJS) -o $(OUT_DIR)/$(EXE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPP_FLAGS) $(LOCAL_CPP_INCLUDES) -c $< -o $@