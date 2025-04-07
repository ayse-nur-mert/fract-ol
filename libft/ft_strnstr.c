/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:39:36 by amert             #+#    #+#             */
/*   Updated: 2024/11/13 12:19:57 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	needle_len;

	index = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	if (ft_strlen(haystack) < len)
		len = ft_strlen(haystack);
	while (index + needle_len <= len)
	{
		if (ft_strncmp(&haystack[index], needle, needle_len) == 0)
			return ((char *)&haystack[index]);
		index++;
	}
	return (NULL);
}
