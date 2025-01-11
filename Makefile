# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llebugle <lucas.lebugle@student.s19.b      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/03 16:58:44 by llebugle          #+#    #+#              #
#    Updated: 2025/01/10 17:07:20 by llebugle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= philo
CC		= cc
#CFLAGS	= -Werror -Wall -Wextra -pthread
CFLAGS	= -pthread
MODE = none
ifeq ($(MODE), debug)
	CFLAGS	+= -fsanitize=thread -g
endif

SRCS_PATH = srcs/
OBJS_PATH = objs/

SRCS		=	main.c \
				utils.c \
				validate.c \
				sim.c		\
				supervisor.c \
				philosophers.c \
				debug.c		\
				
SRC	= $(addprefix $(SRCS_PATH), $(SRCS))
OBJ	= $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_PATH), $(OBJ))
INC = philo.h

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
