/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:58:24 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/18 05:54:10 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_env(t_my_env *env)
{
	t_my_env	*tmp;
	t_my_env	*tmp2;
	char		*name;
	char		*value;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strncmp(tmp->name, tmp2->name, ft_strlen(tmp->name)) > 0)
			{
				name = tmp->name;
				value = tmp->value;
				tmp->name = tmp2->name;
				tmp->value = tmp2->value;
				tmp2->name = name;
				tmp2->value = value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

t_my_env	*go_to_end(t_my_env *env)
{
	t_my_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

bool	auxiliar_errors_export(char input)
{
	if (input == ' ')
		return (1);
	if ((!ft_isdigit(input) && !ft_isalnum(input) && input != '_'))
		return (1);
	return (0);
}

void	handle_errors_export(char *input, bool *local_error)
{
	int	i;

	i = -1;
	if (ft_isdigit(input[0]))
	{
		*local_error = true;
		ft_error(ERR_INVALID_CHAR, input);
	}
	else
	{
		while (input[++i])
		{
			if (auxiliar_errors_export(input[i]))
			{
				*local_error = true;
				ft_error(ERR_INVALID_CHAR, input);
				break ;
			}
		}
	}
}

void	handle_split_env(char **name, char **value, char *newvar)
{
	if (ft_strchr(newvar, '=') == NULL)
	{
		*name = ft_strdup(newvar);
		*value = ft_strdup(" ");
	}
	else
	{
		*name = ft_substr(newvar, 0, ft_strchr(newvar, '=') - newvar);
		*value = ft_substr(ft_strchr(newvar, '=') + 1, 0,
				ft_strlen(ft_strchr(newvar, '=') + 1));
	}
}
