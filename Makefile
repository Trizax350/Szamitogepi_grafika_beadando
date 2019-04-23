all:
	gcc -oHorrorRoom.exe -Iinclude/ src/* -lSOIL -lopengl32 -lglu32 -lglut32 -std=c99
	
linux:
	gcc -oHorrorRoom.exe -Iinclude/ src/* -lSOIL -lGL -lGLU -lglut -std=c99