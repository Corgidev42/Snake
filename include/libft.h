/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:07:52 by ezeppa            #+#    #+#             */
/*   Updated: 2024/11/13 17:28:15 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

// Character type functions
int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_isalnum(int c);
int	ft_isascii(int c);
int	ft_isprint(int c);
int	ft_toupper(int c);
int	ft_tolower(int c);

// String functions
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnchr(const char *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

// Number functions
long	long_size(long n);

// Conversion functions
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
char	*ft_litoa(long n);

// Memory functions
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t new_size);

// Input/Output functions
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// Printf functions
// Boolean
# define FALSE 0
# define TRUE 1

// Flags
# define FLAG_MINUS '-'
# define FLAG_PLUS '+'
# define FLAG_SPACE ' '
# define FLAG_HASH '#'
# define FLAG_ZERO '0'

typedef struct s_format
{
	int		flag_minus;
	int		flag_plus;
	int		flag_space;
	int		flag_hash;
	int		flag_zero;
	int		width;
	int		precision;
	char	specifier;
}	t_format;

int			ft_printf(const char *format, ...);

t_format	*init_format(const char **ptr);

int		ft_putchar_size(char c);
int		ft_putstr_size(char *str);
char	*convert_to_hexa(unsigned long long nb, char *base);

int			print_c(t_format *format, char c);
int			print_s(t_format *format, char *str);
int			print_p(t_format *format, void *ptr);
int			print_d_i(t_format *format, int nb);
int			print_u(t_format *format, unsigned int nb);
int			print_x(t_format *format, unsigned long nb, int is_upper);

char		*formatted_width_minus_zero(
				char *str, int width, int has_minus, int has_zero);
char		*formatted_number_precision(
				char *str, int precision, int has_plus, int has_space);

#endif
