#FILES specifies which files to compile as part of the project
FILES = src\main.c src\menu_screen.c src\game_screen.c src\win_screen.c src\globals.c src\button\button.c src\tile\tile.c src\cursor\cursor.c src\texture\texture.c

#CC specifies which compiler we're using
CC = gcc

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\SDL_dev\SDL2\include\SDL2 -IC:\SDL_dev\SDL2_image\include\SDL2 -IC:\SDL_dev\SDL2_ttf\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\SDL_dev\SDL2\lib -LC:\SDL_dev\SDL2_image\lib -LC:\SDL_dev\SDL2_ttf\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# (-w) suppresses all warnings
# (-Wl,-subsystem,windows) gets rid of the console window
COMPILER_FLAGS = -Wall

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

#EXECUTABLE specifies the name of our exectuable
EXECUTABLE = build\main


#This is the target that compiles our executable
all : $(FILES)
	$(CC) $(FILES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXECUTABLE)

