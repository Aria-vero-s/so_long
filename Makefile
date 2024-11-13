# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 11:10:18 by asaulnie          #+#    #+#              #
#    Updated: 2024/11/13 14:40:39 by asaulnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror -ggdb3

INCLUDES = -Imlx -Ilibft -Iget_next_line -I/usr/include

LIBS = -L./mlx -lmlx -L./libft -lft -L/usr/lib/X11 -lXext -lX11

SRCS = sources/so_long.c sources/check_arg.c sources/display_images.c sources/load_map.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c ft_printf/ft_printf.c ft_printf/ft_itoa.c ft_printf/ft_strlen.c ft_printf/ft_itoa_base.c ft_printf/ft_printc.c ft_printf/ft_prints.c ft_printf/ft_printp.c ft_printf/ft_printd.c ft_printf/ft_printi.c ft_printf/ft_printu.c ft_printf/ft_printx.c ft_printf/ft_print88.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
