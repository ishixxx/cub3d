DEFAULT			= \033[0m
RED				= \033[1;31m
GREEN			= \033[1;32m
YELLOW			= \033[1;33m
MAGENTA			= \033[1;35m
CYAN			= \033[1;36m
WHITE			= \033[1;37m

COL1 			= \033[38;5;218m  # Rose clair
COL2 			= \033[38;5;182m  # Rose pâle
COL3 			= \033[38;5;245m  # Gris clair
COL4 			= \033[38;5;240m  # Gris foncé

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME =			cub3d
BONUS =			cub3d_bonus

CC =			cc
CFLAGS =		-Wall -Wextra -Werror -g3
AR =			ar rcs
RM =			rm -f

################################################################################
#                                PROGRAM'S SOURCES                             #
################################################################################

# Directory paths
SRCS_DIR =				./sources/
OBJS_DIR =				./objets/
SRCS_DIR_BONUS =		./sources_bonus/
OBJS_DIR_BONUS =		./objets_bonus/

MYLIB_DIR =		./libft/
MLX_DIR =		./minilibx-linux/
INCLUDES_DIR =	./includes/ ./libft/includes/

#Libraries

MYLIB =			-L $(MYLIB_DIR) -l:libft.a
MLX =			-L $(MLX_DIR) -l:libmlx.a -lXext -lX11 -lm

SRCS =			$(SRCS_DIR)/parsing/clean.c \
				$(SRCS_DIR)/parsing/color.c \
				$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/parsing/malloc_map.c \
				$(SRCS_DIR)/parsing/textures.c \
				$(SRCS_DIR)/parsing/utils.c \
				$(SRCS_DIR)/parsing/parse_map1.c \
				$(SRCS_DIR)/parsing/parse_map2.c \
				$(SRCS_DIR)/raycasting/draw.c \
				$(SRCS_DIR)/raycasting/raycasting.c \
				$(SRCS_DIR)/raycasting/render.c \
				$(SRCS_DIR)/raycasting/utils.c \
				$(SRCS_DIR)/initialisation.c \
				$(SRCS_DIR)/gameplay/events.c \
				$(SRCS_DIR)/gameplay/init_game.c \
				$(SRCS_DIR)/gameplay/movements.c \


OBJS =			$(patsubst $(SRCS_DIR)%, $(OBJS_DIR)%, $(SRCS:.c=.o))

SRCS_BONUS =	$(SRCS_DIR_BONUS)/parsing/clean.c \
				$(SRCS_DIR_BONUS)/parsing/color.c \
				$(SRCS_DIR_BONUS)/main.c \
				$(SRCS_DIR_BONUS)/parsing/malloc_map.c \
				$(SRCS_DIR_BONUS)/parsing/textures.c \
				$(SRCS_DIR_BONUS)/parsing/utils.c \
				$(SRCS_DIR_BONUS)/parsing/parse_map1.c \
				$(SRCS_DIR_BONUS)/parsing/parse_map2.c \
				$(SRCS_DIR_BONUS)/raycasting/draw.c \
				$(SRCS_DIR_BONUS)/raycasting/raycasting.c \
				$(SRCS_DIR_BONUS)/raycasting/render.c \
				$(SRCS_DIR_BONUS)/raycasting/utils.c \
				$(SRCS_DIR_BONUS)/initialisation.c \
				$(SRCS_DIR_BONUS)/gameplay/events.c \
				$(SRCS_DIR_BONUS)/gameplay/init_game.c \
				$(SRCS_DIR_BONUS)/gameplay/movements.c \
				$(SRCS_DIR_BONUS)/gameplay/mouse.c \
				$(SRCS_DIR_BONUS)/minimap/minimap.c \
				$(SRCS_DIR_BONUS)/minimap/minimap_utils.c \
				$(SRCS_DIR_BONUS)/minimap/minimap_player.c \

OBJS_BONUS =	$(patsubst $(SRCS_DIR_BONUS)%, $(OBJS_DIR_BONUS)%, $(SRCS_BONUS:.c=.o))

################################################################################
#                                     RULES                                    #
################################################################################

# Default rule
all:			$(NAME)
# Bonus rule
bonus:			$(BONUS)

# Rule for creating the executionutable
$(NAME):	$(OBJS)
			@make all --no-print-directory -C $(MYLIB_DIR)
			@echo "$(WHITE)Building $(YELLOW)mlx $(CYAN)library $(DEFAULT)..."
			@make all --no-print-directory -C $(MLX_DIR)
			@echo "$(GREEN)Done $(DEFAULT)✔️"
			@echo "$(WHITE)Linking $(YELLOW)$(NAME) $(CYAN)executable $(DEFAULT)..."
			@$(CC) $(CFLAGS) $(OBJS) $(MYLIB) $(MLX) -o $(NAME)
			@echo "$(GREEN)Done $(DEFAULT)✔️"
			@echo "$(COL1)  ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
			@echo "$(COL1) ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗"
			@echo "$(COL2) ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║"
			@echo "$(COL3) ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
			@echo "$(COL3) ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝"
			@echo "$(COL4)  ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ $(DEFAULT)"
			@echo "$(COL2)              ⠟⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "$(COL2)              ⢷⡄⠈⡓⠢⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⠤⠂⢹"
			@echo "$(COL3)              ⠈⡷⡄⠈⠲⢤⣈⠻⠉⠛⠉⠉⠁⠒⠖⠉⠉⠉⠒⠶⢦⣤⠴⠒⢉⣡⠴⠀⢀⠏"
			@echo "$(COL3)              ⠀⢸⡿⡂⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣴⡞⠉⠀⢀⣠⡞⠀"
			@echo "$(COL4)              ⠀⠀⢙⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⢠⡼⡟⠀⠀"
			@echo "$(COL4)              ⠀⠀⡼⠋⠀⣤⣀⠀⠀⠀⠀⠀⠈⠐⣂⣄⠀⠀⠀⠀⠀⠀⠀⢀⠀⣰⡟⠁⠀⠀"
			@echo "$(COL1)              ⠀⢠⡇⠀⠀⠘⠛⠃⠀⠀⠀⠀⠾⣿⠿⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀"
			@echo "$(COL1)              ⠀⢸⡇⢺⡀⠀⢠⡒⠠⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⡀⠀⠀⠸⡇⠀⠀⠀"
			@echo "$(COL2)              ⠀⢸⡇⣘⠑⡀⠀⠙⢏⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠂⠀⣔⣇⠀⠀⠀"
			@echo "$(COL2)              ⠀⢸⡇⡁⠀⢳⣶⣾⣷⣦⣄⣀⡀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠀⠀⠀"
			@echo "$(COL3)              ⠀⠸⡇⠁⠀⠀⢏⠉⠀⠀⠙⠛⠛⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⡏⠀⠀⠀"
			@echo "$(COL3)              ⠀⠀⠯⣀⣈⣀⣈⣐⣲⣄⣄⣤⣴⣆⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣈⣛⡧⠀$(DEFAULT)"

# Rule for creating the bonus executionutable
$(BONUS):	$(OBJS_BONUS)
			@make all --no-print-directory -C $(MYLIB_DIR)
			@echo "$(WHITE)Building $(YELLOW)mlx $(CYAN)library $(DEFAULT)..."
			@make all --no-print-directory -C $(MLX_DIR)
			@echo "$(GREEN)Done $(DEFAULT)✔️"
			@echo "$(WHITE)Linking $(YELLOW)$(BONUS) $(CYAN)executable $(DEFAULT)..."
			@$(CC) $(CFLAGS) $(OBJS_BONUS) $(MYLIB) $(MLX) -o $(BONUS)
			@echo "$(GREEN)Done $(DEFAULT)✔️"
			@echo "$(COL1)  ██████╗██╗   ██╗██████╗ ██████╗ ██████╗       ██████╗  ██████╗ ███╗   ██╗██╗   ██╗███████╗"
			@echo "$(COL1) ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗      ██╔══██╗██╔═══██╗████╗  ██║██║   ██║██╔════╝"
			@echo "$(COL2) ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║█████╗██████╔╝██║   ██║██╔██╗ ██║██║   ██║███████╗"
			@echo "$(COL3) ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║╚════╝██╔══██╗██║   ██║██║╚██╗██║██║   ██║╚════██║"
			@echo "$(COL3) ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝      ██████╔╝╚██████╔╝██║ ╚████║╚██████╔╝███████║"
			@echo "$(COL4)  ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝       ╚═════╝  ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚══════╝ $(DEFAULT)"
			@echo "$(COL2)              ⠟⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
			@echo "$(COL2)              ⢷⡄⠈⡓⠢⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⠤⠂⢹"
			@echo "$(COL3)              ⠈⡷⡄⠈⠲⢤⣈⠻⠉⠛⠉⠉⠁⠒⠖⠉⠉⠉⠒⠶⢦⣤⠴⠒⢉⣡⠴⠀⢀⠏"
			@echo "$(COL3)              ⠀⢸⡿⡂⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣴⡞⠉⠀⢀⣠⡞⠀"
			@echo "$(COL4)              ⠀⠀⢙⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⢠⡼⡟⠀⠀"
			@echo "$(COL4)              ⠀⠀⡼⠋⠀⣤⣀⠀⠀⠀⠀⠀⠈⠐⣂⣄⠀⠀⠀⠀⠀⠀⠀⢀⠀⣰⡟⠁⠀⠀"
			@echo "$(COL1)              ⠀⢠⡇⠀⠀⠘⠛⠃⠀⠀⠀⠀⠾⣿⠿⠟⠉⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀"
			@echo "$(COL1)              ⠀⢸⡇⢺⡀⠀⢠⡒⠠⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⡀⠀⠀⠸⡇⠀⠀⠀"
			@echo "$(COL2)              ⠀⢸⡇⣘⠑⡀⠀⠙⢏⣁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠂⠀⣔⣇⠀⠀⠀"
			@echo "$(COL2)              ⠀⢸⡇⡁⠀⢳⣶⣾⣷⣦⣄⣀⡀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠀⠀⠀"
			@echo "$(COL3)              ⠀⠸⡇⠁⠀⠀⢏⠉⠀⠀⠙⠛⠛⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⡏⠀⠀⠀"
			@echo "$(COL3)              ⠀⠀⠯⣀⣈⣀⣈⣐⣲⣄⣄⣤⣴⣆⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣈⣛⡧⠀$(DEFAULT)"

# Rule for compiling source files into object files
$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) -c $< -o $@ $(foreach dir,$(INCLUDES_DIR),-I$(dir))

# Rule for compiling bonus source files into object files
$(OBJS_DIR_BONUS)%.o:	$(SRCS_DIR_BONUS)%.c
						@mkdir -p $(dir $@)
						@$(CC) $(CFLAGS) -c $< -o $@ $(foreach dir,$(INCLUDES_DIR),-I$(dir))

# Rule for cleaning up object files
clean:
				@make clean --no-print-directory -C $(MYLIB_DIR)
				@echo "$(RED)Deleting $(CYAN)project object files $(DEFAULT)..."
				@$(RM) -r $(OBJS)
				@echo "$(GREEN)Done $(DEFAULT)✔️"

# Full clean rule (objects files, executionutable and libraries)
fclean:			
			@make fclean --no-print-directory -C $(MYLIB_DIR)
			@echo "$(RED)Deleting $(CYAN)project object files $(DEFAULT)..."
			@$(RM) -r $(OBJS_DIR) $(OBJS_DIR_BONUS)
			@echo "$(GREEN)Done $(DEFAULT)✔️"
			@echo "$(RED)Deleting $(YELLOW)$(NAME) $(CYAN)executable $(DEFAULT)..."
			@$(RM) $(NAME) $(BONUS)
			@echo "$(GREEN)Done $(DEFAULT)✔️"

# Rebuild rule
re:				fclean all

# Rule to ensure that these targets are always executionuted as intended, even if there are files with the same name
.PHONY:			all bonus clean fclean re