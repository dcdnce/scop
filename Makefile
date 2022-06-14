SRCS =	main.cpp my_GL.cpp shader.cpp
OBJS = $(SRCS:%.cpp=%.o)

C = clang++

# Compiler flags (+ where to find headers)
CFLAGS = -Wall -Wextra 
CFLAGS += -I/usr/include
# Linking flags (+ where to find library to link at - -L & -l)
LDFLAGS = -L/usr/lib/x86_64-linux-gnu/
LDFLAGS += -lGL -lglfw -ldl -lGLEW

NAME = prog

%.o	:	%.cpp
	$(C) $(CFLAGS) -c $< -o $@

#######################################################################################
#######################################################################################

$(NAME):	$(OBJS)
	$(C) -o $@ $^ $(LDFLAGS)

all:	$(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
