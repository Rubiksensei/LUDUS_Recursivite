/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 11:27:05 by elenne            #+#    #+#             */
/*   Updated: 2016/08/15 11:15:56 by elenne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_factorial(int nb)
{
	int result;

	if (nb < 0)
		return (0);
	if (nb <= 1)
		return (1);
	if (nb > 12)
		return (0);
	result = (nb * ft_recursive_factorial(nb - 1));
	return (result);
}
