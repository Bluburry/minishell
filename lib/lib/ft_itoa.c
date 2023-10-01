/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:31:10 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/01 21:23:34 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	numofdigits(int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

void	fillnumstring(char *string, int n, int size)
{
	if (n < 0)
	{
		n *= -1;
		string[0] = '-';
	}
	string[size] = 0;
	while (n > 0)
	{
		string[size - 1] = (n % 10) + 48;
		size--;
		n /= 10;
	}
}

void	minint(char *string)
{
	fillnumstring(string, 214748364, 10);
	string[0] = '-';
	string[10] = '8';
	string[11] = 0;
}

char	*ft_itoa(int n)
{
	char	*number;
	int		size;

	if (!n)
	{
		number = (char *) malloc(2 * sizeof(char));
		number[0] = '0';
		number[1] = 0;
		return (number);
	}
	else if (n == -2147483648)
	{
		number = (char *) malloc((12) * sizeof(char));
		minint(number);
		return (number);
	}
	size = numofdigits(n);
	number = (char *) malloc((size + 1) * sizeof(char));
	if (!number)
		return (NULL);
	fillnumstring(number, n, size);
	return (number);
}
