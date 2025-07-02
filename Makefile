DEFAULT			= \033[0m
RED				= \033[1;31m
GREEN			= \033[1;32m
YELLOW			= \033[1;33m
MAGENTA			= \033[1;35m
CYAN			= \033[1;36m
WHITE			= \033[1;37m

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME =			cub3d
CC =			cc
CFLAGS =		-Wall -Wextra -Werror
AR =			ar rcs
RM =			rm -f

################################################################################
#                                PROGRAM'S SOURCES                             #
################################################################################

# Directory paths
SRCS_DIR =		./sources/
OBJS_DIR =		./objets/
MYLIB_DIR =		./libft/
MLX_DIR =		./minilibx-linux-master/
INCLUDES_DIR =	./includes/ ./libft/includes/

#Libraries

MYLIB =			-L $(MYLIB_DIR) -l:libft.a
MLX =			-L $(MLX_DIR) -l:libmlx.a -lXext -lX11 -lm

SRCS =			$(SRCS_DIR)/parsing/clean.c \
				$(SRCS_DIR)/parsing/color.c \
				$(SRCS_DIR)/parsing/main.c \
				$(SRCS_DIR)/parsing/malloc_map.c \
				$(SRCS_DIR)/parsing/read_file.c \
				$(SRCS_DIR)/parsing/textures.c \
				$(SRCS_DIR)/parsing/utils.c \
				$(SRCS_DIR)/parsing/parse_map1.c \
				$(SRCS_DIR)/parsing/parse_map2.c \
				$(SRCS_DIR)/raycasting/draw.c \
				$(SRCS_DIR)/raycasting/raycastiing.c \
				$(SRCS_DIR)/raycasting/render.c \
				$(SRCS_DIR)/raycasting/utils.c \
				$(SRCS_DIR)/initialisation.c \
				$(SRCS_DIR)/gameplay/events.c \


OBJS =			$(patsubst $(SRCS_DIR)%, $(OBJS_DIR)%, $(SRCS:.c=.o))

################################################################################
#                                     RULES                                    #
################################################################################

# Rule for compiling source files into object files
$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) -c $< -o $@ $(foreach dir,$(INCLUDES),-I$(dir))

# Rule for creating the executionutable
$(NAME):	$(OBJS)
			@make all --no-print-directory -C $(MYLIB_DIR)
			@echo "$(WHITE)Building $(YELLOW)mlx $(CYAN)library $(DEFAULT)..."
			@make all --no-print-directory -C $(MLX_DIR)
			@echo "$(GREEN)Done $(DEFAULT)✔️"
			@echo "$(WHITE)Linking $(YELLOW)$(NAME) $(CYAN)executable $(DEFAULT)..."
			@$(CC) $(CFLAGS) $(OBJS) $(MYLIB) $(MLX) -o $(NAME)
			@echo "$(GREEN)Done $(DEFAULT)✔️"

# Default rule
all:			$(NAME)

# Rule for cleaning up object files
clean:
				@make clean --no-print-directory -C $(MYLIB_DIR)
				@echo "$(RED)Deleting $(CYAN)project object files $(DEFAULT)..."
				@$(RM) -r $(OBJ)
				@echo "$(GREEN)Done $(DEFAULT)✔️"

# Full clean rule (objects files, executionutable and libraries)
fclean:			
			@make fclean --no-print-directory -C $(MYLIB_DIR)
			@echo "$(RED)Deleting $(CYAN)project object files $(DEFAULT)..."
			@$(RM) -r $(OBJS_DIR)
			@echo "$(GREEN)Done $(DEFAULT)✔️"
			@echo "$(RED)Deleting $(YELLOW)$(NAME) $(CYAN)executable $(DEFAULT)..."
			@$(RM) $(NAME)
			@echo "$(GREEN)Done $(DEFAULT)✔️"

# Rebuild rule
re:				fclean all

# Rule to ensure that these targets are always executionuted as intended, even if there are files with the same name
.PHONY:			all clean fclean re