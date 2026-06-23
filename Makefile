CC = gcc
CFLAGS = -O1

cJSON = include/cJSON/cJSON.c
SRCS = $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)

OBJ_PATH = build/
OBJS = $(addprefix $(OBJ_PATH), $(notdir $(SRCS:.c=.o)))

INCLUDES = include
LIBS = lib -lraylib -lgdi32 -lwinmm -lbox2d -lm

TARGET = o.exe
D_TARGET = d.exe

$(TARGET) : $(OBJS)
	@echo "Compiling $(TARGET)..."
	@$(CC) $(CFLAGS) $(cJSON) $(OBJS) -o $(TARGET) -I $(INCLUDES) -L $(LIBS)
	@echo "$(TARGET) created successfuly"

# Compile all source files into object files
$(OBJ_PATH)%.o : src/%.c ; @echo "Updating $@" && $(CC) -c $< -o $@ -I $(INCLUDES)

$(OBJ_PATH)%.o : src/assets_manager/%.c ; @echo "Updating $@" && $(CC) -c $< -o $@ -I $(INCLUDES)

$(OBJ_PATH)%.o : src/gameplay/%.c ; @echo "Updating $@" && $(CC) -c $< -o $@ -I $(INCLUDES)

$(OBJ_PATH)%.o : src/state_machine/%.c ; @echo "Updating $@" && $(CC) -c $< -o $@ -I $(INCLUDES)

$(OBJ_PATH)%.o : src/state_machine/states/%.c ; @echo "Updating $@" && $(CC) -c $< -o $@ -I $(INCLUDES)

$(OBJ_PATH)%.o : src/systems/%.c ; @echo "Updating $@" && $(CC) -c $< -o $@ -I $(INCLUDES)

clear:
	@rm -f $(OBJS) $(TARGET) $(D_TARGET)
	@echo "Done: clearing build and executable files"
