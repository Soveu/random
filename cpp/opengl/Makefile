CC=clang++
FLAGS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -I glad/include/

triangle: triangle.cpp
	$(CC) $(FLAGS) triangle.cpp glad/src/glad.c -o triangle

hello: hello.cpp
	$(CC) $(FLAGS) hello.cpp glad/src/glad.c -o hello
