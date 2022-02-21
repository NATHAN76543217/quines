.PHONY: all clean fclean re

# Name of file
NAME		=	quines_maker
# OUTPUT 		=	quined.c

# Name directory
PATH_SRC	=	srcs
PATH_INC	=	includes
PATH_OBJ	=	objs
PATH_LOG	=	logs
PATH_LIBFT	=	libft

# VIRUS  		=	BAD 
# CREATED_FILES = Coucou* $(VIRUS).c $(VIRUS) replica.c

src			= 	quine_maker.c 
# List of sources
SRCS		=	$(addprefix $(PATH_SRC)/ , $(src))
OBJS		=	$(addprefix $(PATH_OBJ)/, $(notdir $(SRCS:.c=.o)))
INCS		=	-I$(PATH_INC) -I$(PATH_LIBFT)/$(PATH_INC)
LOG			=	$(PATH_LOG)/$(NAME).log
LIBFT		=	-L$(PATH_LIBFT) -lft -lncurses

# Commands of compilation
CC			=	clang
COMP_FLAG	=	-Wall -Werror -Wextra

# Others Command
RM			=	/bin/rm

# Color Code and template code
_YELLOW		=	\033[38;5;184m
_GREEN		=	\033[38;5;46m
_RESET		=	\033[0m
_INFO		=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS	=	[$(_GREEN)SUCCESS$(_RESET)]

# Functions
all:	init $(NAME)
	@ echo "$(_SUCCESS) Compilation done"

init:
	@ $(shell mkdir -p $(PATH_OBJ) $(PATH_LOG))
	@ make -C $(PATH_LIBFT)

script:	init $(FILES)

$(NAME): $(OBJS)
	@ (set -x; $(CC) $(COMP_FLAG) $(INCS) -o $(NAME) $(OBJS) $(LIBFT)) >> $(LOG) 2>&1

$(PATH_OBJ)/%.o : $(PATH_SRC)/*/%.c
	@ (set -x; $(COMP) $(COMP_FLAG) -c $< -o $@) >> $(LOG) 2>&1
	@ echo "$(_INFO) Compilation of $*"

$(PATH_OBJ)/%.o : $(PATH_SRC)/%.c 
	@ (set -x; $(CC) $(COMP_FLAG) $(INCS) -c $< -o $@) >> $(LOG) 2>&1
	@ echo "$(_INFO) Compilation of $*"

clean:
	@ $(RM) -rf $(PATH_OBJ)
	@ $(RM) -rf $(CREATED_FILES)
	@ echo "$(_INFO) Deleted files and directory"

fclean: clean
	@ $(RM) -rf $(NAME)
	@ $(RM) -rf $(PATH_LOG)

re: fclean all
