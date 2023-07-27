/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:31:39 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/07/25 20:42:54 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq_algorithm_functions.h"

char	**fill_matrix(char **matrix, char *buffer, int rcnt,
		struct s_param params)
{
	int	row_pos;
	int	column_pos;
	int	pos_buffer;

	pos_buffer = 0;
	row_pos = 0;
	column_pos = 0;
	while (*(buffer + (pos_buffer++)) != '\n')
		;
	while (*(buffer + pos_buffer) != '\0' && row_pos != rcnt)
	{
		if ((*(buffer + pos_buffer) == params.obs) || (*(buffer
					+ pos_buffer) == params.empty))
			matrix[row_pos][column_pos] = *(buffer + pos_buffer);
		if (*(buffer + pos_buffer++) == '\n')
		{
			++row_pos;
			column_pos = 0;
		}
		else
			++column_pos;
	}
	return (matrix);
}

struct s_pos	*put_obstacles(char **matrix, struct s_pos *obs_dic,
		struct s_pos counter, struct s_param params)
{
	int	row_pos;
	int	column_pos;
	int	it;

	column_pos = -1;
	it = 0;
	while (++column_pos < counter.cp)
	{
		row_pos = -1;
		while (++row_pos < counter.rp)
		{
			if (matrix[row_pos][column_pos] == params.obs)
			{
				obs_dic[it].cp = column_pos;
				obs_dic[it].rp = row_pos;
				it++;
			}
		}
	}
	obs_dic[it].cp = -1;
	obs_dic[it].rp = -1;
	return (obs_dic);
}

void	calc_weight(char **m, struct s_pos *obs_dic, struct s_pos c,
		struct s_pos res_p, struct s_param params)
{
	struct s_pos	pos;
	int				greater_weight;
	int				candidate_weight;
	struct s_pos	obs_pos;
	int				it;

	greater_weight = 0;
	pos.rp = -1;
	pos.cp = -1;
	while (++pos.rp < c.rp)
	{
		pos.cp = -1;
		while (++pos.cp < c.cp)
		{
			if (m[pos.rp][pos.cp] != params.obs)
			{
				obs_pos = find_c_obs(pos.cp, pos.rp, obs_dic);
				if (obs_pos.rp == -1)
					candidate_weight = c.cp - pos.cp;
				else
					candidate_weight = obs_pos.cp - pos.cp;
				if (greater_weight < candidate_weight)
				{
					it = pos.rp + 1;
					while (candidate_weight >= (it - pos.rp + 1) && it < c.rp)
					{
						obs_pos = find_c_obs(pos.cp, it, obs_dic);
						if ((obs_pos.cp != -1) && ((obs_pos.cp
									- pos.cp) < candidate_weight))
							candidate_weight = obs_pos.cp - pos.cp;
						it++;
					}
					if (candidate_weight > greater_weight && (it
							- pos.rp) == candidate_weight && (((obs_pos.cp
									- pos.cp) >= candidate_weight)
							|| (obs_pos.cp == -1)))
					{
						greater_weight = candidate_weight;
						res_p.cp = pos.cp;
						res_p.rp = pos.rp;
					}
					else
					{
						if (c.rp - pos.rp < candidate_weight)
							candidate_weight = c.rp - pos.rp;
						else
							candidate_weight = obs_pos.rp - pos.rp;
						if (greater_weight < candidate_weight)
						{
							greater_weight = candidate_weight;
							res_p.cp = pos.cp;
							res_p.rp = pos.rp;
						}
					}
				}
			}
		}
	}
	print_matrix(write_x_in_matrix(m, greater_weight, res_p, params), c.rp,
		c.cp);
}

void	free_mat(char **matrix, struct s_pos *obs_dic, int rcnt)
{
	int	i;

	i = 0;
	while (i < rcnt)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	free(obs_dic);
}
