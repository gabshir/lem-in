# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/08 02:27:55 by jwillem-          #+#    #+#              #
#    Updated: 2019/05/16 21:15:17 by jwillem-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -framework OpenGL -framework AppKit

SRCDIR = srcs/
OBJDIR = obj/

FILES = main	rooms	val_tools	algo	tools	bfs	\
	freelinks	visual	ant_flow	blokway	restorroom	\
	errors	debug	patch_analysis	saveway get_map_info \
	combination
SRC = $(addprefix $(SRCDIR), $(addsuffix .c,$(FILES)))
OBJ = $(addprefix $(OBJDIR),$(addsuffix .o,$(FILES)))

LIBFT = ./libft/libftprintf.a 
MLXLIB = ./minilibx/libmlx.a
INCDIR = -I ./includes
LIBLINK = -L ./libft -lftprintf -L ./minilibx -lmlx
LIBINC = -I ./libft/includes -I ./minilibx

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C ./libft

$(MLXLIB):
	@make -C ./minilibx

$(OBJDIR):
	@echo "Creating Lem-in object files directory..."
	@mkdir $(OBJDIR)
	@echo "Directory created!"

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	@$(CC) $(FLAGS) $(INCDIR) $(LIBINC) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Compiling Lem-in..."
	@$(CC) $(LIBLINK) $(MLXFLAGS) -o $(NAME) $(OBJ)
	@echo "Lem-in is compiled!"

libclean:
	@make clean -C ./libft
	@make clean -C ./minilibx

clean: libclean
	@echo "Deleting Lem-in object files..."
	@rm -rf $(OBJDIR)
	@echo "Lem-in object files are deleted!"

fclean: clean
	@echo "Deleting lem-in executable..."
	@rm -rf $(NAME)
	@echo "Executable is deleted!"
	@make fclean -C ./libft
	@echo "Everything is cleaned!"

re: fclean
	@$(MAKE) all

test-bigs:
	./generator --big-superposition > test1; ./lem-in < test1

test-big:
	./generator --big > test1; ./lem-in < test1
