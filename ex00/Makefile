NAME = btc
CXX1 = clang++
CXX2 = g++
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -Wshadow -std=c++98 -O3 #-g
#HEADER =

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC_FILES = main BitcoinExchange InputFile DataBase ParseException \
			OperationInterrupt

SRC = $(addsuffix .cpp, $(SRC_FILES))

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o : %.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	$(CXX) $(CXXFLAGS) $(OBJ) -g -o $(NAME)
	@echo "$(GREEN)Executable $(NAME) created!$(DEF_COLOR)"

bonus: all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

asif: re
	make fclean

strict:
	@echo "$(GREEN)Compiling with $(YELLOW)$(CXX1)$(GREEN)...$(DEF_COLOR)"
	@$(MAKE) all CXX=$(CXX1)
	@echo "$(GREEN)Cleaning up...$(DEF_COLOR)"
	@$(MAKE) fclean
	@echo "$(GREEN)Compiling with $(YELLOW)$(CXX2)$(GREEN)...$(DEF_COLOR)"
	@$(MAKE) all CXX=$(CXX2)
	@echo "$(GREEN)Cleaning up again...$(DEF_COLOR)"
	@$(MAKE) clean
	@echo "$(GREEN)Tested for both compilers.$(DEF_COLOR)"

.PHONY: all clean fclean re asif
