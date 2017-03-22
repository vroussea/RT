NAME = rt
CC = clang
CFLAGS = -Ofast -march=native  -msse -msse2 -msse3 -msse4 -Wall -Wextra -Werror -arch x86_64 -Wconversion -g -Wimplicit-function-declaration -I ./includes -I $(HOME)/.brew/Cellar/sdl2/2.0.5/include/SDL2
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
		rtv1.c \
		get_infos.c \
		maths.c \
		maths2.c \
		init_cam.c \
		check.c \
		convert_to_hex.c \
		init_default_values.c \
		init_final_infos.c \
		make_new_obj.c \
		obj_infos.c \
		init_spots.c \
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
		textures.c

SRCF = ./srcs/
OBJS = $(addprefix $(SRCF), $(SRCS:.c=.o))

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS)  -L $(HOME)/.brew/Cellar/sdl2/2.0.5/lib -lSDL2 -lSDL2_ttf
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
	cp ~/.brew/Cellar/sdl2_ttf/2.0.14/include/SDL2/SDL_ttf.h ~/.brew/Cellar/sdl2/2.0.5/include/SDL2/
	cp ~/.brew/Cellar/sdl2_ttf/2.0.14/lib/* ~/.brew/Cellar/sdl2/2.0.5/lib/

.PHONY: clean fclean all re $(NAME) start
