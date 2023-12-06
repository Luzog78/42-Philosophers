/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_get_nth.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:47:03 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/05 06:52:25 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char const	*ft_print_get_nth(int nth)
{
	if (nth % 10 == 1 && nth % 100 != 11)
		return ("st");
	else if (nth % 10 == 2 && nth % 100 != 12)
		return ("nd");
	else if (nth % 10 == 3 && nth % 100 != 13)
		return ("rd");
	else
		return ("th");
}
