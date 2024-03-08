# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 15:31:20 by yobouhle          #+#    #+#              #
#    Updated: 2024/03/01 13:45:45 by hanmpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR			= src
OBJS_DIR			= obj
INC_DIR				= include
BIN_DIR				= ..

SRCS				= $(addprefix $(SRCS_DIR)/, c_arraylen.c c_atod.c \
					c_free_void_array.c c_iscomma.c c_strisdigit.c \
					c_isdouble.c c_isnl.c c_isspace.c c_readfd.c \
					c_split_func.c c_strcmp.c ft_atoi.c ft_bzero.c ft_calloc.c \
					ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
					ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
					ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
					ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
					ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
					ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
					ft_tolower.c ft_toupper.c)

SRCS_BONUS			= $(addprefix $(SRCS_DIR)/, ft_lstadd_back.c \
					ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
					ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
					ft_lstsize.c)

OBJS				= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

OBJS_BONUS			= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS_BONUS:.c=.o)))

ifdef WITH_BONUS
	OBJS_TOT		= $(OBJS) $(OBJS_BONUS)
else
	OBJS_TOT		= $(OBJS)
endif

DEPS				= Makefile $(INC_DIR)/libft.h

$(OBJS_DIR)/%.o: 	$(SRCS_DIR)/%.c $(DEPS)
					@mkdir -p $(OBJS_DIR)
					$(CC) $(CFLAGS) -c $< -o $@

CC					= cc

RM					= rm -f

CFLAGS				= -Wall -Wextra -Werror -I$(INC_DIR)

NAME				= libft.a

all:				$(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(OBJS_TOT)
					ar rc $@ $(OBJS_TOT)

bonus:
					@${MAKE} WITH_BONUS=1

clean:
					$(RM) -r $(OBJS_DIR)

fclean:				clean
					$(RM) $(BIN_DIR)/$(NAME)

re:					fclean all

.PHONY:				all bonus clean fclean re