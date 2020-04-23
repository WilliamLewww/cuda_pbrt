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

SRCS := $(filter-out $(wildcard src/file_system/*.cpp), $(wildcard src/*.cpp) $(wildcard src/*/*.cpp))
OBJS := $(notdir $(SRCS:%.cpp=%.o))

FILESYSTEM_SRCS := $(wildcard src/file_system/*.cpp)
FILESYSTEM_OBJS := $(notdir $(FILESYSTEM_SRCS:%.cpp=%.o))

CUDA_SRCS := $(wildcard src/*.cu)
CUDA_OBJS := $(notdir $(CUDA_SRCS:%.cu=%.o))

all: clean $(EXEC)

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

run:
	$(BIN_PATH)/$(EXEC) $(EXEC_ARGS)

clean: SHELL:=/bin/bash
clean: clean-bin clean-build clean-dump

clean-bin:
	find $(BIN_PATH) -type f -not -name '.gitkeep' -delete

clean-build:
	find $(BUILD_PATH) -type f -not -name '.gitkeep' -delete

clean-dump:
	find $(DUMP_PATH) -type f -not -name '.gitkeep' -delete