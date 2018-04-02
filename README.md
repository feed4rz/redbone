# redbone
OpenGL 2D Game Engine

- [Compile on windows](#compile-on-windows-)
- [Compile on mac os](#compile-on-mac-os-)
- [Methods](#methods-)
- - [Entity](#entity-class-)
- - [Renderer](#renderer-class-)

---

# Compile on windows
Install GCC
Install freeglut in your **GCC_PATH**

Compile your project with 
```
g++ -c -o main.o PROJECT_ENTRY_FILE.cpp -I"GCC_PATH"

g++ -o main.exe main.o -L"GCC_PATH\freeglut\lib\x64" -lfreeglut -lopengl32 -lglu32 -Wl,--subsystem,windows
```


# Compile on mac os
Install HomeBrew

```
brew install gcc
brew cask install xquartz
brew install freeglut
```

Compile your project with
```
g++ -c -o main.o PROJECT_ENTRY_FILE.cpp
g++ -o main main.o -framework OpenGL -framework GLUT
```

---

# Methods
List of all available methods for all classes


## Entity class
The object on the screen.

### void render()
Renders an Entity inside of a **Renderer** class


## Renderer class
Stores Entities and renders them each frame.

### Entity newEntity(args)
List of **args** in order:
- int **x** - Plain x coordinate of an Entity
- int **y** - Plain y coordinate of an Entity
- int **w** - Width of an Entity
- int **h** - Height of an Entity
- int **angle** - Rotation angle in **degrees** of an Entity
- float **r** - Red level of Entity's color (0-1)
- float **g** - Green level of Entity's color (0-1)
- float **b** - Blue level of Entity's color (0-1)

### void render()
Renders all stored Entities calling **render** method on them

### void run()
Runs main OpenGL loop. Required to initialize rendering.