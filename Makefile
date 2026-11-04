NAME=get_next_line
SRCS=get_next_line.c\
	get_next_line_utils.c
OBJS=$(SRCS:.c=.o)
CC=cc
CFLAGS=-Wall -Werror -Wextra
HEADERS=get_next_line.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
all: $(NAME)


fclean: clean
	rm -f $(NAME)
clean: 
	rm -f $(OBJS)

re: fclean all

.PHONY: all fclean clean re