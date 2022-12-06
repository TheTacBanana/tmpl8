#OBJS specifies which files to compile as part of the project
OBJS = tmpl8.cpp 

#CC specifies which compiler we're using
CC = g++

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = tmpl8

#This is the target that compiles our executable
default : $(OBJS)
	$(CC) $(OBJS) -o $(OBJ_NAME) -lstdc++fs
	sudo cp $(OBJ_NAME) /usr/local/bin

run:
	./$(OBJ_NAME)
all:
	make
	./$(OBJ_NAME)