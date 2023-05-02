# Meta

NAME := minishell

SRCDIR := ./src
OBJDIR := ./obj
INCDIR := $(SRCDIR)/include

AST_DIR := ast
AST_SRC :=\
	ast.c\
	lexer.c\
	str_util.c\
	sym.c\
	token.c\

PARSER_DIR := parser
PARSER_SRC :=\
	unexpect.c\
	parse_pipeline.c\
	parse_command.c\
	parse_parameters.c\

SRC :=\
	main.c\
	signal.c\
	interpreter.c\
	redirection.c\
	pipe.c\
	$(AST_SRC:%=$(AST_DIR)/%)\
	$(PARSER_SRC:%=$(PARSER_DIR)/%)\

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
LDFLAGS := -O3 -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline -lhistory $(FT_LD)

# Rules

all: $(NAME) 

run: all
	./$(NAME)

debug: CFLAGS+= -g -fsanitize=address
debug: LDFLAGS+= -fsanitize=address
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
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all run debug clean fclean re
