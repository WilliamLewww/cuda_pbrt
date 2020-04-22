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

all: clean $(EXEC)

SRCS := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJS := $(notdir $(SRCS:%.cpp=%.o))

CUDA_SRCS := $(wildcard src/*.cu)
CUDA_OBJS := $(notdir $(CUDA_SRCS:%.cu=%.o))

$(EXEC): $(OBJS) $(CUDA_OBJS)
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
clean:
	find $(BIN_PATH) -type f -not -name '.gitignore' -delete
	find $(BUILD_PATH) -type f -not -name '.gitignore' -delete
	find $(DUMP_PATH) -type f -not -name '.gitignore' -delete