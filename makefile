# Important fields:
FILES = main.o textures/texture.o shaders/program.o shaders/material.o shaders/light.o models/model.o models/cube.o window/window.o window/camera.o debug/debug.o
HEADERS = cube.hpp program.hpp texture.hpp window.hpp model.hpp camera.hpp globals.hpp debug.hpp material.hpp light.hpp
INCLUDES := -I "libraries/includes" -I "headers"
LIB := -L "libraries/lib"
LIBRARIES := -lglfw3 -lglad -lopengl32 -lgdi32 -luser32 -lkernel32

# OS-Dependant commands:
# Currently set up for Windows Shell
RM := del /q
DIR := cd
ECHO := @echo

# Other fields:
GXX := g++
GXXFLAGS := -g
CACHE := build-cache
OUTPUT-NAME := run.exe

clean : introductions clear binaries

clear:
	$(ECHO)  Removing old objects...
	@for %%i in ($(subst /,\, $(FILES))) do $(RM) %%i
	$(ECHO)  Removing old binaries...
	@-$(RM)  $(OUTPUT-NAME)
	$(ECHO)  Cleaning done.
	$(ECHO).

binaries : $(FILES) $(addprefix, headers/,$(HEADERS))
	$(ECHO)  Linking objects...
	@$(GXX) -o $(OUTPUT-NAME) $(FILES) $(LIB) $(INCLUDES) $(LIBRARIES) $(GXXFLAGS)
	$(ECHO)  Project built successfully.
	$(ECHO).
	$(ECHO)  Build completed.

%.o : %.cpp
	$(ECHO)  Compiling object "$(@F)"...
	@$(GXX) -o $@ -c $< $(LIB) $(INCLUDES) $(LIBRARIES) $(GXXFLAGS)
	$(ECHO)  Object "$(@F)" compiled successfully.
	$(ECHO).

build : introductions binaries

introductions:
	$(ECHO)  ===============================
	$(ECHO)  Starting project build process.
	$(ECHO)  ===============================
	$(ECHO).
