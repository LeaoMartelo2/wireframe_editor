.PHONY: clear
CC = g++
WINDOWS_COMPILER = x86_64-w64-mingw32-g++

DISABLED_WARNINGS = -Wno-missing-field-initializers -Wno-format-overflow

CPPFLAGS = -std=c++20 -Wall -Wextra $(DISABLED_WARNINGS) -O3 -pedantic -lm
CFLAGS = -std=c23 -Wall -Wextra $(DISABLED_WARNINGS) -O3 -pedantic -lm

POSIX_FLAGS = -L ./raylib/linux/ -lraylib
WINDOWS_FLAGS = -L ./raylib/windows/ -lraylib -lgdi32 -lwinmm -lopengl32 -static -mwindows

SRCDIR = src
OBJDIR = build/posix
WINOBJDIR = build/win32

SRC = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*.c)

OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%.o, $(SRC))
WINOBJ := $(patsubst $(SRCDIR)/%, $(WINOBJDIR)/%.o, $(SRC))

# Default target for Linux
editor: $(OBJ)
	$(CC) $^ $(CPPFLAGS) $(POSIX_FLAGS) -o editor

win: editor.exe

# Windows target
editor.exe: $(WINOBJ)
	$(WINDOWS_COMPILER) $^ $(CPPFLAGS) $(WINDOWS_FLAGS) -o editor.exe

# Compile object files for Linux
$(OBJDIR)/%.o: $(SRCDIR)/%
	@mkdir -p $(OBJDIR)
	$(if $(filter %.c,$<), $(CC) $(CFLAGS) $(POSIX_FLAGS) -x c -c $< -o $@, $(CC) $(CPPFLAGS) $(POSIX_FLAGS) -c $< -o $@)

# Compile object files for Windows
$(WINOBJDIR)/%.o: $(SRCDIR)/%
	@mkdir -p $(WINOBJDIR)
	$(if $(filter %.c,$<), $(WINDOWS_COMPILER) $(CFLAGS) $(WINDOWS_FLAGS) -x c -c $< -o $@, $(WINDOWS_COMPILER) $(CPPFLAGS) $(WINDOWS_FLAGS) -c $< -o $@)

# Clean all builds
clear: 
	@rm -f $(OBJDIR)/*.o $(WINOBJDIR)/*.o editor editor.exe
