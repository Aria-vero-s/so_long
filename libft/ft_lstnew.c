/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:17:04 by asaulnie          #+#    #+#             */
/*   Updated: 2024/06/07 14:20:49 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// new (liste?)
// var content
// retourner un nouveau bloc (node)
// la var next est a NULL

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
int main(void)
{
	int	a;

	a = 12;
	printf("%d\n", ft_lstnew(a));
	return (0);
}
*/
