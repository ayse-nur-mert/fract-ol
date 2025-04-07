/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:39:28 by amert             #+#    #+#             */
/*   Updated: 2024/11/13 12:19:51 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned int	index;

	ret = ft_strdup(s);
	if (ret && s && f)
	{
		index = 0;
		while (ret[index])
		{
			ret[index] = f(index, ret[index]);
			index++;
		}
	}
	return (ret);
}
