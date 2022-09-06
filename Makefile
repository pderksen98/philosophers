# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pderksen <pderksen@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/22 14:33:13 by pderksen      #+#    #+#                  #
#    Updated: 2022/09/06 13:30:28 by pieterderks   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME := philo
CC := gcc

# Colors
GREEN=\033[0;32m
RED=\033[0;31m
COLOUR_END=\033[0m

# Directories
INCL_DIR := -I./includes
OBJ_DIR := obj
SRC_DIR := src
VPATH := $(subst $(space),:,$(shell find $(SRC_DIR) -type d))

ifndef DEBUG
CC := gcc
CFLAGS := -Wall -Wextra -Werror
else
CC := clang
CFLAGS := -Wall -Wextra -Werror -fsanitize=thread -g -DDEBUG=1
endif

#Source and object files
SRCS := main.c \
		utils.c \
		atoi.c \
		initialize.c
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))


all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)---------- EXACUTABLE CREATED ----------$(COLOUR_END)"

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< $(INCL_DIR) -o $@

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)
			
clean :
	rm -rf $(OBJS) $(OBJ_DIR)
	@echo "$(RED)--------- OBJECT FILES DELETED ---------$(COLOUR_END)"
	
fclean : clean
	rm -f $(NAME)
	@echo "$(RED)---------- EXACUTABLE DELETED ----------$(COLOUR_END)"
	
re : fclean $(NAME)

.PHONY : all, clean, fclean, re



#*************EXAMPLE*************#
#    all: library.c main.c
#    - $@ = all
#    - $< = library.c
#    - $^ = library.c main.c
#*********************************#

# -o : names the output file --> -o filename
# -c : Directs the compiler to suppress linking with ld(1) and to produce a .o file for each source file	

#@echo "$(COLOUR_GREEN)Creating executable$(COLOUR_END)"
# COLOUR_GREEN=\033[0;32m
# COLOUR_RED=\033[0;31m
# COLOUR_END=\033[0m


