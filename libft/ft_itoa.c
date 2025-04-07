/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:37:45 by amert             #+#    #+#             */
/*   Updated: 2024/11/15 00:40:30 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	k_digitcount(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	k_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static char	*k_rev(char *str)
{
	size_t	i;
	size_t	len;
	char	temp;

	i = 0;
	len = ft_strlen(str);
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*num;
	size_t	len;
	int		sign;

	sign = (n < 0);
	num = (char *)malloc(sizeof(char) * (k_digitcount(n) + (size_t)sign + 1));
	if (!num)
		return (NULL);
	len = 0;
	if (n == 0)
		num[len++] = '0';
	while (n != 0)
	{
		num[len++] = k_abs(n % 10) + '0';
		n /= 10;
	}
	if (sign)
		num[len++] = '-';
	num[len] = '\0';
	return (k_rev(num));
}
