NAME		= minishell
# **************************************************************************** #
DIR_LIB		= ./lib
DIR_OBJ		= ./obj
# **************************************************************************** #
CC			:= gcc
IFLAGS		:= -Iinc -Iinc/executor -Iinc/env_tools -I$(DIR_LIB)/src/header
CFLAGS		= -Wall -Wextra -Werror
CFLAGS		= -MMD -MP
CFLAGS		+= -g3 #-fsanitize=address
# CFLAGS		+= -arch x86_64
LFLAGS		:= -L$(DIR_LIB) -lreadline
RM			= rm -rf
# **************************************************************************** #
ifeq ($(shell uname -s),Darwin)			# Mac
	IFLAGS := $(IFLAGS) -I$(shell brew --prefix readline)/include
	LFLAGS := $(LFLAGS) -L$(shell brew --prefix readline)/lib
endif

COMPILE		:= $(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LFLAGS)
# **************************************************************************** #
SRC_EXEC	= executor/builtins/cd.c \
			  executor/builtins/echo.c \
			  executor/builtins/env.c \
			  executor/builtins/exit.c \
			  executor/builtins/export.c \
			  executor/builtins/pwd.c \
			  executor/builtins/unset.c \
			  executor/exec/exec_helper.c \
			  executor/exec/exec.c \
			  executor/executable/executable.c \
			  executor/path/get_cd_path.c \
			  executor/path/get_exec_path.c \
			  executor/path/get_path_path.c \
			  executor/path/helper_path.c \
			  executor/redirect/here_doc.c \
			  executor/redirect/open_files.c \
			  executor/redirect/redirections.c \
			  executor/tools/do_free.c \
			  executor/tools/do_uatoi.c \
			  executor/tools/error_hand.c \
			  executor/tools/signal.c \
			  executor/tools/var.c \
			  main.c

SRC_ENV		= env_tools/init_clean/command_clean.c \
			  env_tools/init_clean/env_clean.c \
			  env_tools/init_clean/env_init.c \
			  env_tools/make_envp.c

SRC_GL		= command_line_handler/gl/helpers.c \
			  command_line_handler/gl/parcer_processor.c \
			  command_line_handler/gl/quotes.c \
			  command_line_handler/gl/stage1.c \
			  command_line_handler/gl/stage2.c \
			  command_line_handler/gl/stage3.c \
			  command_line_handler/gl/stage4.c \
			  command_line_handler/gl/vars.c \
			  command_line_handler/gl/vars2.c \
			  command_line_handler/gl/vars3.c \
			  command_line_handler/gl/vars4.c

SRC_CLH		= command_line_handler/commands_build.c \
			  command_line_handler/commands_build2.c \
			  command_line_handler/check_commands.c \
			  command_line_handler/envp_keeper.c \
			  command_line_handler/readline_loop.c \
			  command_line_handler/file.c \
			  command_line_handler/file2.c \
			  command_line_handler/file3.c
# **************************************************************************** #
SRCS		= $(SRC_EXEC) $(SRC_GL) $(SRC_CLH) $(SRC_ENV)
OBJS		= $(patsubst %.c,$(DIR_OBJ)/%.o,$(SRCS))
# **************************************************************************** #
DEPS       = $(OBJS:.o=.d)
# **************************************************************************** #
all: $(NAME)

run: all
	@clear
	@./$(NAME)

rungrid: all
	@clear
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(NAME)

runregrid: re
	@clear
	@valgrind --tool=memcheck --leak-check=full ./$(NAME)

$(DIR_LIB)/lib.a:
	@echo "\033[K\r\033[32m$(NAME) is compiled.\033[0m"
	@echo "42 lib is compiling"
	@$(MAKE) -s -C $(DIR_LIB)

$(NAME): $(OBJS) $(DIR_LIB)/lib.a
	@$(COMPILE) $^ -o $(NAME) $(LFLAGS)
	@echo "\r\033[K\033[32m$(NAME) \033[0mis created."

$(DIR_OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d) -MT $@
	@echo "$< \033[32mcompiled.\033[0m"

-include $(DEPS)

clean:
	@$(RM) $(DIR_OBJ)
	@$(MAKE) -s -C $(DIR_LIB) clean
	@echo "Object files are removed"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(DIR_LIB) fclean
	@echo "$(NAME) is removed"

re: fclean all

.PHONY: clean all fclean re