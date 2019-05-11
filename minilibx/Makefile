#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

all: $(NOM)

$(NOM):	$(OBJ)
	@echo "Compiling minilibx..."
	@ar -r $(NOM) $(OBJ)
	@ranlib $(NOM)
	@echo "Minilibx is compiled!"

clean:
	@echo "Cleaning minilibx..."
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app
	@echo "Minilibx is cleaned!"

re: clean all
