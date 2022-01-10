NAME		=	pipex

#CHECK_NAME	=	checker

#HEADER		=	pipex.h

SRCS		=	pipex.c utils.c split.c

OBJS		=	$(SRCS:.c=.o)
				
#CHECK_SRCS	=	checker.c validator.c validator_helper.c split.c initializer.c commands.c \
				sorting.c methods.c commands_wrap.c settings.c utils_func.c get_next_line/*.c
				
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror #-I$(HEADER)

.PHONY		:	all clean fclean re

all			:	$(NAME)

#bonus		:
#	@$(CC) $(CFLAGS) -o $(CHECK_NAME) $(CHECK_SRCS)

%.o:			%.c #$(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) 	:	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o  $(NAME)

clean		:	
	@rm -f $(OBJS)

fclean		:	clean
	@rm -f $(NAME) $(CHECK_NAME)

re:			fclean all