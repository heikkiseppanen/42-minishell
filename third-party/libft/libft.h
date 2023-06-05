/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:04:10 by hseppane          #+#    #+#             */
/*   Updated: 2023/06/05 11:34:35 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "include/ft/buf.h"
# include "include/ft/htable.h"

# include <stdlib.h> // size_t, malloc(), free()
# include <unistd.h> // write()

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// LIST

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

int		ft_lstsize(t_list *lst);

// C TYPE

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);

int		ft_toupper(int c);
int		ft_tolower(int c);

// STRING

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *str, int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

int		ft_strflds(char const *str, const char delim);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);

char	**ft_split(char const *s, char c);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	*ft_strarr_del(char **arr);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

size_t	ft_toklen(const char *str, char delim);

// MEMORY

void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

// IO

char	*get_next_line(int fd);

int		ft_fprintf(int fd, const char *str, ...);
int		ft_printf(const char *str, ...);

int		ft_put_u64_base_fd(unsigned long long nb, int base, char *set, int fd);
int		ft_put_i64_base_fd(long long nb, int base, char *set, int fd);

int		ft_puthex_upper_u64_fd(unsigned long long nb, int fd);
int		ft_puthex_upper_u64(unsigned long long nb);
int		ft_puthex_lower_u64_fd(unsigned long long nb, int fd);
int		ft_puthex_lower_u64(unsigned long long nb);

int		ft_putdec_u64_fd(unsigned long long nb, int fd);
int		ft_putdec_u64(unsigned long long nb);
int		ft_putdec_i64_fd(long long nb, int fd);
int		ft_putdec_i64(long long nb);

int		ft_putptr_fd(void *ptr, int fd);
int		ft_putptr(void *ptr);

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(const char *c, int fd);
int		ft_putendl_fd(const char *c, int fd);
int		ft_putnbr_fd(int n, int fd);

#endif
