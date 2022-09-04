# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dokwak <dokwak@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 15:32:26 by dokwak            #+#    #+#              #
#    Updated: 2022/09/04 21:31:13 by dokwak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color Aliases
DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SHELL=/bin/bash
UNAME = $(shell uname -s)

# Linux Valgrind
##ifeq ($(UNAME), Linux)
##	LEAKS = valgrind --leak-check=full --track-fds=yes --trace-children=yes -s -q 
##endif
# Mac Valgrind 
ifeq ($(UNAME), Darwin)
	LEAKS = valgrind --leak-check=full --track-fds=yes --trace-children=yes -s -q 
endif

AR = ar rcs
CFLAGS = -Wall -Wextra -Werror -MD -g3 
RM = rm -f
CC = gcc
PRINTF = LC_NUMERIC="en_US.UTF-8" printf
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .
#LIBFT = libft/libft.a
BIN = philo
NAME = $(BIN_DIR)/$(BIN)

SRC = main.c ft_atoi.c utils.c ft_strjoin.c ft_strlcat.c ft_strlen.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# LIBFT
# OBJ_LFT = $(addprefix $(OBJ_LFT_DIR)/, $(SRC_LFT:.c=.o))

# Progress vars
SRC_COUNT_TOT := $(shell expr $(shell echo -n $(SRC) | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_COUNT_TOT) -le 0; echo $$?),0)
	SRC_COUNT_TOT := $(shell echo -n $(SRC) | wc -w)
endif
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

all: $(NAME)

##########################################
############	LINKING		##############
##########################################
$(NAME): create_dirs $(OBJ)
	@$(CC) $(CFLAGS) $(CDEBUG) $(OBJ) -lpthread -o $@
	@$(PRINTF) "\r%100s\r$(GREEN)$(BIN) is up to date!$(DEFAULT)\n"

##########################################
############	COMPILING	##############
##########################################
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(BLUE)$<$(DEFAULT)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) $(CDEBUG) -c $< -o $@

# libft make
#compile_libft:
#	@make -C libft bonus

create_dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

run: all
	@$(LEAKS)./$(NAME) 10 20 30 40 50

clean:
	@$(PRINTF) "$(CYAN)Cleaning up object files in $(OBJ_DIR)...$(DEFAULT)\n"
#	@if [ -d "libft" ]; then \
#		make clean -C libft/; \
	fi
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) -r $(BIN_DIR)
	@$(PRINTF) "$(CYAN)Removed $(BIN)$(DEFAULT)\n"

re: fclean
	@make all

-include $(OBJ_DIR)/*.d
-include $(OBJB_DIR)/*.d

.PHONY: all clean fclean create_dirs re
