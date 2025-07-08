##
## EPITECH PROJECT, 2025
## Rush3
## File description:
## Makefile
##

SRC =	main.cpp \
		src/Tools/Math/Point3D/Point3D.cpp \
		src/Tools/Math/Vector3D/Vector3D.cpp \
		src/Tools/Math/Matrix/TransformMatrix.cpp \
		src/Factory/LightFactory/LightFactory.cpp \
		src/Factory/PrimitiveFactory/PrimitiveFactory.cpp \
		src/Tools/ConfigNode/ConfigNode.cpp \
		src/RayTracer/Ray/Ray.cpp \
		src/RayTracer/Scene/Scene.cpp \
		src/RayTracer/Camera/Camera.cpp \
		src/Plugins/Sphere/Sphere.cpp

NAME =	raytracer

OBJ =	$(SRC:.cpp=.o)

CXX =	g++

CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -I ./src

all: $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)
	find . -name '*#*' -delete -or -name '*~' -delete

fclean: clean
	rm -f $(NAME)

re: fclean all