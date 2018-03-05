# redbone
OpenGL 2D Game Engine


## Compile on windows
Install TDM-GCC-64
Compile using ```compile.bat```

## Compile on mac os
Install HomeBrew

```
brew install gcc
brew cask install xquartz
brew install freeglut
```

Compile with
```
g++ -c -o main.o main.cpp
g++ -o main main.o -framework OpenGL -framework GLUT
```