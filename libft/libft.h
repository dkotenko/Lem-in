/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:31:52 by edrowzee          #+#    #+#             */
/*   Updated: 2020/02/13 20:50:55 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "ft_printf.h"
# include "libft_compat.h"

# define BUFF_SIZE 100
# ifndef REAL_FLOAT
#  define REAL_FLOAT 0
# endif

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef	struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

int					ft_atoi(const char *str);
void				ft_bzero(void *destination, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memccpy(void *dest, const void *src,
		int c, size_t count);
void				*ft_memchr(const void *buffer, int c, size_t count);
int					ft_memcmp(const void *buffer1,
		const void *buffer2, size_t count);
void				*ft_memmove(void *dest, const void *src, size_t count);
void				*ft_memset(void *destination, int c, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putendl(char const *s);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
size_t				ft_putstr_fd(char const *s, int fd);
void				ft_putstr(char *str);
char				*ft_strcat(char *str_destination, const char *str_source);
char				*ft_strchr(const char *str, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t i);
char				*ft_strcpy(char *str_destination, const char *str_source);
void				ft_strdel(char **as);
char				*ft_strdup(const char *src);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *str_destination,
		const char *str_source, size_t count);
size_t				ft_strlen(const char *str);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *str_destination,
		const char *str_source, size_t count);
char				*ft_strncpy(char *str_destination, const char *str_source,
					size_t count);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *str, const char *str_search,
		size_t count);
char				*ft_strrchr(const char *str, int c);
char				*ft_strstr(const char *str, const char *str_search);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_itoa(long long int a);
int					ft_atoi(const char *str);
char				**ft_strsplit(char const *s, char c);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list*elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_btree_apply_infix(t_btree *root, void (*applyf)(void *));
void				ft_btree_apply_prefix(t_btree *root,
	void (*applyf)(void *));
void				ft_btree_apply_suffix(t_btree *root,
	void (*applyf)(void *));
t_btree				*ft_btree_create_node(void *item);
void				ft_btree_insert_data(t_btree **root, void *item,
		int (*cmpf)(void *, void *));
int					get_next_line(const int fd, char **line);
char				*ft_ultoa_buf(char *s, ULONG n, UINT base);
char				*ft_itoa_buf(char *s, long long int n, UINT base);
char				*ft_ftoa_buf(char *s, long double n, int decimals);
char				*ft_toupper_inplace(char *s);
char				*ft_strrev(char *str);
void				*ft_memrev(void *str, size_t len);
unsigned char		ft_bitrev(unsigned char b);
void				ft_swap(void **a, void **b);
void				ft_swap_int(int *a, int *b);
void				ft_swap_char(char *a, char *b);
void				ft_swap_double(double *a, double *b);
ULLONG				ft_ullpow(ULLONG a, ULLONG b);
UINT				ft_count_int_digits(long long int n, UINT base);
int					ft_printf(const char *format, ...);
int					ft_printf_ap(int fd, const char *format, va_list ap);
int					ft_fprintf(int fd, const char *format, ...);
char				*ft_ultoa_buf(char *s, ULONG n, UINT base);
ULLONG				ft_ullpow(ULLONG a, ULLONG b);

#endif
