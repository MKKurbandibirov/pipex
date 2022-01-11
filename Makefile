NAME		=	pipex

NAME_B		=	pipex_bonus

SRCS		=	pipex.c utils.c split.c

OBJS		=	$(SRCS:.c=.o)
				
SRCS_B		=	pipex_bonus.c utils_bonus.c split_bonus.c

OBJS_B		=	$(SRCS_B:.c=.o)
				
CC			=	gcc -g 
CFLAGS		=	-Wall -Wextra -Werror

.PHONY		:	all bonus clean fclean re

all			:	$(NAME)

bonus		:	$(NAME_B)

%.o:			%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) 	:	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o  $(NAME)

$(NAME_B)	:	$(OBJS_B)
	@$(CC) $(CFLAGS) $(OBJS_B) -o  $(NAME_B)

clean		:	
	@rm -f $(OBJS) $(OBJS_B)

fclean		:	clean
	@rm -f $(NAME) $(NAME_B)

re:			fclean all