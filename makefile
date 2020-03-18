CUDA_PATH=/usr/local/cuda-10.1

CURRENT_PATH=$(shell pwd)

BIN_PATH=$(CURRENT_PATH)/bin
BUILD_PATH=$(CURRENT_PATH)/build
DUMP_PATH=$(CURRENT_PATH)/dump
SRC_PATH=$(CURRENT_PATH)/src

CC=g++
NVCC=$(CUDA_PATH)/bin/nvcc
NVPROF=$(CUDA_PATH)/bin/nvprof
NSIGHT_CLI=$(CUDA_PATH)/bin/nv-nsight-cu-cli
NVVP=$(CUDA_PATH)/bin/nvvp
GDB=gdb
CUDA_GDB=$(CUDA_PATH)/bin/cuda-gdb
MEMCHECK=$(CUDA_PATH)/bin/cuda-memcheck

CUDA_FLAGS=--gpu-architecture=sm_30
LINKER_ARGUMENTS=

EXEC=fourier_transform.out
EXEC_ARGS=

all: clean $(EXEC) run

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:src/%.cpp=%.o)

CUDA_SRCS := $(wildcard src/*.cu)
CUDA_OBJS := $(CUDA_SRCS:src/%.cu=%.o)

$(EXEC): $(OBJS) $(CUDA_OBJS)
	$(NVCC) $(CUDA_FLAGS) $(BUILD_PATH)/*.o -o $(BIN_PATH)/$(EXEC) $(LINKER_ARGUMENTS)

%.o: $(SRC_PATH)/%.cpp
	$(NVCC) $(CUDA_FLAGS) --device-c $^ -o $(BUILD_PATH)/$@ $(LINKER_ARGUMENTS)

%.o: $(SRC_PATH)/%.cu
	$(NVCC) $(CUDA_FLAGS) --device-c $^ -o $(BUILD_PATH)/$@ $(LINKER_ARGUMENTS)

run:
	$(BIN_PATH)/$(EXEC) $(EXEC_ARGS)

clean: SHELL:=/bin/bash
clean:
	find $(BIN_PATH) -type f -not -name '.gitignore' -delete
	find $(BUILD_PATH) -type f -not -name '.gitignore' -delete
	find $(DUMP_PATH) -type f -not -name '.gitignore' -delete