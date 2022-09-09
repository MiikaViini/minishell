# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 19:07:08 by mviinika          #+#    #+#              #
#    Updated: 2022/09/09 10:26:22 by mviinika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_FILES = main.c

OBJS = $(SRC_FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

LIBFT = ./libft/libft.a

LIBFT_DIR = ./libft/

INC = ./include/

##COLOURS##
RED = \x1b[31;01m
GREEN = \x1b[32;01m
YELLOW = \x1b[33;01m
RESET = \x1b[32;00m

all: $(NAME)

$(NAME): Makefile $(OBJS) $(INC)
	@make -C $(LIBFT_DIR)
	@gcc -c $(FLAGS) $(SRC_FILES) -I $(INC)
	@gcc $(OBJS) -o $(NAME) $(LIBFT)
	@echo "$(GREEN)$(NAME) compiled$(RESET)"

clean:
	@echo "$(YELLOW)Deleting ft_ls objs$(RESET)"
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)

fclean: clean
	@echo "$(RED)Removing $(NAME) $(RESET)"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

so:
	clang-11 -nostartfiles -fPIC $(FLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

