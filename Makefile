# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 14:07:23 by pbalbino          #+#    #+#              #
#    Updated: 2024/01/09 12:22:18 by pbalbino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra

READLINE_PATH = $(shell brew --prefix readline)
INC = -I./includes/ -I$(READLINE_PATH)/include
LDFLAGS = -L$(READLINE_PATH)/lib -lreadline

#INC = -I./includes/
#LDFLAGS = -lreadline

SRC_PATH = ./
OBJ_PATH = objects/

# Add all source files here
SRC	=	main.c						\
	aux_functions/ft_isspace.c		\
	aux_functions/ft_putstr_fd.c	\
	aux_functions/list_utils.c		\
	aux_functions/ft_atol.c			\
	aux_functions/ft_strlen.c		\
	aux_functions/ft_lstsize.c		\
	aux_functions/ft_lstadd_back.c	\
	aux_functions/ft_lstclear.c		\
	aux_functions/ft_lst_tokens.c	\
	aux_functions/ft_lstnew.c		\
	aux_functions/ft_lstdelone.c	\
	aux_functions/ft_split.c		\
	aux_functions/ft_split2.c		\
	aux_functions/ft_memset.c		\
	aux_functions/ft_substr.c		\
	aux_functions/ft_strncmp.c		\
	aux_functions/ft_strdup.c		\
	aux_functions/ft_isalnum.c		\
	aux_functions/ft_isdigit.c		\
	aux_functions/ft_isalpha.c		\
	aux_functions/ft_itoa.c			\
	aux_functions/ft_strcmp.c		\
	aux_functions/ft_strchr.c		\
	aux_functions/ft_strtrim.c		\
	aux_functions/ft_strjoint.c		\
	parsing/variable_expansion.c	\
	parsing/variable_expansion2.c	\
	parsing/variable_expansion3.c	\
	parsing/variable_expansion4.c	\
	parsing/quote_removal.c			\
	parsing/quote_removal2.c		\
	parsing/env.c					\
	parsing/free_resources.c		\
	parsing/parse_input.c			\
	parsing/parse_lexical.c			\
	parsing/parse_lexical_utils.c	\
	parsing/build_commands.c		\
	parsing/build_commands_utils.c	\
	parsing/path_utils.c 			\
	parsing/work_dir.c 				\
	parsing/io_init.c 				\
	parsing/heredoc_exec.c 			\
	syntax/append.c 				\
	syntax/arguments.c 				\
	syntax/heredoc.c 				\
	syntax/heredoc_utils.c 			\
	syntax/pipe.c 					\
	syntax/redir_in.c 				\
	syntax/redir_out.c 				\
	syntax/syntax_utils.c 			\
	syntax/word.c 					\
	execution/exec_command.c 		\
	execution/errors.c 				\
	execution/redirection_io.c 		\
	execution/clean.c 				\
	execution/pipes.c				\
	execution/execute.c				\
	execution/utils.c				\
	execution/signal_handler.c		\
	execution/export_utils.c		\
	execution/exec_utils.c			\
	execution/exit.c 				\
	builtins/cd_builtin.c			\
	builtins/cd_builtin_utils.c		\
	builtins/echo_builtin.c			\
	builtins/env_builtin.c			\
	builtins/exit_builtin.c			\
	builtins/export_builtin.c		\
	builtins/pwd_builtin.c			\
	builtins/unset_builtin.c


# Object files
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

# ANSI color codes
RED		= \033[0;31m
GREEN	= \033[0;32m
NC		= \033[0m # No Color

# Progress bar variables
TOTAL_FILES := $(words $(SRC))
CURRENT_FILE := 0

define show_progress
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
    @printf "\rProgress: ["; \
    for number in $$(seq 1 $(TOTAL_FILES)); do \
        if [ $$number -le $(CURRENT_FILE) ]; then \
            printf "="; \
        else \
            printf " "; \
        fi; \
    done; \
    printf "] $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))%% Compiling  \033[K$<"
endef

# Rules
all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH) $(addprefix $(OBJ_PATH)/, aux_functions execution parsing syntax builtins)
	@echo "$(GREEN)Created object directories$(NC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(call show_progress)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@printf "\r\033[K$(GREEN)Compiled $(NAME)$(NC)\n"

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)Cleaned object files$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Removed $(NAME)$(NC)"

re: fclean all

.PHONY: all re clean fclean
