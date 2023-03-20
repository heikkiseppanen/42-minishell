NAME := libft.a

SRCDIR := ./src
OBJDIR := ./obj
INCDIR := ./include

SRC :=\
ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_isspace.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_striteri.c \
ft_strmapi.c \
ft_strchr.c \
ft_strdup.c \
ft_strndup.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strncmp.c \
ft_strflds.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strarr_del.c\
ft_strtrim.c \
ft_substr.c \
ft_toklen.c \
ft_tolower.c \
ft_toupper.c \
ft_lstnew_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstsize_bonus.c \
ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c \
ft_lstclear_bonus.c \
ft_lstiter_bonus.c \
ft_lstmap_bonus.c \
\
buf.c \
get_next_line.c \
\
ft_printf.c \
ft_putbase.c \
ft_puthex.c \
ft_putdec.c \
ft_putptr.c \
ft_write_str.c \
ft_write_char.c \

OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
DEP := $(OBJ:%.o=.d)

CC := cc
CFLAGS := -O3 -I./ -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rus $(NAME) $(OBJ)

# Include dependency info
-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c  
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	$(CC) $(CFLAGS) -MMD -c $< -o $@ 

clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all so clean fclean re bonus
