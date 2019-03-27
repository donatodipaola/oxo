
PROJECT_NAME=oxo

INCLUDE_DIR =include
SOURCE_DIR =src
BUILD_DIR=build

MAKE_BUILD_DIR = $(shell mkdir -p $(BUILD_DIR))

HEADER_FILES = $(patsubst %,$(INCLUDE_DIR)/%,$(*.h))
SOURCE_FILES = $(shell find $(SOURCE_DIR) -type f -name *.c)
OBJECT_FILES = $(MAKE_BUILD_DIR) $(patsubst $(SOURCE_DIR)%.c,$(BUILD_DIR)%.o,$(SOURCE_FILES))

CC=gcc
CFLAGS=-Wall -W -pedantic -std=c99


$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADER_FILES)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(INCLUDE_DIR)

$(PROJECT_NAME): $(OBJECT_FILES)
	$(CC) -o $@ $^ -I$(INCLUDE_DIR)

clean:
	rm -rf $(PROJECT_NAME) $(BUILD_DIR) *~ core $(INCDIR)/*~
