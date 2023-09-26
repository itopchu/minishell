# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: itopchu <itopchu@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/13 18:28:06 by itopchu       #+#    #+#                  #
#    Updated: 2023/01/13 18:28:06 by itopchu       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= libft
HEADER	= ../header/
ARCHIVE_NAME = $(NAME).a
# **************************************************************************** #
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
COMPILE = $(CC) $(CFLAGS) -I $(HEADER)
RM		= rm -rf
# **************************************************************************** #
AR		= ar
ARFLAGS	= -rcs
ARCHIVE	= $(AR) $(ARFLAGS)
# **************************************************************************** #
DIR_OBJ	= ../../obj/
# **************************************************************************** #
SRC 	=	ft_atoi.c \
			ft_bzero.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strndup.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_split.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_free2m.c
# **************************************************************************** #
OBJ		= $(SRC:%.c=$(DIR_OBJ)%.o)
# **************************************************************************** #
$(DIR_OBJ)%.o: %.c $(HEADER)
	@$(COMPILE) -o $@ -c $<

$(ARCHIVE_NAME): $(OBJ)
	@$(ARCHIVE) $(ARCHIVE_NAME) $(OBJ)
	@echo "\033[33m$(NAME) is compiled.\033[0m"
# **************************************************************************** #
all: $(ARCHIVE_NAME)

fclean:
	@$(RM) $(ARCHIVE_NAME)

re: fclean all

.PHONY: clean all fclean re