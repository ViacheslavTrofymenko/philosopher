# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 10:43:22 by vtrofyme          #+#    #+#              #
#    Updated: 2025/08/12 14:35:23 by vtrofyme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = \033[1m
RED = \033[31;2m
GREEN = \033[32m
YELLOW = \033[33m
RESET = \033[0m

NAME			= philo
SRC_DIR			= src
OBJ_DIR			= obj
INCLUDE_DIR		= include
SRC				= $(addprefix $(SRC_DIR)/, philo_main.c parse_args.c free_utils.c initialize.c philo_routine.c monitor.c)
TOTAL_SRCS 		:= $(words $(SRC))
OBJ				= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC 				= cc
CFLAGS			= -Wall -Wextra -Werror #-g3 -fsanitize=thread #-fsanitize=leak
INCLUDES		= -I$(INCLUDE_DIR)
RM 				= rm -rf

all: $(NAME)

$(NAME):$(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -lpthread -o $(NAME)
	@echo

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(eval SRC_NUM := $(shell expr $(SRC_NUM) + 1))
	@$(eval PERCENT := $(shell printf "%.0f" $(shell echo "scale=4; $(SRC_NUM) / $(TOTAL_SRCS) * 100" | bc)))
	@printf "$(BOLD)\rCompiling $(NAME): ["
	@$(eval PROGRESS := $(shell expr $(PERCENT) / 5))
	@printf "$(GREEN)%0.s#$(RESET)$(BOLD)" $(shell seq 1 $(PROGRESS))
	@if [ $(PERCENT) -lt 100 ]; then printf "%0.s-" $(shell seq 1 $(shell expr 20 - $(PROGRESS))); fi
	@printf "] "
	@if [ $(PERCENT) -eq 100 ]; then printf "$(GREEN)"; fi
	@printf "%d%% $(RESET)" $(PERCENT)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
