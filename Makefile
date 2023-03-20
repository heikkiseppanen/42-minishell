# Meta

NAME := minishell

SRCDIR := ./src
OBJDIR := ./obj

SRC :=\
main.c \

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
DEP := $(OBJ:%.o=%.d)

CC := cc
CFLAGS := -Wall -Werror -Wextra $(INCLUDE)
LDFLAGS := -O3

# Rules

all: $(NAME)

run: all
	./$(NAME)

debug: CFLAG+= -g -fsanitize=address
debug: LDFLAGS+= -fsanitize=address
debug: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

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
