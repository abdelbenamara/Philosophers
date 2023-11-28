# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/04 14:00:25 by abenamar          #+#    #+#              #
#    Updated: 2023/11/28 08:30:41 by abenamar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo_bonus

INCLUDES := -I $(CURDIR)

LDLIBS := -pthread

SRCS := ft_strlen.c
SRCS += ft_strncmp.c

SRCS += ft_atos.c
SRCS += ft_stoa.c

SRCS += ft_pstderr.c

SRCS += ft_sem_free.c
SRCS += ft_sem_init.c

SRCS += ft_routine.c
SRCS += ft_simulate.c

SRCS += philo_bonus.c

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

bonus: $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all bonus