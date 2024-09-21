SRCS =	srcs/main.cpp \
		libs/glad/glad.cpp \
		srcs/Shader.cpp \
		srcs/Camera.cpp \
		srcs/Frame.cpp \
		srcs/Mesh.cpp \
		srcs/Engine/Engine.cpp \
		srcs/Engine/Engine_Init.cpp \
		srcs/ObjParser/ObjParser.cpp \
		srcs/ObjParser/ObjParser_ParseF.cpp \
		srcs/ObjParser/ObjParser_Utils.cpp \
		srcs/ObjParser/ObjParser_BuildMesh.cpp \

OBJS = $(SRCS:%.cpp=%.o)

C = g++

OS = $(shell uname)

# CFLAGS - Compiler flags (where to find headers)
# LFLAGS - Linking flags (where to find library to link at - -L & -l)

CFLAGS = -Wall -Wextra -g 
CFLAGS += -Iincludes

ifeq ($(OS), Darwin)
	LFLAGS 	= -framework OpenGL 
	LFLAGS += libs/glfw/libglfw.3.3.dylib
else
	CFLAGS += -I/usr/include
	LFLAGS = -L/usr/lib/x86_64-linux-gnu/
	LFLAGS += -lGL -lglfw -ldl
endif

NAME = scop

%.o	:	%.cpp
	$(C) $(CFLAGS) -c $< -o $@

#######################################################################################
#######################################################################################

$(NAME):	$(OBJS)
	$(C) -fsanitize=address -g -o $@ $^ $(LFLAGS)

all:	$(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
