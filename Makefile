# Meta

NAME := minishell

SRCDIR := ./src
OBJDIR := ./obj
INCDIR := $(SRCDIR)/include

AST_DIR := ast
AST_SRC :=\
	ast.c\

TOKENIZER_DIR := tokenizer
TOKENIZER_SRC :=\
	tokenizer.c\
	str_util.c\
	sym.c\
	token.c\

PARSER_DIR := parser
PARSER_SRC :=\
	unexpect.c\
	parse_pipeline.c\
	parse_command.c\
	parse_parameters.c\

INTERPRETER_DIR := interpreter
INTERPRETER_SRC :=\
	interpreter.c\
	pipeline.c\
	redirection.c\
	command.c\
	process.c\

IO_DIR := io
IO_SRC :=\
	pipe.c\
	redir.c\

EXP_DIR := expansion
EXP_SRC:=\
	arg_expand.c\
	dollar_expand.c\
	token_checks.c\

BUILTIN_DIR := builtins
BUILTIN_SRC:=\
	b_cd.c\
	b_echo.c\
	b_env.c\
	b_export.c\
	b_pwd.c\
	b_unset.c\

SRC :=\
	main.c\
	signal.c\
	$(AST_SRC:%=$(AST_DIR)/%)\
	$(TOKENIZER_SRC:%=$(TOKENIZER_DIR)/%)\
	$(PARSER_SRC:%=$(PARSER_DIR)/%)\
	$(INTERPRETER_SRC:%=$(INTERPRETER_DIR)/%)\
	$(IO_SRC:%=$(IO_DIR)/%)\
	$(EXP_SRC:%=$(EXP_DIR)/%)\
	$(BUILTIN_SRC:%=$(BUILTIN_DIR)/%)\

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
DEP := $(OBJ:%.o=%.d)

# Libft

FT_DIR := ./third-party/libft
FT_AR := $(FT_DIR)/libft.a
FT_LD := -L ./third-party/libft -lft

# Compilation 

CC := cc
INCLUDE := -I $(FT_DIR) -I $(INCDIR)
CFLAGS := -Wall -Werror -Wextra $(INCLUDE)
LDFLAGS := -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline -lhistory $(FT_LD)

# Rules

all: $(NAME) 

run: all
	./$(NAME)

debug: CFLAGS+= -g -fsanitize=address,undefined
debug: LDFLAGS+= -fsanitize=address,undefined
debug: $(NAME)

$(NAME): $(FT_AR) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

$(FT_AR):
	make -C $(FT_DIR)

-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c  
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	$(CC) $(CFLAGS) -MMD -c $< -o $@ 

clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make fclean -C $(FT_DIR)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all run debug clean fclean re
