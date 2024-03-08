# -------------------------------- DIRECTORIES --------------------------------- #
INC_MAIN_DIR	= include/main
INC_BONUS_DIR	= include/bonus

SRC_MAIN_DIR	= src/main
SRC_BONUS_DIR	= src/bonus

OBJECT_FILE_DIR	= obj

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
CFLAGS			= -Wall -Wextra -Werror -O3

UTILS_FLAGS		= -lm -Llib -lft
ifdef BONUS
	UTILS_FLAGS	+= -lpthread
endif

ifeq ($(shell uname), Linux)
	MLX_FLAGS	= -lmlx -lXext -lX11
else
	MLX_FLAGS	= -lmlx -framework openGL -framework AppKit
endif

# ----------------------------------- FILES ------------------------------------ #
SRCS			= $(addprefix $(SRC_MAIN_DIR)/, \
					mrt_errors.c \
					mrt.c \
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
					mrt_mlx_event.c \
					mrt_mlx_image.c \
					mrt_mlx.c) \
				$(addprefix $(OBJ_DIR)/, \
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
					mrt_ray.c \
					mrt_raytracing.c \
					mrt_render.c))

OBJS_MAIN		= $(SRCS:.c=.o)

SRCS_BONUS		= $(addprefix $(SRC_BONUS_DIR)/, \
					mrt_bonus.c \
					mrt_errors_bonus.c \
				$(addprefix $(MTH_DIR)/, \
					mrt_geometry_utils_bonus.c \
					mrt_mat3x3_inv_bonus.c \
					mrt_mat3x3_op_bonus.c \
					mrt_mat4x4_apply_bonus.c \
					mrt_mat4x4_inv_bonus.c \
					mrt_mat4x4_op_bonus.c \
					mrt_vec3_op1_bonus.c \
					mrt_vec3_op2_bonus.c) \
				$(addprefix $(MLX_DIR)/, \
					mrt_mlx_bonus.c \
					mrt_mlx_event_bonus.c \
					mrt_mlx_image_bonus.c) \
				$(addprefix $(OBJ_DIR)/, \
					mrt_checker_bonus.c \
					mrt_cone_bonus.c \
					mrt_cylinder_bonus.c \
					mrt_plane_bonus.c \
					mrt_sphere_bonus.c \
					mrt_objects_bonus.c) \
				$(addprefix $(PRS_DIR)/, \
					mrt_get_data1_bonus.c \
					mrt_get_data2_bonus.c \
					mrt_parse_obj_bonus.c \
					mrt_parse_param_bonus.c \
					mrt_parsing_bonus.c \
					mrt_scene_get_bonus.c \
					mrt_scene_read_bonus.c \
					mrt_set_cam_bonus.c \
					mrt_set_obj_bonus.c) \
				$(addprefix $(RTC_DIR)/, \
					mrt_color_bonus.c \
					mrt_intensity_bonus.c \
					mrt_raytracing_bonus.c \
					mrt_ray_bonus.c \
					mrt_render_bonus.c \
					mrt_thread_bonus.c))

OBJS_BONUS		= $(SRCS_BONUS:.c=.o)

ifdef BONUS
	OBJS		= $(OBJS_BONUS)
else
	OBJS		= $(OBJS_MAIN)
endif

# -------------------------------- COMPILATION --------------------------------- #
DEPS_MAIN		= Makefile $(addprefix $(INC_MAIN_DIR)/, mrt_math.h mrt_error.h mrt_parsing.h mrt_render.h mrt.h)

DEPS_BONUS		= Makefile $(addprefix $(INC_BONUS_DIR)/, mrt_math_bonus.h mrt_error_bonus.h mrt_parsing_bonus.h mrt_render_bonus.h mrt_bonus.h)

$(SRC_MAIN_DIR)/%.o:	$(SRC_MAIN_DIR)/%.c $(DEPS_MAIN)
				$(CC) $(CFLAGS) -I$(INC_MAIN_DIR) -I$(LIBMLX_DIR) -I$(LIBFT_INC_DIR) -c $< -o $@

$(SRC_BONUS_DIR)/%.o:	$(SRC_BONUS_DIR)/%.c $(DEPS_BONUS)
				$(CC) $(CFLAGS) -I$(INC_BONUS_DIR) -I$(LIBMLX_DIR) -I$(LIBFT_INC_DIR) -c $< -o $@

# ----------------------------------- RULES ------------------------------------ #
RM				= rm -f
NAME			= miniRT

all:			libft mlx $(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(UTILS_FLAGS) -L$(LIBMLX_DIR) $(MLX_FLAGS) -o $@

libft:
				$(MAKE) -C $(LIBFT_DIR)

mlx:
				$(MAKE) -C $(LIBMLX_DIR)

bonus:
				$(MAKE) BONUS=1 all

clean:
				$(MAKE) -C $(LIBFT_DIR) clean
				$(MAKE) -C $(LIBMLX_DIR) clean
				$(RM) -r $(OBJS_MAIN) $(OBJS_BONUS)

fclean:
				$(MAKE) -C $(LIBFT_DIR) fclean
				$(MAKE) -C $(LIBMLX_DIR) fclean
				$(RM) -r $(OBJS_MAIN) $(OBJS_BONUS)
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all libft mlx bonus clean fclean re
