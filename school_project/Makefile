.PHONY: clean fclean re all os check_sources check_headers

#######################################################################
#
# Makefile for C projects
# (OS detect)
# Version: 2 (Special)
#
#######################################################################

# Name of target executable
NAME		= Colleen Grace Sully
LANG		= C
PWD			= $$(pwd)
# Locations 
SRC_DIR		= srcs
INC_DIR		= includes
BIN_DIR		= bin
LIB_DIR		= lib

# Sources & Headers 
# - fill only with name of the file
# - make will check for the file in SRC_DIR
# - use "-" if empty
SRCS		=	Colleen.c Grace.c Sully.c

LIBRARIES	=	libft


# Openssl
# OPENSSL_VERSION=1.1
# OPENSSL_PATH= $(shell brew --prefix openssl@$(OPENSSL_VERSION))

C_DFLAGS	=	#-g3 -fsanitize=address
CFLAGS		=	-Wextra -Wall -Werror -DLIBFT_PATH=$(PWD) $(C_DFLAGS)

C_IFLAGS	=	-I$(LIB_DIR)/libft/includes
C_LFLAGS	=	-L$(LIB_DIR)/libft -lft



SRC_FILES	=	$(shell find $(SRC_DIR) | grep -E '$(shell echo $(SRCS) | tr ' ' '|')')
# HEADER_FILES=	$(shell find $(INC_DIR) | grep -E '$(shell echo $(HEADERS) | tr ' ' '|')')
OBJS		=	$(addprefix $(BIN_DIR)/, $(SRC_FILES:.c=.o))
C_IFLAGS	+=	$(addprefix -I,$(shell echo $(HEADER_FILES) | tr ' ' '\n' | rev | cut -d'/' -f2- | rev | sort | uniq))
C_LFLAG		+=	$(addprefix -L,$(addprefix $(LIB_DIR), $(LIBRARIES)))

# include prefix definitions
include fancyPrefix.mk

#   Main rule
all: gitinit display_os comp_lib check_sources $(NAME)
	@echo "$(PREFIX_INFO) done = $(CFLAGS)"

#	include OS detection
include detectOs.mk

#	check_sources :
#	simple bash script to check duplicates sources files 
check_sources:
	@duplicates=$$( echo $(SRC_FILES) | tr ' ' '\n' | rev | cut -d'/' -f1 | rev | sort | uniq -c | sed 's/^ *//g' | sed 's/ /./g' ) ; \
	error=0 ; \
	for source in $$duplicates ; do \
			if [ $$(echo $$source | cut -d '.' -f 1 | tr -d '\n' ) -gt 1 ] ; then \
				echo "$(PREFIX_DUPL)" Duplicates source files found for \"$$(echo $$source | cut -d '.' -f2- )\" in: ; \
				find $(SRC_DIR) | grep $$(echo $$source | cut -d '.' -f 2 | tr -d '\n' ); \
				error=1 ; \
			fi \
	done ; \
	if [ $$error -eq 1 ] ; then \
		echo "$(PREFIX_ERROR) Cannot manage duplicates files, aborting..." ; \
		exit 1 ; \
	fi

#	check_headers :
#	simple bash script to check duplicates header files 
check_headers:
	@duplicates=$$( echo $(HEADER_FILES) | tr ' ' '\n' | rev | cut -d'/' -f1 | rev | sort | uniq -c | sed 's/^ *//g' | sed 's/ /./g' ) ; \
	error=0 ; \
	for source in $$duplicates ; do \
			if [ $$(echo $$source | cut -d '.' -f 1 | tr -d '\n' ) -gt 1 ] ; then \
				echo "$(PREFIX_DUPL)" Duplicates header files found for \"$$(echo $$source | cut -d '.' -f2- )\" in: ; \
				find $(INC_DIR) | grep $$(echo $$source | cut -d '.' -f 2 | tr -d '\n' ); \
				error=1 ; \
			fi \
	done ; \
	if [ $$error -eq 1 ] ; then \
		echo "$(PREFIX_ERROR) Cannot manage duplicates files, aborting..." ; \
		exit 1 ; \
	fi

#	Compilation of libraries
comp_lib:
	@echo "$(PREFIX_INFO) Compiling libraries..."
	@for lib in $(LIBRARIES) ; do \
		make -C $(LIB_DIR)/$$lib ; \
		echo "\n$(PREFIX_INFO) library $$lib done."; \
	done

#	Clean of libraries
fclean_lib:
	@echo "$(PREFIX_CLEAN) Cleaning libraries."
	@for lib in $(LIBRARIES) ; do \
		echo "$(PREFIX_CLEAN) Cleaning library $$lib"; \
		make -C $(LIB_DIR)/$$lib fclean; \
	done

#	Bin directory
$(BIN_DIR):
	@echo "$(PREFIX_WARN) No bin dir found. Creating one."
	@mkdir -p $(BIN_DIR)

#	Linking rule
$(NAME): $(BIN_DIR) $(OBJS)
	@$(COMP) $(BIN_DIR)/$(SRC_DIR)/Colleen.o -o Colleen $(CFLAGS) $(C_LFLAGS)
	@echo "$(PREFIX_LINK) Linking done for: Colleen"
	@$(COMP) $(BIN_DIR)/$(SRC_DIR)/Grace.o -o Grace $(CFLAGS) $(C_LFLAGS)
	@echo "$(PREFIX_LINK) Linking done for: Grace"
	@$(COMP) $(BIN_DIR)/$(SRC_DIR)/Sully.o -o Sully $(CFLAGS) $(C_LFLAGS)
	@echo "$(PREFIX_LINK) Linking done for: Sully"


# Compilation rule 
$(BIN_DIR)/$(SRC_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER_FILES)
	@mkdir -p $(BIN_DIR)/$(shell dirname $<)
	@$(COMP) -c $< -o $@ $(CFLAGS) $(C_IFLAGS)
	@echo "$(PREFIX_COMP) Compiled: $(shell basename $<)"

# clean rule
clean:
	@echo "$(PREFIX_CLEAN) Cleaning $(BIN_DIR)/"
	@rm -rf $(BIN_DIR)
	@rm -rf Grace_kid.c Sully7 Sully6 Sully5 Sully4 Sully3 Sully2 Sully1 Sully0 Sully_7.c Sully_6.c Sully_5.c Sully_4.c Sully_3.c Sully_2.c Sully_1.c Sully_0.C

# final clean rule
fclean: fclean_lib clean
	@echo "$(PREFIX_CLEAN) Cleaning $(LIB_DIR)/"
	@rm -rf $(LIB_DIR)
	@echo "$(PREFIX_CLEAN) Cleaning Colleen"
	@rm -f Colleen
	@echo "$(PREFIX_CLEAN) Cleaning Grace"
	@rm -f Grace
	@echo "$(PREFIX_CLEAN) Cleaning Sully"
	@rm -f Sully

# remake rule
softre: clean all

# remake rule
re: fclean all

# git submodule initialisation

gitinit: 
	@mkdir -p ./lib/libft
	@find ./lib -maxdepth 1 -empty -type d -exec printf "$(PREFIX_WARN) The library directory is empty. Cloning library 'libft' into {}. " \; -exec git clone "https://github.com/NATHAN76543217/libft.git" {} \;
# @mkdir -p ./lib/argparse
# @find ./lib -maxdepth 0 -empty -type d -exec printf "$(PREFIX_WARN) The library directory is empty. Cloning library 'argparse' into {}" \; -exec git clone "https://github.com/NATHAN76543217/argparse.git" {}/argparse \;

