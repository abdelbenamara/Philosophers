# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/04 14:00:25 by abenamar          #+#    #+#              #
#    Updated: 2023/11/12 14:27:21 by abenamar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

INCLUDES := -I $(CURDIR)

LDLIBS := -pthread

SRCS := ft_strlen.c
SRCS += ft_strncmp.c

SRCS += ft_atos.c
SRCS += ft_stoa.c

SRCS += ft_pstderr.c

SRCS += ft_routine.c
SRCS += ft_simulate.c

SRCS += philo.c

OBJS := $(SRCS:.c=.o)

CC := cc

CFLAGS := -Wall
CFLAGS += -Wextra
CFLAGS += -Werror

RM := rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(LDLIBS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all 