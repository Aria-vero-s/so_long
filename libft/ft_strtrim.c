/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:00:09 by asaulnie          #+#    #+#             */
/*   Updated: 2024/06/06 15:22:09 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const*s1, char const*set)
{
	size_t	start;
	size_t	end;
	char	*mid;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	end = ft_strlen(s1);
	while (ft_strrchr(set, s1[end - 1]) && end > start)
		end--;
	mid = malloc(sizeof(char) * (end - start + 1));
	if (!mid)
		return (NULL);
	i = 0;
	while (&s1[start] != &s1[end])
	{
		mid[i] = s1[start];
		start++;
		i++;
	}
	mid[i] = '\0';
	return (mid);
}
