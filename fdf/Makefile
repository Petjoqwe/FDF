# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 10:00:00 by student          #+#    #+#              #
#    Updated: 2024/01/01 10:00:00 by student         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./libft
LDFLAGS = -L./libft -lft -lmlx42 -lglfw -lm

SRCDIR = src
OBJDIR = obj

SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/parse_map.c \
       $(SRCDIR)/parse_map_utils.c \
       $(SRCDIR)/render.c \
       $(SRCDIR)/render_utils.c \
       $(SRCDIR)/events.c \
       $(SRCDIR)/utils.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft

clean:
	rm -rf $(OBJDIR)
	@make -C libft clean

fclean: clean
	rm -f $(NAME)
	@make -C libft fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
