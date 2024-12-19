/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:48:56 by marvin            #+#    #+#             */
/*   Updated: 2024/12/09 18:48:30 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_c(t_format *format, char c)
{
	int	count;

	count = 0;
	if (format->flag_minus)
		count += ft_putchar_size(c);
	if (format->width)
		while (count < format->width - (!format->flag_minus))
			count += ft_putchar_size(' ');
	if (!format->flag_minus)
		count += ft_putchar_size(c);
	return (count);
}

static char	*get_str_null_precision(char *str, int precision)
{
	char	*new_str;

	if (str)
		new_str = ft_strdup(str);
	else if (precision != -1 && precision < 6)
		new_str = ft_strdup("");
	else
		new_str = ft_strdup("(null)");
	return (new_str);
}

int	print_s(t_format *format, char *str)
{
	char	*res;
	int		count;
	int		size;

	str = get_str_null_precision(str, format->precision);
	if (format->precision == 0)
		size = 0;
	else if (format->precision != -1 && format->precision < (int)ft_strlen(str))
		size = format->precision;
	else
		size = ft_strlen(str);
	res = malloc(sizeof(char) * size + 1);
	ft_strlcpy(res, str, (size + 1));
	res = formatted_width_minus_zero(res, format->width, format->flag_minus, 0);
	count = ft_putstr_size(res);
	return (free(str), free(res), count);
}

static char	*str_int_precision(char *res, t_format *format, int nb)
{
	if (format->precision != -1
		&& format->precision > (int)ft_strlen(res) - (nb < 0))
	{
		res = formatted_number_precision(
				res, format->precision, format->flag_plus, format->flag_space);
		res = formatted_width_minus_zero(
				res, format->width, format->flag_minus, 0);
	}
	return (res);
}

int	print_d_i(t_format *format, int nb)
{
	char	*res;
	int		count;

	res = ft_itoa(nb);
	if (nb == 0 && format->precision == 0)
		res[0] = '\0';
	res = str_int_precision(res, format, nb);
	if (!(format->precision != -1
			&& format->precision > (int)ft_strlen(res) - (nb < 0)))
	{
		res = formatted_number_precision(
				res, -1, format->flag_plus, format->flag_space);
		if (format->flag_zero && nb < 0
			&& format->width > (int)ft_strlen(res))
		{
			res = formatted_width_minus_zero(res, format->width,
					format->flag_minus, format->flag_zero);
			res[0] = '-';
			res[format->width - long_size((long)nb)] = '0';
		}
		else
			res = formatted_width_minus_zero(
					res, format->width, format->flag_minus, format->flag_zero);
	}
	return (count = ft_putstr_size(res), free(res), count);
}
