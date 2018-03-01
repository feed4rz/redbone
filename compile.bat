g++ -c -o main.o main.cpp -I"C:\TDM-GCC-64\freeglut\include"

g++ -o main.exe main.o -L"C:\TDM-GCC-64\freeglut\lib\x64" -lfreeglut -lopengl32 -lglu32 -Wl,--subsystem,windows

pause