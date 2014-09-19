NAME=karatsuba

CXX=g++ -std=c++11

CXXFLAGS= -Werror

SRC=main.cpp

OBJ=$(SRC:.cpp=.o)

ALL: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $@ $^ 

re: fclean ALL

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: clean fclean