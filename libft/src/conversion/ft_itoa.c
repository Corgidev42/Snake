/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:24:27 by ezeppa            #+#    #+#             */
/*   Updated: 2024/11/13 19:23:32 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	int_size(int n)
{
	int		len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_recursive(char *s, int n, int i)
{
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	if (n > 9)
	{
		ft_recursive(s, n / 10, i - 1);
		s[i] = (n % 10) + '0';
	}
	else
		s[i] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*ptr;

	if (n == -2147483648)
	{
		ptr = malloc(sizeof(char) * 12);
		if (!ptr)
			return (ptr);
		ft_strlcpy(ptr, "-2147483648", 12);
		return (ptr);
	}
	ptr = malloc(sizeof(char) * (int_size(n) + 1));
	if (!ptr)
		return (NULL);
	ft_recursive(ptr, n, (int_size(n) - 1));
	ptr[int_size(n)] = '\0';
	return (ptr);
}
