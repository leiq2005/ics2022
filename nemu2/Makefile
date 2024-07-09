# DIR
WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build

# 定义变量
CC := gcc
CFLAGS := -Wall -g
#CFLAGS := -Wall -Wextra -Werror -pedantic -g -O0
SRC := main.c
OBJ := $(BUILD_DIR)/main.o
EXEC := $(BUILD_DIR)/main

# 默认目标
all: $(EXEC)

# 创建构建目录
$(BUILD_DIR):
	@mkdir -p $@

# 编译目标文件
$(OBJ): $(SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
    # $< 在这里表示规则中的第一个依赖 $(SRC)，即 main.c
    # $@ 在这里表示规则中的目标 $(OBJ)，即 build/main.o

# 链接生成可执行文件
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

# 运行可执行文件
run: $(EXEC)
	$(EXEC)

debug: $(EXEC)
	gdb $(EXEC)
# 清理
clean:
	rm -rf $(BUILD_DIR)

# 伪目标
.PHONY: all clean run $(BUILD_DIR)