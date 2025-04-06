# 菜鸟驿站管理系统 Makefile
# 作者: ctfy

# 编译器和编译选项
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include

# 目录结构
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
BUILD_DIR = build
DATA_DIR = data
TEST_DIR = test

# 目标可执行文件
TARGET = $(BIN_DIR)/cainiao

# 源文件 - 自动检测src目录下的所有.c文件
SRCS = $(wildcard $(SRC_DIR)/*.c)

# 目标文件
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# 确保输出目录存在
$(shell mkdir -p $(BIN_DIR))
$(shell mkdir -p $(BUILD_DIR))

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm
	@echo "编译完成: $@"

# 编译源文件生成目标文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "编译: $<"

# 添加main.c文件 (如果还没有)
main:
	@if [ ! -f $(SRC_DIR)/main.c ]; then \
		echo "创建main.c文件..."; \
		echo "#include \"../include/station.h\"\n\nint main() {\n    printf(\"菜鸟驿站管理系统启动...\\n\");\n    // TODO: 初始化系统并调用主菜单\n    return 0;\n}" > $(SRC_DIR)/main.c; \
	else \
		echo "main.c已存在"; \
	fi

# 清理生成的文件
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)
	@echo "清理完成"

# 清理并重新构建
rebuild: clean all

# 运行程序
run: all
	@echo "运行程序..."
	@./$(TARGET)

# 安装 - 创建必要的数据目录
install: all
	@mkdir -p $(DATA_DIR)
	@echo "安装完成"

# 调试
debug: CFLAGS += -g
debug: clean all
	@echo "调试版本已构建"

# 帮助信息
help:
	@echo "菜鸟驿站管理系统 Makefile 帮助"
	@echo "--------------------------------"
	@echo "make             - 构建整个项目"
	@echo "make clean       - 清理生成的文件"
	@echo "make rebuild     - 清理并重新构建"
	@echo "make run         - 构建并运行程序"
	@echo "make debug       - 构建调试版本"
	@echo "make install     - 安装程序"
	@echo "make main        - 创建main.c文件(如果不存在)"
	@echo "make help        - 显示帮助信息"

# 编译单个模块的规则
package: $(BUILD_DIR)/packege.o
	@echo "包裹模块已编译"

user: $(BUILD_DIR)/user.o
	@echo "用户模块已编译"

interface: $(BUILD_DIR)/user_interface.o
	@echo "界面模块已编译"

# 显示目录结构信息
info:
	@echo "项目信息:"
	@echo "源文件: $(SRCS)"
	@echo "目标文件: $(OBJS)"
	@echo "当前目录结构:"
	@ls -la

# 导出目标：这些不是文件名
.PHONY: all clean rebuild run install debug help package user interface info main