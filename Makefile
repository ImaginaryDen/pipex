NAME	=   pipex
HEADER  =   pipex.h

SRC_UTL = $(shell ls ./utils/*.c)
SRC_PIPE = $(shell ls ./pipe_cmd/*.c) 

SRCS		=	$(SRC_UTL) $(SRC_PIPE) pipex.c

OBG		=	$(SRCS:%.c=%.o)

CFLAGS	= -Wall -Wextra -Werror 
RM		= rm -rf
CC		= gcc

all:			$(NAME)

$(NAME):		${OBG} $(HEADER)
				$(CC) $(CFLAGS)  -o $(NAME) ${OBG}

%.o: 			%.c	
				$(CC) $(CFLAGS) -I./ -c $< -o $@

clean:
				$(RM) ${OBG} ${OBG_BONUS}

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)

re:				fclean all

test:
				make -s && ./$(NAME)

.PHONY: clean fclean re all bonus
