.PHONY: all build run clean help
.SILENT:

# Компилятор и флаги
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
LDFLAGS := 

# Директории и файлы
BIN_DIR := .bin
TARGET := $(BIN_DIR)/main
SRC := main.cpp


# Цель по умолчанию
.DEFAULT_GOAL := help

all: build ## Сборка проекта (по умолчанию)

build: ## Компиляция
	mkdir -p $(BIN_DIR) && $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: build ## Запуск
	$(TARGET)

clean: ## Очистка
	rm -rf *.o $(BIN_DIR)

help: ## Отображает список доступных команд
	@echo "Доступные команды:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-30s\033[0m %s\n", $$1, $$2}'

