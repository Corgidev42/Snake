/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 01:48:52 by marvin            #+#    #+#             */
/*   Updated: 2024/12/09 18:13:17 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_u(t_format *format, unsigned int nb)
{
	char	*res;
	int		count;

	res = ft_litoa(nb);
	if (nb == 0 && format->precision == 0)
		res[0] = '\0';
	res = formatted_number_precision(res, format->precision, 0, 0);
	if (format->width > (int)ft_strlen(res))
		res = formatted_width_minus_zero(
				res, format->width, format->flag_minus, format->flag_zero);
	count = ft_putstr_size(res);
	return (free(res), count);
}

int	print_x(t_format *format, unsigned long nb, int is_upper)
{
	char	*res;
	char	*temp;
	int		count;

	if (!nb && format->precision == 0)
		res = ft_strdup("");
	else if (is_upper)
		res = convert_to_hexa(nb, "0123456789ABCDEF");
	else
		res = convert_to_hexa(nb, "0123456789abcdef");
	res = formatted_number_precision(res, format->precision, 0, 0);
	if (nb && format->flag_hash)
	{
		temp = res;
		if (is_upper)
			res = ft_strjoin("0X", res);
		else
			res = ft_strjoin("0x", res);
		free(temp);
	}
	res = formatted_width_minus_zero(
			res, format->width, format->flag_minus, format->flag_zero);
	count = ft_putstr_size(res);
	return (free(res), count);
}

int	print_p(t_format *format, void *ptr)
{
	char				*res;
	char				*temp;
	unsigned long long	tmp;
	int					count;

	if (!ptr)
		res = ft_strdup("(nil)");
	else
	{
		tmp = (unsigned long long)ptr;
		res = convert_to_hexa(tmp, "0123456789abcdef");
		temp = res;
		res = ft_strjoin("0x", res);
		free(temp);
	}
	res = formatted_width_minus_zero(res, format->width, format->flag_minus, 0);
	count = ft_putstr_size(res);
	return (free(res), count);
}
