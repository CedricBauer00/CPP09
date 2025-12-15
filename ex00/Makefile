NAME = btc

SRC = src/main.cpp \
		src/BitcoinExchange
	
OBJ := $(SRC:%.cpp=%.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iinc

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) && echo "\033[32mCompilation successful\033[0m"

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ) && echo "\033[31mObjects cleared!\033[0m"

fclean:
	@rm -f $(NAME) &(OBJ) > /dev/null && echo "\033[31mProgram cleared successfully!\033[0m"

re: fclean all
	@echo "\033[36mRunning $(NAME)..."
	@echo "\n===== 31mProgram36m =====\n\033[0m"
	@./$(NAME)
.PHONY: all fclean re