NAME		=	pipex

DIR			=	./mandatory_srcs

NAME_B		=	pipex_bonus

DIR_B		=	./bonus_srcs

SRCS		=	$(DIR)/pipex.c $(DIR)/utils.c $(DIR)/split.c

OBJS		=	$(SRCS:.c=.o)
				
SRCS_B		=	$(DIR_B)/pipex_bonus.c $(DIR_B)/utils_bonus.c $(DIR_B)/split_bonus.c $(DIR_B)/parsing.c $(DIR_B)/processing.c\
				get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

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