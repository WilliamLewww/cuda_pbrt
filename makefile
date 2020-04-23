CUDA_PATH=/usr/local/cuda-10.2

CURRENT_PATH=$(shell pwd)

BIN_PATH=$(CURRENT_PATH)/bin
BUILD_PATH=$(CURRENT_PATH)/build
DUMP_PATH=$(CURRENT_PATH)/dump
SRC_PATH=$(CURRENT_PATH)/src

CC=g++
NVCC=$(CUDA_PATH)/bin/nvcc

CUDA_FLAGS=--gpu-architecture=sm_30

EXEC=cuda-pbrt.out
EXEC_ARGS=res/example.scene

HEXDUMP_EXEC=hexdump.out
HEXDUMP_EXEC_ARGS=dump/drive
HEXDUMP_EXEC_OUTPUT=output.txt

SRCS := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
SRCS := $(filter-out $(wildcard src/file_system/*.cpp), $(SRCS))
SRCS := $(filter-out $(wildcard src/hexdump/*.cpp), $(SRCS))

FILESYSTEM_SRCS := $(wildcard src/file_system/*.cpp)
HEXDUMP_SRCS := $(wildcard src/hexdump/*.cpp)

OBJS := $(notdir $(SRCS:%.cpp=%.o))
FILESYSTEM_OBJS := $(notdir $(FILESYSTEM_SRCS:%.cpp=%.o))
HEXDUMP_OBJS := $(notdir $(HEXDUMP_SRCS:%.cpp=%.o))

CUDA_SRCS := $(wildcard src/*.cu)
CUDA_OBJS := $(notdir $(CUDA_SRCS:%.cu=%.o))

all: clean-build $(EXEC)

hexdump: clean-build $(HEXDUMP_OBJS)
	$(NVCC) $(CUDA_FLAGS) $(BUILD_PATH)/*.o -o $(BIN_PATH)/$(HEXDUMP_EXEC)

filesystem: clean-dump $(FILESYSTEM_OBJS)
	$(NVCC) $(CUDA_FLAGS) $(BUILD_PATH)/*.o -o $(BIN_PATH)/$(EXEC)

$(EXEC): $(OBJS) $(FILESYSTEM_OBJS) $(CUDA_OBJS)
	$(NVCC) $(CUDA_FLAGS) $(BUILD_PATH)/*.o -o $(BIN_PATH)/$(EXEC)

%.o: $(SRC_PATH)/%.cpp
	$(NVCC) $(CUDA_FLAGS) --device-c $^ -o $(BUILD_PATH)/$@

%.o: $(SRC_PATH)/*/%.cpp
	$(NVCC) $(CUDA_FLAGS) --device-c $^ -o $(BUILD_PATH)/$@

%.o: $(SRC_PATH)/%.cu
	$(NVCC) $(CUDA_FLAGS) --device-c $^ -o $(BUILD_PATH)/$@

%.o: $(SRC_PATH)/*/%.cu
	$(NVCC) $(CUDA_FLAGS) --device-c $^ -o $(BUILD_PATH)/$@

run: run-core run-hexdump

run-core:
	$(BIN_PATH)/$(EXEC) $(EXEC_ARGS)

run-hexdump:
	$(BIN_PATH)/$(HEXDUMP_EXEC) $(HEXDUMP_EXEC_ARGS) > $(DUMP_PATH)/$(HEXDUMP_EXEC_OUTPUT)

clean: SHELL:=/bin/bash
clean: clean-bin clean-build clean-dump

clean-bin:
	find $(BIN_PATH) -type f -not -name '.gitkeep' -delete

clean-build:
	find $(BUILD_PATH) -type f -not -name '.gitkeep' -delete

clean-dump:
	find $(DUMP_PATH) -type f -not -name '.gitkeep' -delete