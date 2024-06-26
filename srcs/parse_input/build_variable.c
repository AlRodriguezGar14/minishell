/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:22:03 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/24 13:53:18 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_sent(char **sent)
{
	int	idx;

	if (!sent)
		return ;
	idx = 0;
	while (sent[idx])
	{
		if (sent[idx])
		{
			free(sent[idx]);
			idx++;
		}
	}
	sent[idx] = NULL;
}

char	*get_the_variable(char *cmd, t_shell *shell)
{
	int		idx;
	int		jdx;
	char	**sent;
	char	*out;
	char	*expanded;

	idx = -1;
	sent = ft_calloc(4, sizeof(char *));
	while (cmd[++idx])
	{
		if (cmd[idx] == '$')
		{
			free_sent(sent);
			sent[0] = ft_substr(cmd, 0, idx);
			jdx = 0;
			while (search_token(cmd, idx, jdx))
				jdx++;
			sent[1] = ft_substr(cmd, idx + 1, jdx - 1);
			sent[2] = ft_substr(cmd, idx + jdx, ft_strlen(cmd) - idx - jdx);
		}
	}
	expanded = search_expand(shell, sent[1]);
	out = ft_sprintf("%s%s%s", sent[0], expanded, sent[2]);
	return (free_sent(sent), free(sent), free(cmd), free(expanded), out);
}

static int	replace_with_global(char **cmd, int idx, int jdx)
{
	char	*end;
	char	*start;
	char	*global;
	char	*tmp;

	end = NULL;
	start = NULL;
	global = NULL;
	if (cmd[idx][jdx + 1] == '?')
	{
		jdx += 2;
		if (cmd[idx][jdx] != '\0')
			end = ft_substr(cmd[idx], jdx, ft_strlen(cmd[idx] + jdx));
		start = ft_substr(cmd[idx], 0, jdx - 2);
		global = ft_sprintf("%d", g_status);
		free(cmd[idx]);
		tmp = ft_sprintf("%s%s%s", start, global, end);
		cmd[idx] = ft_strtrim(tmp, " ");
		return (free(tmp), free(start), free(global), free(end), 1);
	}
	return (0);
}

char	**expand_variable(char **cmd, t_shell *shell, int s_quote, int d_quote)
{
	int	idx;
	int	jdx;

	idx = -1;
	while (cmd[++idx])
	{
		jdx = -1;
		while (cmd[idx][++jdx])
		{
			set_quote(&s_quote, &d_quote, cmd[idx][jdx]);
			if (cmd[idx][jdx] == '$' && (!s_quote || (s_quote <= d_quote)))
			{
				if (replace_with_global(cmd, idx, jdx))
					continue ;
				else if (cmd[idx][jdx + 1] == '\0')
					continue ;
				cmd[idx] = get_the_variable(cmd[idx], shell);
				jdx = -1;
			}
		}
	}
	return (cmd);
}
