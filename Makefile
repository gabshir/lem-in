# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/08 02:27:55 by jwillem-          #+#    #+#              #
#    Updated: 2019/05/17 19:33:38 by jwillem-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM-IN = lem-in
VISU-HEX = visu-hex

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -framework OpenGL -framework AppKit

SRCDIR = srcs
OBJDIR = obj

SRC-LEM-DIR = lem-in/
LEM-FILES = main	algo	tools	bfs	\
	freelinks	ant_flow	blokway	restorroom	\
	debug	patch_analysis	saveway		combination	
	#errors	val_tools	val_tools2
LEM-OBJ = $(addprefix $(OBJDIR)/$(SRC-LEM-DIR),$(addsuffix .o,$(LEM-FILES)))

SRC-VISU-DIR = visu-hex/
VISU-FILES = visual		test
VISU-OBJ = $(addprefix $(OBJDIR)/$(SRC-VISU-DIR),$(addsuffix .o,$(VISU-FILES)))

SRC-COMMON-DIR = common/
COMMON-FILES = errors	val_tools	val_tools2	get_map_info	rooms
COMMON-OBJ = $(addprefix $(OBJDIR)/$(SRC-COMMON-DIR),$(addsuffix .o,$(COMMON-FILES)))

#SRC = $(addprefix $(SRCDIR), $(addsuffix .c,$(FILES)))
#OBJ = $(addprefix $(OBJDIR),$(addsuffix .o,$(FILES)))

LIBFT = ./libft/libftprintf.a 
MLXLIB = ./minilibx/libmlx.a
INCDIR = -I ./includes
LIBLINK = -L ./libft -lftprintf -L ./minilibx -lmlx
LIBINC = -I ./libft/includes -I ./minilibx

all: $(LIBFT) $(MLXLIB) $(LEM-IN) $(VISU-HEX)

$(LIBFT):
	@make -C ./libft

$(MLXLIB):
	@make -C ./minilibx

$(OBJDIR):
	@echo "Creating object files directories..."
	@mkdir $(OBJDIR)
	@mkdir $(OBJDIR)/$(SRC-LEM-DIR)
	@mkdir $(OBJDIR)/$(SRC-VISU-DIR)
	@mkdir $(OBJDIR)/$(SRC-COMMON-DIR)
	@echo "Directories are created!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(FLAGS) $(INCDIR) $(LIBINC) -c $< -o $@

$(LEM-IN): $(LEM-OBJ) $(COMMON-OBJ)
	@echo "Compiling Lem-in..."
	@$(CC) $(LIBLINK) $(MLXFLAGS) -o $(LEM-IN) $(LEM-OBJ) $(COMMON-OBJ) 
	@echo "Lem-in is compiled!"

$(VISU-HEX): $(VISU-OBJ) $(COMMON-OBJ)
	@echo "Compiling Visu-hex..."
	@$(CC) $(LIBLINK) $(MLXFLAGS) -o $(VISU-HEX) $(VISU-OBJ) $(COMMON-OBJ)
	@echo "Visu-hex is compiled!"

libclean:
	@make clean -C ./libft
	@make clean -C ./minilibx

clean: libclean
	@echo "Deleting Lem-in object files..."
	@rm -rf $(OBJDIR)
	@echo "Lem-in object files are deleted!"

fclean: clean
	@echo "Deleting executables..."
	@rm -rf $(LEM-IN)
	@rm -rf $(VISU-HEX)
	@echo "Executables are deleted!"
	@make fclean -C ./libft
	@echo "Everything is cleaned!"

re: fclean
	@$(MAKE) all

test-bigs:
	./generator --big-superposition > test1; ./lem-in < test1

test-big:
	./generator --big > test1; ./lem-in < test1
