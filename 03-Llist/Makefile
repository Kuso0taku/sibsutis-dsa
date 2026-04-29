# Makefile для 03-Llist
ROOT = ..
CC = gcc
CFLAGS = -O0 -Wall -Wextra -Iinclude -I$(ROOT)/libs/utils/include -MMD
LDFLAGS =
LDLIBS = -lm

BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj

# Основной исполняемый файл
TARGET = $(BIN_DIR)/llist

# Тестовый исполняемый файл
TEST_TARGET = $(BIN_DIR)/test

# Категории объектных файлов
MAIN_OBJ_DIR = $(OBJ_DIR)/main
SRC_OBJ_DIR = $(OBJ_DIR)/src
EXT_OBJ_DIR = $(OBJ_DIR)/external
TEST_OBJ_DIR = $(OBJ_DIR)/test

# Исходные файлы
MAIN_SRC = src/main.c
LOCAL_SRCS = $(filter-out $(MAIN_SRC), $(wildcard src/*.c))
UTILS_SRC = $(ROOT)/libs/utils/src/utils.c
TEST_SRC = test.c

# Объектные файлы для основной программы
MAIN_OBJ = $(MAIN_OBJ_DIR)/main.o
LOCAL_OBJS = $(addprefix $(SRC_OBJ_DIR)/, $(notdir $(LOCAL_SRCS:.c=.o)))
UTILS_OBJ = $(EXT_OBJ_DIR)/utils.o
ALL_OBJS = $(MAIN_OBJ) $(LOCAL_OBJS) $(UTILS_OBJ)

# Объектные файлы для тестов (без main.o)
TEST_OBJ = $(TEST_OBJ_DIR)/test.o
TEST_OBJS = $(TEST_OBJ) $(LOCAL_OBJS) $(UTILS_OBJ)

# Файлы зависимостей
DEPS = $(ALL_OBJS:.o=.d) $(TEST_OBJ:.o=.d)

# Цель по умолчанию
all: $(TARGET)

# Линковка основной программы
$(TARGET): $(ALL_OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Линковка тестов
$(TEST_TARGET): $(TEST_OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Компиляция main.c
$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция остальных локальных .c файлов (data_list.c, list.c)
$(SRC_OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция внешней библиотеки utils.c
$(UTILS_OBJ): $(UTILS_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция test.c
$(TEST_OBJ): $(TEST_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание папки bin
$(BIN_DIR):
	mkdir -p $@

# Подключаем файлы зависимостей
-include $(DEPS)

# Очистка
clean:
	rm -rf $(BUILD_DIR)

# Запуск тестов (удобная цель)
test: $(TEST_TARGET)
	$(TEST_TARGET)

.PHONY: all clean test
