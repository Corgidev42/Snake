/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezeppa <ezeppa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:36:07 by ezeppa            #+#    #+#             */
/*   Updated: 2024/11/13 19:23:32 by ezeppa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	len_word(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (len_word(s, c) > 0)
		{
			s += len_word(s, c);
			count++;
		}
		else
			break ;
	}
	return (count);
}

void	free_all(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	nb_words;
	size_t	i;

	nb_words = count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < nb_words)
	{
		while (*s == c)
			s++;
		strs[i] = ft_substr(s, 0, len_word(s, c));
		if (!strs[i])
			return (free_all(strs, i), NULL);
		s += len_word(s, c);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
