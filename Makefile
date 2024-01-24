NAME = philo/philo

CC = gcc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRC =  philo/main.c philo/parse.c philo/utils.c philo/routine.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
