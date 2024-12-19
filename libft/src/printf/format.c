/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:39:22 by ezeppa            #+#    #+#             */
/*   Updated: 2024/11/29 00:27:25 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	add_flags(t_format *format, const char *ptr)
{
	int	i;

	i = 0;
	while (TRUE)
	{
		if (ptr[i] == FLAG_MINUS)
			format->flag_minus = TRUE;
		else if (ptr[i] == FLAG_PLUS)
			format->flag_plus = TRUE;
		else if (ptr[i] == FLAG_SPACE)
			format->flag_space = TRUE;
		else if (ptr[i] == FLAG_HASH)
			format->flag_hash = TRUE;
		else if (ptr[i] == FLAG_ZERO)
			format->flag_zero = TRUE;
		else
			return (i);
		i++;
	}
	return (i);
}

static int	add_width(t_format *format, const char *ptr)
{
	int	nb;
	int	count;

	nb = ft_atoi(ptr);
	if (!nb && *ptr != '0')
		return (0);
	format->width = nb;
	count = 0;
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

static int	add_precision(t_format *format, const char *ptr)
{
	int	nb;
	int	count;

	if (*ptr != '.')
		return (0);
	ptr++;
	count = 1;
	while (*ptr == '0')
	{
		ptr++;
		count++;
	}
	nb = ft_atoi(ptr);
	format->precision = nb;
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

static int	add_specifier(t_format *format, const char *ptr)
{
	if (*ptr != 'c'
		&& *ptr != 's'
		&& *ptr != 'p'
		&& *ptr != 'd'
		&& *ptr != 'i'
		&& *ptr != 'u'
		&& *ptr != 'x'
		&& *ptr != 'X'
		&& *ptr != '%')
		return (0);
	format->specifier = *ptr;
	return (1);
}

t_format	*init_format(const char **ptr)
{
	t_format	*format;

	format = malloc(sizeof(t_format));
	if (!format)
		return (NULL);
	format->flag_minus = FALSE;
	format->flag_plus = FALSE;
	format->flag_space = FALSE;
	format->flag_hash = FALSE;
	format->flag_zero = FALSE;
	format->width = FALSE;
	format->precision = -1;
	format->specifier = 0;
	*ptr += add_flags(format, *ptr);
	*ptr += add_width(format, *ptr);
	*ptr += add_precision(format, *ptr);
	*ptr += add_specifier(format, *ptr);
	return (format);
}
