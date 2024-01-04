SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
CFLAGS := -MMD

app: $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^ -g

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -g -o $@ $<



