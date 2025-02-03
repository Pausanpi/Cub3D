NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
RM = rm -rf

MLX42_PATH = MLX42
MLX42 = $(MLX42_PATH)/build/libmlx42.a
#MLX42_BUILD_PATH = $(MLX42_PATH)/build

LIBFT_PATH = libs/libft
LIBFT = $(LIBFT_PATH)/libft.a

HEADERS = -I ./libs -I $(MLX42_PATH)/include/MLX42 -I $(LIBFT_PATH)

SRCS =	src/main.c \
		src/ft_raycast.c \
		src/parse.c src/map_checker.c src/textures.c \
		src/utils.c src/minimap.c src/keys.c src/draw.c

OBJS = $(SRCS:src/%.c=obj/%.o)

# colores?

######################################################

all : $(MLX42) $(LIBFT) $(NAME)

# .SILENT: pa silenciar echos

$(NAME): $(OBJS)
	@clear
	@echo "Linking $@..."
	@$(CC) $(CFLAGS) $(OBJS) $(MLX42) $(LIBFT) $(HEADERS) -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME) -lm
	@echo "\033[32mCompilation successful!\033[0m"
#añadido el -lm para linkear bien la libreria math y poder tener floor y ceiling y eso. Podriamos hacer las nuestras si no.

$(LIBFT):
	@echo "Building libft..."
	@make -s -C $(LIBFT_PATH)

$(MLX42):
	@echo "Building MLX42..."
	@cmake $(MLX42_PATH) -B $(MLX42_PATH)/build >/dev/null 2>&1
	@make -s -C $(MLX42_PATH)/build -j4 >/dev/null

obj/%.o: src/%.c
	@mkdir -p obj
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

clean:
	@clear
	@echo "Cleaning object files..."
	@$(RM) obj
	@make -s -C $(LIBFT_PATH) clean
	@make -s -C $(MLX42_PATH)/build clean >/dev/null 2>&1

fclean: clean
	@echo "Cleaning executable..."
	@$(RM) obj $(NAME)
	@make -s -C $(LIBFT_PATH) fclean
	@$(RM) $(MLX42_PATH)/build
	@echo "\033[32mCleaning successful!\033[0m"

re: fclean all

.PHONY: all clean fclean re

