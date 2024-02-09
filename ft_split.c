/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:13:45 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/09 13:47:57 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_bzero(void *s, int n)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (i < n)
	{
		*(p + i) = '\0';
		i++;
	}
}

void	*ft_calloc(int nmemb, int size)
{
	void	*p;

	p = (void *)malloc(nmemb * size);
	if (!p)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
	return (NULL);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*subs;
	int		i;

	if (start >= ft_strlen(s))
	{
		subs = ft_calloc(1, sizeof(char));
		if (!subs)
			return (NULL);
		return (subs);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	subs = (char *)malloc((len + 1) * sizeof(char));
	if (!subs)
		return ((void *)0);
	i = 0;
	while (i < len && s[start + i])
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

static int	ft_count_words(char *s, char c)
{
	int	words;
	int	flag;

	words = 0;
	flag = 0;
	while (*s)
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			words++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	if (words == 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	return (words);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		i;
	int		start;

	res = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!s || !res)
		return ((void *)0);
	i = 0;
	start = -1;
	while (i <= ft_strlen(s) && s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c)
		{
			start = (int)i;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (i - start > 0)
				*res++ = ft_substr(s, start, i - start);
		}
	}
	*res = (void *)0;
	return (res - ft_count_words(s, c));
}
