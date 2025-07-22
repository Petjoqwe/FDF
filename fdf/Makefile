# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by student          #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by student         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes
LIBFT_DIR	= libft

# Source files
SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/parse_map.c \
			  $(SRC_DIR)/parse_utils.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/render_utils.c \
			  $(SRC_DIR)/draw_line.c \
			  $(SRC_DIR)/events.c \
			  $(SRC_DIR)/utils.c \
			  $(SRC_DIR)/free_utils.c \
			  $(SRC_DIR)/projection.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT		= $(LIBFT_DIR)/libft.a
MLX42_DIR	= MLX42
MLX42		= $(MLX42_DIR)/build/libmlx42.a

# Include paths
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX42_DIR)/include

# MLX42 flags (Linux)
MLX_FLAGS	= -ldl -lglfw -pthread -lm

# Colors
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
NC			= \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX42) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(NC)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)libft built successfully!$(NC)"

$(MLX42):
	@echo "$(YELLOW)Building MLX42...$(NC)"
	@if [ ! -d "$(MLX42_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
	fi
	@cd $(MLX42_DIR) && cmake -B build && cmake --build build -j4
	@echo "$(GREEN)MLX42 built successfully!$(NC)"

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@echo "$(RED)Cleaning executables...$(NC)"
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@$(RM) -r $(MLX42_DIR)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
