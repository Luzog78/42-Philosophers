/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_print_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:09:43 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/09 16:16:41 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_print_list(t_print_list **list)
{
	t_print_list	*tmp;

	if (!list || !*list)
		return ;
	tmp = *list;
	while (tmp)
	{
		*list = (*list)->next;
		free(tmp);
		tmp = *list;
	}
	*list = NULL;
}
