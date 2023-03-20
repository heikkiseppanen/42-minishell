# Meta

NAME := minishell

SRCDIR := ./src
OBJDIR := ./obj

SRC :=\
main.c \

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
DEP := $(OBJ:%.o=%.d)

# Libft

FT_DIR := ./third-party/libft
FT_AR := $(FT_DIR)/libft.a
FT_LD := -L ./third-party/libft -lft

# Compilation 

CC := cc
INCLUDE := -I $(FT_DIR) -I $(SRCDIR)
CFLAGS := -Wall -Werror -Wextra $(INCLUDE)
LDFLAGS := -O3 -lreadline $(FT_LD)

# Rules

all: $(NAME) 

run: all
	./$(NAME)

debug: CFLAG+= -g -fsanitize=address
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
