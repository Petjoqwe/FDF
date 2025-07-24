NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRCS = ft_split.c \
       ft_atoi.c \
       ft_putendl_fd.c \
       ft_strlen.c \
       ft_strjoin.c \
       ft_strchr.c \
       ft_strdup.c \
       ft_substr.c \
       ft_strcpy.c \
       get_next_line.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 