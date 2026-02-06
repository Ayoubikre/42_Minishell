CC = cc

CFLAGS = -Wall -Werror -Wextra -I./readline/include
# CFLAGS = -fsanitize=address -g -Wall -Werror -Wextra -I./readline/include

RDFLAGS = -L./readline/lib -lreadline

headers  =	./include/main.h \
			./include/parse.h \
			./include/builtins.h \

PARSING  =	./main.c \
			./Parsing/parse.c \
			./Parsing/Tokenize/tokenize.c \
			./Parsing/Tokenize/set_token.c\
			./Parsing/Tokenize/validate_list.c \
			./Parsing/Tokenize/list.c \
			./Parsing/Exp/expand.c \
			./Parsing/Exp/swap_value.c \
			./Parsing/Exp/swap_utils.c \
			./Parsing/Exp/swap_utils2.c \
			./Parsing/Exp/fix_list.c \
			./Parsing/Exp/fix_cas_1.c \
			./Parsing/Exp/fix_cas_2.c \
			./Parsing/Exp/set_token.c \
			./Parsing/Exp/quotes.c \
			./Parsing/Exp/quotes2.c \
			./Parsing/Exp/filter_exp.c \
			./Parsing/Exp/utils.c \
			./Parsing/Wildcard/wildcard.c \
			./Parsing/Wildcard/get_wc_list.c \
			./Parsing/Wildcard/files_list.c \
			./Parsing/Wildcard/cmd_list.c \
			./Parsing/Wildcard/filter_list.c \
			./Parsing/Wildcard/fix_wc_list.c \
			./Parsing/Filter/filter_list.c  \
			./Parsing/Filter/filter_list2.c  \
			./Parsing/Utils/ft_split2.c \
			./Parsing/Utils/ft_split3.c \
			./Parsing/Utils/ft_split4.c \
			./Parsing/Utils/ft_split5.c \
			./Parsing/Utils/ft_strjoin4.c \
			./Parsing/Utils/utils1.c \
			./Parsing/Utils/utils2.c \

BUILTINS =	./execution/builtins/pwd.c \
			./execution/builtins/cd.c \
			./execution/builtins/echo.c \
			./execution/builtins/environment.c \
			./execution/builtins/exit.c \
			./execution/builtins/export.c \
			./execution/builtins/unset.c \
			./execution/builtins_utils/cd_utils.c \
			./execution/builtins_utils/cd_utils2.c \
			./execution/builtins_utils/export_utils.c \
			./execution/builtins_utils/export_utils2.c \
			./execution/builtins_utils/split_env.c \
			./execution/builtins_utils/env_utils.c \

EXEC = 		./execution/exec/execution.c \
			./execution/exec/exec_external.c \
			./execution/exec/exec_external_utils.c \
			./execution/exec/exec_external_utils2.c \
			./execution/exec/exec_single.c \
			./execution/exec/helpers.c \
			./execution/exec/redirection.c \
			./execution/exec/red_utils.c \
			./execution/exec/heredoc.c \
			./execution/exec/here_utils.c \
			./execution/exec/pipe.c \
			./execution/exec/pipe_utils.c \
			./execution/exec/pipe_utils2.c \
			./execution/signal/signals.c \
			./execution/signal/signals_utils.c \

EXECUTION = ${BUILTINS} \
			${EXEC} \


SRC =	${PARSING} \
		${EXECUTION} \

OBJC = $(SRC:%.c=%.o)

libft_DIR = ./42_Libft
libft = $(libft_DIR)/libft.a

NAME = ./minishell

#	Colors

RESET		= \033[0m
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m

# ASCII Art Display Functions
define show_banner
	@echo "$(GREEN)"
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "$(YELLOW)"
	@echo "                🌟 Minishell Bonus - With Wildcards! 🌟"
	@echo "$(PURPLE)                      Created by anktiri & aakritah$(RESET)"
	@echo ""
endef

all: $(NAME)

$(NAME): show_banner $(OBJC)
	@make -C $(libft_DIR)
	@echo "$(CYAN)🔗 Linking executable...$(RESET)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJC) -o $(NAME) $(libft) $(RDFLAGS)
	@echo "$(GREEN)✅ Minishell compiled successfully!$(RESET)"

show_banner:
	$(call show_banner)

%.o: %.c $(headers) $(libft_DIR)/libft.h
	@echo "$(CYAN)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@make -C $(libft_DIR) clean
	@rm -rf $(OBJC) 
	@echo "$(GREEN)✅ Clean completed!$(RESET)"

fclean: clean
	@echo "$(RED)🗑️  Full clean - removing executables...$(RESET)"
	@make -C $(libft_DIR) fclean
	@rm -rf $(NAME)
	@echo "$(GREEN)✅ Full clean completed!$(RESET)"

re: fclean all
	@echo "$(CYAN)🔄 Rebuild completed!$(RESET)"

.PHONY: all bonus clean fclean re show_banner 