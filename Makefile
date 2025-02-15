# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 15:05:17 by mzhitnik          #+#    #+#              #
#    Updated: 2025/02/14 13:33:24 by mzhitnik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= so_long
NAME_B		:= so_long_bonus

CC = cc
CFLAGS		:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX		:= ./lib/MLX42

HEADERS		:= -I ./inc -I ./lib/MLX42/include

LIBS		:= $(LIBMLX)/build/libmlx42.a
LIBS_FLAGS	:= -ldl -lglfw -pthread -lm
SRCS_PATH	:= ./src
SRCS_B_PATH := ./src_bonus
OBJS_PATH	:= ./obj
OBJS_B_PATH	:= ./obj_bonus

LIBFT_PATH	:= ./lib/libft
LIBFT		:= $(LIBFT_PATH)/libft.a

SRCS := $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/map_val.c \
		$(SRCS_PATH)/map_check.c \
		$(SRCS_PATH)/map_flood_check.c \
		$(SRCS_PATH)/error.c \
		$(SRCS_PATH)/animate.c \
		$(SRCS_PATH)/mlx_init.c \
		$(SRCS_PATH)/events.c \
		$(SRCS_PATH)/draw_instances.c

SRCS_B := $(SRCS_B_PATH)/main_bonus.c \
		$(SRCS_B_PATH)/map_val_bonus.c \
		$(SRCS_B_PATH)/map_check_bonus.c \
		$(SRCS_B_PATH)/map_flood_check_bonus.c \
		$(SRCS_B_PATH)/error_bonus.c \
		$(SRCS_B_PATH)/animate_bonus.c \
		$(SRCS_B_PATH)/mlx_init_bonus.c \
		$(SRCS_B_PATH)/events_bonus.c \
		$(SRCS_B_PATH)/enemy_bonus.c \
		$(SRCS_B_PATH)/draw_instances_bonus.c

OBJS	:= $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)
OBJS_B	:= $(SRCS_B:$(SRCS_B_PATH)/%.c=$(OBJS_B_PATH)/%.o)

all: $(NAME)

$(NAME): $(LIBMLX) $(LIBS) $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(LIBS_FLAGS) $(LIBFT) $(HEADERS) -o $(NAME) 
	@echo "$(NAME) building completed ..."

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBMLX):
	@git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)

$(LIBS):
	@cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null 2>&1 && make -C $(LIBMLX)/build -j4 > /dev/null 2>&1
	@echo "libmlx42.a building completed ..."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) > /dev/null 2>&1

bonus: $(NAME_B)

$(NAME_B): $(LIBMLX) $(LIBS) $(OBJS_B) $(LIBFT)
	@$(CC) $(OBJS_B) $(LIBS) $(LIBS_FLAGS) $(LIBFT) $(HEADERS) -o $(NAME_B)
	@echo "$(NAME_B) building completed ..."

$(OBJS_B_PATH):
	@mkdir -p $(OBJS_B_PATH)

$(OBJS_B_PATH)/%.o: $(SRCS_B_PATH)/%.c | $(OBJS_B_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -rf $(OBJS_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@echo "cleaning completed ..."

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@echo "force cleaning completed..."

re: fclean all

cleanb:
	@rm -rf $(OBJS_B_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@echo "bonus and libft cleaning completed ..."

fcleanb: cleanb
	@rm -f $(NAME_B)
	@echo "bonus force cleaning completed..."

reb: fcleanb bonus

.PHONY: all clean fclean re bonus cleanb fcleanb reb
