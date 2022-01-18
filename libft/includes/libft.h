/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:24:16 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/13 18:21:40 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "ft_printf.h"
# include "get_next_line.h"

int					ft_retfree(char **s, int ret);
void				ft_tabfree(char **tab);
int					ft_tablen(char **tab);

void				*ft_memset(void *b, int c, size_t len);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_bzero(void *s, size_t n);

size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t len);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);

char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strrev(char *s);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strddel(char ***ap);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoinf(char const *s1, char const *s2);
char				*ft_strnjoin(char const *s1, char const *s2, size_t n);

char				*ft_strjoint(char const *s1, char const *s2,
						char const *s3);

char				*ft_strjointf(char const *s1, char const *s2,
						char const *s3);

char				*ft_strfnjoin(char const *s1, char const *s2,
						size_t n, char const *f);
char				**ft_strsplit(char const *s, char c);
int					ft_strisalnum(char *str);
int					ft_strisdigit(char *str);
int					ft_strisascii(char *str);
char				*ft_insert_str(char *str, char *insert, int index);
char				*ft_strdelpart(char *str, int i, int len);
char				*ft_stradd(char *s1, char s2);
int					ft_strnncmp(char *dest, char *src, int start, int end);

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
int					ft_islower(int c);
char				*ft_strlower(char *str);
int					ft_isupper(int c);
char				*ft_strupper(char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isspace(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isnumeric(char *str);

int					ft_putchar(int c);
int					ft_putchar_err(int c);
void				ft_putstr(char const *s);
void				ft_putnstr(char const *s, size_t n);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnstr_fd(char const *s, size_t n, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

void				ft_putstrtable(char **tb);
char				*ft_strfdup(const char *s1, const char *f);
char				*ft_strfjoin(char const *s1, char const *s2, char const *f);
char				*ft_strpathfile(const char *s1, const char *s2);
void				ft_multifree(char **s1, char **s2, char **s3);
char				*ft_strcut(char *str, size_t beg, size_t end);
char				*ft_strfcut(char *str, size_t beg, size_t end);

#endif
