NAME		=	philo
SRC_DIR		=	./srcs/
INC_DIR		=	./includes/
SRCS		=	main.c\

SRC_BASENAME    =    $(addprefix $(SRC_DIR), $(SRCS))
OBJS            =    $(SRC_BASENAME:.c=.o)
		CC		=	gcc
		FLAGS	=	-Wall -Wextra -Werror -lpthread -pthread -g3 -I $(INC_DIR)

.c.o	:
		$(CC) $(FLAGS) -c $< -o $@

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean	:
		rm -rf $(OBJS)

fclean	:	clean
		rm -f $(NAME)

re		:	fclean all
