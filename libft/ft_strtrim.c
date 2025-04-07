/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:39:44 by amert             #+#    #+#             */
/*   Updated: 2024/11/13 12:20:01 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;

	begin = 0;
	while (s1[begin] && ft_strchr(set, s1[begin]))
		begin++;
	if (!(s1[begin]))
		return (ft_strdup(""));
	end = ft_strlen(s1) -1;
	while (ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, begin, end - begin + 1));
}
