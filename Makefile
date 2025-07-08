##
## EPITECH PROJECT, 2025
## Rush3
## File description:
## Makefile
##

SRC =	src/main.cpp \
		math/Point3D/Point3D.cpp \
		math/Vector3D/Vector3D.cpp \

NAME =	raytracer

OBJ =	$(SRC:.cpp=.o)

CXX =	g++

CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -I ./src -I ./math

all: $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)
	find . -name '*#*' -delete -or -name '*~' -delete

fclean: clean
	rm -f $(NAME)

re: fclean all