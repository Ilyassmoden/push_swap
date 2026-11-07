MANDATORY_NAME = push_swap
BONUS_NAME = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror

UTILS_SRCS = $(wildcard utils/*.c)
OPERATIONS_SRCS = $(wildcard operations/*.c)

MANDATORY_SRC = $(UTILS_SRCS) $(OPERATIONS_SRCS) $(wildcard mandatory/*.c simple_algorithm/*.c medium_algorithm/*.c complex_algorithm/*.c)
MANDATORY_OBJS = $(MANDATORY_SRC:.c=.o)

BONUS_SRC = $(UTILS_SRCS) $(OPERATIONS_SRCS) $(wildcard bonus/*.c)
BONUS_OBJS = $(BONUS_SRC:.c=.o)

all: $(MANDATORY_NAME)

$(MANDATORY_NAME): $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) -o $(MANDATORY_NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(MANDATORY_NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
