NAME = rt
CC = clang
CFLAGS = -Ofast -march=native -Wall -Wextra -Werror -arch x86_64 -g -Wimplicit-function-declaration -I ./includes -I $(HOME)/.brew/Cellar/sdl2/2.0.5/include/SDL2 -I $(HOME)/.brew/Cellar/sdl2_ttf/2.0.14/include/SDL2 -I $(HOME)/.brew/Cellar/sdl2_image/2.0.1_2/include/SDL2 -I $(HOME)/.brew/Cellar/sdl2_gfx/1.0.1/include/SDL2
SRCS = 	gui/hook.c \
		gui/hook2.c \
		gui/graphiclib.c \
		gui/renderer.c \
		gui/loadingbar.c \
		gui/math.c \
		gui/buttons.c\
		gui/initgui.c \
		gui/colorutils.c \
		gui/api.c \
		gui/fog.c \
		utils/file.c \
		utils/threads.c \
		utils/flares.c \
		parser/get_infos.c \
		parser/init_cam.c \
		parser/check.c \
		parser/convert_to_hex.c \
		parser/init_default_values.c \
		parser/init_final_infos.c \
		parser/make_new_obj.c \
		parser/obj_infos.c \
		parser/init_spots.c \
		parser/init_recap_spots.c \
		parser/init_procedural_textures.c \
		rtv1.c \
		maths.c \
		maths2.c \
		list_funct.c \
		draw_image.c \
		intersec_plane.c \
		intersec_sphere.c \
		intersec_cylinder.c \
		intersec_cone.c \
		vectors.c \
		luminosity.c \
		shadows.c \
		shadows_obj.c \
		libft.c \
		get_next_line.c \
		get_proc_color.c \


SRCF = ./srcs/
OBJS = $(addprefix $(SRCF), $(SRCS:.c=.o))

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS)  -L $(HOME)/.brew/Cellar/sdl2/2.0.5/lib -lSDL2 -L $(HOME)/.brew/Cellar/sdl2_ttf/2.0.14/lib/ -lSDL2_ttf -L $(HOME)/.brew/Cellar/sdl2_image/2.0.1_2/lib -lSDL2_image  -L $(HOME)/.brew/Cellar/libpng/1.6.29/lib -lpng16 -lpng -lpng16.16  -L $(HOME)/.brew/Cellar/sdl2_gfx/1.0.1/lib -lSDL2_gfx
	@echo Compiling RT ...

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

start:
	./$(NAME)

sdl:
	brew install sdl2
	brew install sdl2_ttf
	brew install sdl2_image
	brew install libpng
	brew install sdl2_gfx



.PHONY: clean fclean all re $(NAME) start
