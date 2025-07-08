##
## EPITECH PROJECT, 2025
## Rush3
## File description:
## Makefile
##

SRC =	main.cpp \
		src/Plugins/Camera/Camera.cpp \
		src/Plugins/Primitives/Sphere/Sphere.cpp \
		src/Plugins/Primitives/Plane/Plane.cpp \
		src/Plugins/Primitives/Cone/Cone.cpp \
		src/Plugins/Primitives/Cylinder/Cylinder.cpp \
		src/Plugins/Renders/SFML/SFMLRenderer.cpp \
		src/Plugins/Material/FlatColor/FlatColor.cpp \
		src/Plugins/Light/AmbientLight/AmbientLight.cpp \
		src/Plugins/Light/DirectionnalLight/DirectionnalLight.cpp \
		src/RayTracer/Scene/Scene.cpp \
		src/RayTracer/LightManager/LightManager.cpp \
		src/Tools/ConfigNode/ConfigNode.cpp \
		src/Tools/Math/Matrix/TransformMatrix.cpp \
		src/Tools/Math/Point3D/Point3D.cpp \
		src/Tools/Math/Vector3D/Vector3D.cpp \
		src/Tools/Ray/Ray.cpp \
		src/RayTracer/Parser/Parser.cpp \
		src/RayTracer/Builder/sceneBuilder.cpp

NAME = raytracer

OBJ = $(SRC:.cpp=.o)

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -I ./src -g

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lconfig++

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	find . -name '*#*' -delete -or -name '*~' -delete

fclean: clean
	rm -f $(NAME)

re: fclean all