NAME		=	philo
SRC_DIR		=	./srcs/
INC_DIR		=	./includes/
SRCS		=	main.c\
				utils.c\
				routine.c\
				utils_2.c\
				check.c\

SRC_BASENAME    =    $(addprefix $(SRC_DIR), $(SRCS))
OBJS            =    $(SRC_BASENAME:.c=.o)
		CC		=	gcc
#		FLAGS	=	-Wall -Wextra -Werror -g3 -lpthread -pthread -I $(INC_DIR) -fsanitize=thread
		FLAGS	=	-Wall -Wextra -Werror -g3 -lpthread -pthread -I $(INC_DIR)

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
