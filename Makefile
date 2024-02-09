# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 17:51:13 by rtavabil          #+#    #+#              #
#    Updated: 2024/02/09 18:36:24 by rtavabil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

SRC := main.c strings.c error.c ft_split.c pipex_utils.c \
       pipex.c get_next_line.c get_next_line_utils.c
OBJ := $(SRC:.c=.o)

SRCB := pipex_bonus.c strings.c error.c ft_split.c pipex_utils.c \
        pipex.c get_next_line.c get_next_line_utils.c
OBJB := $(SRCB:.c=.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror

OBJ_PATH := obj/
OBJS := $(addprefix $(OBJ_PATH), $(OBJ))

BONUS_OBJ_PATH := bonus_obj/
BONUS_OBJS := $(addprefix $(BONUS_OBJ_PATH), $(OBJB))

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJ_PATH) $(BONUS_OBJ_PATH)

fclean: clean
	@rm -f $(NAME) pipex_bonus

re: fclean all

bonus: $(BONUS_OBJS)
	@$(CC) $(CFLAGS) -o pipex_bonus $(BONUS_OBJS)

$(BONUS_OBJ_PATH)%.o: %.c
	@mkdir -p $(BONUS_OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all re clean fclean bonus
