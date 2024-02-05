NAME = philo

CC = gcc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRC =  src/main.c src/parse.c src/utils.c src/actions.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
