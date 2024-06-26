/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_things_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:27:21 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/11 05:36:23 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_pp(char **container)
{
	int	y;

	y = -1;
	while (container[++y])
		;
	return (y);
}

void	print_env(t_my_env *env)
{
	while (env)
	{
		if (env->name && env->value && ft_strlen(env->name) > 0)
			printf("declare -x %s=%s\n", env->name, env->value);
		env = env->next;
	}
}
