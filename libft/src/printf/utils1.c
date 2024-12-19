/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:56:32 by marvin            #+#    #+#             */
/*   Updated: 2024/12/09 17:49:41 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_size(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_size(char *str)
{
	write(1, str, ft_strlen(str));
	return (ft_strlen(str));
}

static int	hexa_size(unsigned long long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		nb = 1;
	while (nb > 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

char	*convert_to_hexa(unsigned long long nb, char *base)
{
	char	*res;
	int		size;

	size = hexa_size(nb);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	res[size] = '\0';
	while (size > 0)
	{
		size--;
		res[size] = base[(nb % 16)];
		nb /= 16;
	}
	return (res);
}
