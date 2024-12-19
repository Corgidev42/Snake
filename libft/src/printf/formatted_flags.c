/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatted_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 02:29:09 by marvin            #+#    #+#             */
/*   Updated: 2024/12/09 18:09:39 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*formatted_width_minus_zero(
	char *str, int width, int has_minus, int has_zero)
{
	char	*ptr;
	char	*res;
	int		len;

	len = (int)ft_strlen(str);
	if (width == 0 || len > width)
	{
		res = ft_strdup(str);
		return (free(str), res);
	}
	ptr = malloc(sizeof(char) * (width - len + 1));
	if (has_minus || !has_zero)
		ptr = ft_memset(ptr, ' ', (width - len + 1));
	else
		ptr = ft_memset(ptr, '0', (width - len + 1));
	ptr[width - len] = '\0';
	if (has_minus)
		res = ft_strjoin(str, ptr);
	else
		res = ft_strjoin(ptr, str);
	return (free(str), free(ptr), res);
}

char	*formatted_number_precision(
	char *str, int precision, int has_plus, int has_space)
{
	char	*ptr;
	char	*res;
	int		len;
	int		formatted_len;

	len = (int)ft_strlen(str) - (*str == '-');
	if (precision != -1 && len < precision)
		formatted_len = precision - len
			+ (*str == '-' || (has_plus || has_space));
	else if (precision == -1)
		formatted_len = (*str == '-' || (has_plus || has_space));
	else
		formatted_len = (has_plus || has_space);
	ptr = malloc(sizeof(char) * (formatted_len + 1));
	ptr = ft_memset(ptr, '0', (formatted_len + 1));
	ptr[formatted_len] = '\0';
	if (*str == '-')
		ptr[0] = '-';
	else if (has_plus)
		ptr[0] = '+';
	else if (has_space)
		ptr[0] = ' ';
	res = ft_strjoin(ptr, &str[(*str == '-')]);
	return (free(str), free(ptr), res);
}
