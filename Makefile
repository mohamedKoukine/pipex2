# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 16:50:44 by mkaoukin          #+#    #+#              #
#    Updated: 2024/04/17 12:18:43 by mkaoukin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAMEB = pipex_bonus

CC = CC

FLAGS = -Wall -Wextra -Werror

SRC =	ft_split.c\
		parsing.c\
		ft_strjoin.c\
		ft_strcmp.c\
		ft_strncmp.c\
		ft_strdup.c\
		ft_substr.c\
		pipex.c

SRCB =	ft_split.c\
		parsing_bonus.c\
		ft_strjoin.c\
		ft_strcmp.c\
		ft_strncmp.c\
		ft_strdup.c\
		ft_substr.c\
		get_next_line_utils.c\
		get_next_line.c\
		pipex_bonus.c

OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)

INCLUDE = pipex.h


$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	
$(NAMEB): $(OBJB)
	$(CC) $(OBJB) -o $(NAMEB)

%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

bonus : $(NAMEB)

clean :
	rm -rf $(OBJ) $(OBJB)

fclean : clean
	rm -rf $(NAME) $(NAMEB)

re : fclean all

.PHONY : clean