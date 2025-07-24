# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paguiler <paguiler@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by paguiler          #+#    #+#              #
#    Updated: 2025/07/23 02:32:17 by paguiler         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./libft -I./MLX42/include

SRCS = src/main.c \
       src/parse_map.c \
       src/free_map.c \
       src/utils.c \
       src/render.c \
       src/events.c \
       src/transform.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
MLX42 = MLX42/build/libmlx42.a

all: $(LIBFT) $(MLX42) $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@make -C libft

$(MLX42):
	@echo "Building MLX42..."
	@cd MLX42 && mkdir -p build && cd build && cmake .. && make

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -L./MLX42/build -lmlx42 -lglfw -ldl -lm -o $(NAME)
	@echo "$(NAME) created successfully!"

test: $(LIBFT)
	@echo "Building test..."
	$(CC) $(CFLAGS) test_simple.c -L./libft -lft -I./libft -o test_simple
	@echo "Test created successfully!"

test_gnl: $(LIBFT)
	@echo "Building GNL test..."
	$(CC) $(CFLAGS) test_gnl_simple.c -L./libft -lft -I./libft -o test_gnl_simple
	@echo "GNL test created successfully!"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@make -C libft clean
	@rm -f $(OBJS)
	@rm -f test_simple test_gnl_simple

fclean: clean
	@echo "Cleaning everything..."
	@make -C libft fclean
	@rm -f $(NAME)
	@rm -rf MLX42/build

re: fclean all

.PHONY: all clean fclean re test test_gnl 