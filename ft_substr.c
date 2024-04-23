/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:05:17 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/03/25 17:37:08 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*d;
	unsigned int	l;
	unsigned int	i;

	l = len;
	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s, 0) || l == 0)
		return (ft_strdup(""));
	if (start + l > ft_strlen(s, 0))
		l = ft_strlen(s, 0) - start;
	d = (char *)malloc(sizeof(char) * l + 1);
	if (!d)
		return (0);
	while (s[start] && i < l)
	{
		d[i] = s[start];
		i++;
		start++;
	}
	d[i] = '\0';
	return (d);
}
