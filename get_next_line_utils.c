/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:17:21 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/12 17:26:08 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (-1);
	if (c == '\0')
		return (ft_strlen(s) + 1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	*ft_memcpy(void *dest, void *src, int n)
{
	char	*new_dest;
	char	*new_src;
	int		i;

	new_dest = (char *)dest;
	new_src = (char *)src;
	i = 0;
	while (i < n)
	{
		*(new_dest + i) = *(new_src + i);
		i++;
	}
	return (dest);
}

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}
