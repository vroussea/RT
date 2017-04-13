NAME = rt
CC = clang
CFLAGS = -Ofast -mmmx -m3dnow -msse -msse2 -march=native -Wall -Wextra -Werror -arch x86_64 -g -Wimplicit-function-declaration -I ./includes -I $(HOME)/.brew/Cellar/sdl2/2.0.5/include/SDL2 -I $(HOME)/.brew/Cellar/sdl2_ttf/2.0.14/include/SDL2 -I $(HOME)/.brew/Cellar/sdl2_image/2.0.1_2/include/SDL2
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
		gui/flarebuttons.c \
		utils/file.c \
		utils/threads.c \
		utils/flares.c \
		utils/colors.c \
		utils/scalesurfaces.c \
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
		parser/init_obj_values.c \
		parser/init_obj_functs.c \
		rtv1.c \
		maths.c \
		maths2.c \
		maths3.c \
		list_funct.c \
		draw_image.c \
		calcs.c \
		intersec_plane.c \
		intersec_sphere.c \
		intersec_cylinder.c \
		intersec_cone.c \
		vectors.c \
		luminosity.c \
		shadows.c \
		shadows_obj.c \
		libft.c \
		libft2.c \
		libft3.c \
		get_next_line.c \
		get_proc_color.c \
		textures.c \
		parser/init_ref.c \
		recursive_ray.c \
		reflection_refraction.c

SRCF = ./srcs/
OBJS = $(addprefix $(SRCF), $(SRCS:.c=.o))

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS)  -L $(HOME)/.brew/Cellar/sdl2/2.0.5/lib -lSDL2 -L $(HOME)/.brew/Cellar/sdl2_ttf/2.0.14/lib/ -lSDL2_ttf -L $(HOME)/.brew/Cellar/sdl2_image/2.0.1_2/lib -lSDL2_image  -L $(HOME)/.brew/Cellar/libpng/1.6.29/lib -lpng16 -lpng -lpng16.16
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



.PHONY: clean fclean all re $(NAME) start
