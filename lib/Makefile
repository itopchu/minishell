# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: itopchu <itopchu@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/21 17:19:12 by itopchu       #+#    #+#                  #
#    Updated: 2023/01/21 17:19:12 by itopchu       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= lib
HEADER	= src/header
ARCHIVE_NAME = $(NAME).a
####################################
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
COMPILE = $(CC) $(CFLAGS) -I $(HEADER)
RM		= rm -rf
####################################
AR		= ar
ARFLAGS	= -rcs
ARCHIVE	= $(AR) $(ARFLAGS)
# **************************************************************************** #
DIR_OBJ	= obj/
# **************************************************************************** #
OBJ_O	=	base_conv.o \
			based_int.o \
			ft_printf.o \
			hex.o \
			write.o \
			get_next_line_utils.o \
			get_next_line.o \
			ft_atoi.o \
			ft_bzero.o \
			ft_isalpha.o \
			ft_isalnum.o \
			ft_isascii.o \
			ft_isdigit.o \
			ft_isprint.o \
			ft_memchr.o \
			ft_memcmp.o \
			ft_memcpy.o \
			ft_memmove.o \
			ft_memset.o \
			ft_strchr.o \
			ft_strcmp.o \
			ft_strlcat.o \
			ft_strlcpy.o \
			ft_strlen.o \
			ft_strncmp.o \
			ft_strndup.o \
			ft_strnstr.o \
			ft_strrchr.o \
			ft_tolower.o \
			ft_toupper.o \
			ft_calloc.o \
			ft_strdup.o \
			ft_substr.o \
			ft_strjoin.o \
			ft_strtrim.o \
			ft_itoa.o \
			ft_strmapi.o \
			ft_striteri.o \
			ft_putchar_fd.o \
			ft_putstr_fd.o \
			ft_putendl_fd.o \
			ft_putnbr_fd.o \
			ft_split.o \
			ft_lstnew.o \
			ft_lstadd_front.o \
			ft_lstsize.o \
			ft_lstlast.o \
			ft_lstadd_back.o \
			ft_lstdelone.o \
			ft_lstclear.o \
			ft_lstiter.o \
			ft_lstmap.o \
			ft_free2m.o
# **************************************************************************** #
OBJ		= $(OBJ_O:%.o=$(DIR_OBJ)%.o)
# **************************************************************************** #
DIR_NXT	= src/get_next_line/
DIR_LIB	= src/libft/
DIR_PRN	= src/printf/
# **************************************************************************** #
$(ARCHIVE_NAME): $(HEADER) libs
	@$(ARCHIVE) $(ARCHIVE_NAME) $(OBJ);
	@echo "\033[94m$(NAME) is archived.\033[0m"
# **************************************************************************** #
all		: $(ARCHIVE_NAME)

libs	:
	@mkdir -p $(DIR_OBJ)
	@$(MAKE) -s -C $(DIR_NXT)
	@$(MAKE) -s -C $(DIR_LIB)
	@$(MAKE) -s -C $(DIR_PRN)

clean	:
	@$(RM) $(DIR_OBJ)

fclean	: clean
	@$(MAKE) -s -C $(DIR_NXT) fclean
	@$(MAKE) -s -C $(DIR_LIB) fclean
	@$(MAKE) -s -C $(DIR_PRN) fclean
	@$(RM) $(ARCHIVE_NAME)
	@echo "$(ARCHIVE_NAME) is removed"

re		: fclean all

.PHONY	: clean all fclean re