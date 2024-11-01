# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 13:02:03 by mbaumgar          #+#    #+#              #
#    Updated: 2024/11/01 16:43:12 by mbaumgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

# ╔═╗╦  ╔═╗╔═╗╔═╗
# ╠╣ ║  ╠═╣║ ╦╚═╗
# ╚  ╩═╝╩ ╩╚═╝╚═╝

CC			= cc
ARFLAGS 	= -crs
RM			= rm -rf
CFLAGS		= -Wall -Werror -Wextra
DBG_LEAK	= -fsanitize=address -fsanitize=leak -g3
DBG_THREAD	= -fsanitize=thread -g3

# ╔═╗╔═╗╦  ╔═╗╦═╗╔═╗
# ║  ║ ║║  ║ ║╠╦╝╚═╗
# ╚═╝╚═╝╩═╝╚═╝╩╚═╚═╝

DUCK		= \033[38;2;8;195;187m
FLUO		= \033[38;2;223;255;0m
MAUVE		= \033[0;34m
RED			= \033[0;31m
END			= \033[m

# ╔═╗╔═╗╦ ╦╦═╗╔═╗╔═╗╔═╗
# ╚═╗║ ║║ ║╠╦╝║  ║╣ ╚═╗
# ╚═╝╚═╝╚═╝╩╚═╚═╝╚═╝╚═╝

SRC_DIR		= ./src/
OUT_DIR		= ./bin/
UTILS_DIR	= utils/

SRC			= main.c routine.c \
			$(UTILS_DIR)libft.c $(UTILS_DIR)utils.c $(UTILS_DIR)time.c

OBJ			= $(SRC:%.c=$(OUT_DIR)%.o)

# ╦═╗╦ ╦╦  ╔═╗╔═╗
# ╠╦╝║ ║║  ║╣ ╚═╗
# ╩╚═╚═╝╩═╝╚═╝╚═╝

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(DUCK)\nphilosophers$(END) ready! $(MAUVE)Have fun!$(END) • ᴗ •\n"
	@echo "$(FLUO)Command:$(END) ./philo [number_of_philosophers]"
	@echo "                 [time_to_die]            (in milliseconds)"
	@echo "                 [time_to_eat]            (in milliseconds)"
	@echo "                 [time_to_sleep]          (in milliseconds)"
	@echo "                 [number_of_meals]        (optional)"
	@echo "\n$(MAUVE)Example:$(END) ./philo 4 410 200 200 5\n"

$(OUT_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OUT_DIR)
	@mkdir -p $(OUT_DIR)$(OP_DIR) $(OUT_DIR)$(UTILS_DIR)
	$(CC) $(CFLAGS) -g3 -c $< -o $@

clean:
	$(RM) $(OUT_DIR)
	@echo "🧹 $(RED)removed:$(END) objects"

fclean: clean
	$(RM) $(NAME)
	@echo "🧹 $(RED)removed:$(END) philo\n"

re: fclean all

uwu: re
	@$(MAKE) --no-print-directory clean

norminette:
	@echo "\n"
	norminette inc/*
	@echo "\n"
	norminette src/*

leak: re
	$(CC) $(CFLAGS) $(DBG_LEAK) -o $(NAME) $(OBJ)

thread: re
	$(CC) $(CFLAGS) $(DBG_THREAD) -o $(NAME) $(OBJ)

git: fclean
	cd ..
	git add .
	git commit -m "update from philo : $(m)"
	git push

.PHONY: all clean fclean re uwu norminette leak thread git
