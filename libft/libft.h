/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamekiller2111 <gamekiller2111@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:37:53 by pgaspar           #+#    #+#             */
/*   Updated: 2024/12/05 21:07:15 by gamekiller2      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct o_node
{
	int				value;
	struct o_node	*prev;
	struct o_node	*next;
}					t_node;

t_node				*ft_lstdoublynew(int value);

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *ptr, int value, size_t num);
void				*ft_memchr(const void *ptr, int c, size_t n);
void				*ft_calloc(size_t num_elements, size_t element_size);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char s, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_unsigned(unsigned int n, int *c);
void				ft_putchar(char c, int *i);
void				ft_putstr(char *str, int *c);
void				ft_putnbr(int nb, int *i);
void				free_matrix(char **s);
void				print_pointer(void *p, int *c);
void				int_to_hex_lower(unsigned int i, int *c);
void				int_to_hex_upper(unsigned int i, int *c);
int					ft_printf(const char *p, ...);
int					ft_lstsize(t_list *lst);
int					ft_isspace(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_atoi_base(const char *str, int str_base);
int					ft_atoi(const char *str);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t n);
int					get_strlen(char *s);
char				*ft_itoa(int i);
char				*ft_strchr(const char *str, int c);
char				**ft_split(const char *s, char c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnstr(const char *h, const char *nd, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strdup(const char *str);
char				*get_next_line(int fd);
char				*get_strchr(const char *s, int c);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
long long			ft_atol(const char *nptr);

#endif
