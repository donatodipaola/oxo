
PROJECT_NAME=oxo
INCLUDE_DIR =include
SOURCE_DIR =src
BUILD_DIR=build

DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(*.h))

SOURCE_FILES = $(shell find $(SOURCE_DIR) -type f -name *.c)
OBJECT_FILES = $(patsubst $(SOURCE_DIR)%.c,$(BUILD_DIR)%.o,$(SOURCE_FILES))

CC=gcc
CFLAGS=-Wall -W -pedantic -std=c99

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(DEPS)
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(INCLUDE_DIR)

$(PROJECT_NAME): $(OBJECT_FILES)
	$(CC) -o $@ $^ -I$(INCLUDE_DIR)

clean:
	rm -rf oxo $(BUILD_DIR) *~ core $(INCDIR)/*~
