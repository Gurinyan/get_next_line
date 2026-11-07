NAME=get_next_line
SRCS=get_next_line.c\
	get_next_line_utils.c
OBJS=$(SRCS:.c=.o)
CC=cc
CFLAGS=-Wall -Werror -Wextra
HEADERS=get_next_line.h
BONUS=get_next_line_bonus
SRCS_BONUS=get_next_line_bonus.c\
			get_next_line_utils_bonus.c
OBJS_BONUS=$(SRCS_BONUS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

$(BONUS): $(OBJS_BONUS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS)

bonus: fclean $(BONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)
clean: 
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

re: fclean all

.PHONY: all bonus fclean clean re bonus