# -------------------------------- DIRECTORIES --------------------------------- #
INC	= include

SRC_DIR	= src

MTH_DIR			= math
MLX_DIR			= mlx
OBJ_DIR			= objects
PRS_DIR			= parsing
RTC_DIR			= raytracing

LIBFT_DIR		= lib/libft
LIBFT_INC_DIR	= $(LIBFT_DIR)/include

ifeq ($(shell uname), Linux)
	LIBMLX_DIR	= lib/libmlx/linux
else
	LIBMLX_DIR	= lib/libmlx/macos
endif

# ------------------------------- COMPILER FLAGS ------------------------------- #
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -O3 -ffast-math

UTILS_FLAGS		= -lm -Llib -lft -lpthread

ifeq ($(shell uname), Linux)
	MLX_FLAGS	= -lmlx -lXext -lX11
else
	MLX_FLAGS	= -lmlx -framework openGL -framework AppKit
endif

# ----------------------------------- FILES ------------------------------------ #
SRCS			= $(addprefix $(SRC_DIR)/, \
					mrt.c \
					mrt_errors.c \
				$(addprefix $(MTH_DIR)/, \
					mrt_geometry_utils.c \
					mrt_mat3x3_inv.c \
					mrt_mat3x3_op.c \
					mrt_mat4x4_apply.c \
					mrt_mat4x4_inv.c \
					mrt_mat4x4_op.c \
					mrt_vec3_op1.c \
					mrt_vec3_op2.c) \
				$(addprefix $(MLX_DIR)/, \
					mrt_mlx.c \
					mrt_mlx_event.c \
					mrt_mlx_image.c) \
				$(addprefix $(OBJ_DIR)/, \
					mrt_checker.c \
					mrt_cone.c \
					mrt_cylinder.c \
					mrt_plane.c \
					mrt_sphere.c \
					mrt_objects.c) \
				$(addprefix $(PRS_DIR)/, \
					mrt_get_data1.c \
					mrt_get_data2.c \
					mrt_parse_obj.c \
					mrt_parse_param.c \
					mrt_parsing.c \
					mrt_scene_get.c \
					mrt_scene_read.c \
					mrt_set_cam.c \
					mrt_set_obj.c) \
				$(addprefix $(RTC_DIR)/, \
					mrt_color.c \
					mrt_intensity.c \
					mrt_raytracing.c \
					mrt_ray.c \
					mrt_render.c \
					mrt_thread.c))

OBJS		= $(SRCS:.c=.o)

# -------------------------------- COMPILATION --------------------------------- #
DEPS		= Makefile $(addprefix $(INC)/, mrt_math.h mrt_error.h mrt_objects.h mrt_parsing.h mrt_render.h mrt.h)

$(SRC_DIR)/%.o:	$(SRC_DIR)/%.c $(DEPS)
				$(CC) $(CFLAGS) -I$(INC) -I$(LIBMLX_DIR) -I$(LIBFT_INC_DIR) -c $< -o $@

# ----------------------------------- RULES ------------------------------------ #
RM				= rm -f
NAME			= rt

all:			libft mlx $(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(UTILS_FLAGS) -L$(LIBMLX_DIR) $(MLX_FLAGS) -o $@

libft:
				$(MAKE) -C $(LIBFT_DIR)

mlx:
				$(MAKE) -C $(LIBMLX_DIR)

clean:
				$(MAKE) -C $(LIBFT_DIR) clean
				$(MAKE) -C $(LIBMLX_DIR) clean
				$(RM) -r $(OBJS)

fclean:
				$(MAKE) -C $(LIBFT_DIR) fclean
				$(MAKE) -C $(LIBMLX_DIR) fclean
				$(RM) -r $(OBJS)
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all libft mlx bonus clean fclean re
