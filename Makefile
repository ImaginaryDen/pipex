NAME	=   pipex
LIBFT	=	./libft/libft.a
PATH_HEADER = ./header/
PATH_LIB = ./libft/
HEADER  =  ./header/pipex.h 

SRC_UTL = $(shell ls ./utils/*.c)
SRC_PIPE = $(shell ls ./pipe_cmd/*.c) 

SRCS		=	$(SRC_UTL) $(SRC_PIPE) pipex.c
OBG		=	$(SRCS:%.c=%.o)

CFLAGS	= #-Wall -Wextra -Werror 
RM		= rm -rf
CC		= gcc

all:		run_libft $(NAME) 

$(NAME):	 ${OBG} $(HEADER) $(LIBFT)
			$(CC) $(CFLAGS) ${OBG} $(LIBFT) -o $(NAME)

run_libft:	
			@make -C $(PATH_LIB)	

%.o: 		%.c	
			$(CC) $(CFLAGS) -I$(PATH_HEADER) -c $< -o $@

clean:
			$(RM) ${OBG} ${OBG_BONUS}
			@make -C $(PATH_LIB) clean

fclean:		clean
			$(RM) $(NAME) $(NAME_BONUS)
			@make -C $(PATH_LIB) fclean

re:			fclean all

test:
			make -s && ./$(NAME)

.PHONY: clean fclean re all bonus
