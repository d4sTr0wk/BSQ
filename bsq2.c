/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:23:28 by ybouhaik          #+#    #+#             */
/*   Updated: 2023/07/25 20:42:32 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

struct			s_pos
{
	int			row_pos;
	int			column_pos;
};

void			print_matrix(char **matrix, int row_count, int column_count);
char			**write_x_in_matrix(char **matrix, int weigth,
					struct s_pos pos);

struct s_pos	find_c_obs(int column_pos, int row_pos, struct s_pos *obs_dic)
{
	int				it;
	int				found;
	struct s_pos	obs_pos;

	it = -1;
	found = 0;
	obs_pos.column_pos = -1;
	obs_pos.row_pos = -1;
	while (!found && obs_dic[++it].row_pos != -1)
	{
		if (obs_dic[it].column_pos >= column_pos
			&& obs_dic[it].row_pos == row_pos)
		{
			found = 1;
			obs_pos.column_pos = obs_dic[it].column_pos;
			obs_pos.row_pos = obs_dic[it].row_pos;
		}
	}
	return (obs_pos);
}

void	calc_weight(char **m, struct s_pos *obs_dic, int rc, int cc,
		struct s_pos res_p)
{
	int				row_pos;
	int				column_pos;
	int				greater_weight;
	int				candidate_weight;
	struct s_pos	obs_pos;
	int				it;

	greater_weight = 0;
	row_pos = -1;
	column_pos = -1;
	while (++row_pos < rc)
	{
		column_pos = -1;
		while (++column_pos < cc)
		{
			if (m[row_pos][column_pos] != 'o')
			{
				obs_pos = find_c_obs(column_pos, row_pos, obs_dic);
				if (obs_pos.row_pos == -1)
					candidate_weight = cc - column_pos;
				else
					candidate_weight = obs_pos.column_pos - column_pos;
				if (greater_weight < candidate_weight)
				{
					it = row_pos + 1;
					while (candidate_weight >= (it - row_pos + 1) && it < rc)
					{
						obs_pos = find_c_obs(column_pos, it, obs_dic);
						if ((obs_pos.column_pos != -1) && ((obs_pos.column_pos
									- column_pos) < candidate_weight))
							candidate_weight = obs_pos.column_pos - column_pos;
						it++;
					}
					if (candidate_weight > greater_weight && (it
							- row_pos) == candidate_weight
						&& (((obs_pos.column_pos
									- column_pos) >= candidate_weight)
							|| (obs_pos.column_pos == -1)))
					{
						greater_weight = candidate_weight;
						res_p.column_pos = column_pos;
						res_p.row_pos = row_pos;
					}
					else
					{
						candidate_weight = obs_pos.row_pos - row_pos;
						if (greater_weight < candidate_weight)
						{
							greater_weight = candidate_weight;
							res_p.column_pos = column_pos;
							res_p.row_pos = row_pos;
						}
					}
				}
			}
		}
	}
	//printf("rc: %d, cc: %d\n", rc, cc);
	print_matrix(write_x_in_matrix(m, greater_weight, res_p), rc, cc);
}

struct s_pos	*put_obstacles(char **matrix, struct s_pos *obs_dic, int rcnt,
		int ccnt)
{
	int	row_pos;
	int	column_pos;
	int	it;

	column_pos = -1;
	it = 0;
	while (++column_pos < ccnt)
	{
		row_pos = -1;
		while (++row_pos < rcnt)
		{
			if (matrix[row_pos][column_pos] == 'o')
			{
				obs_dic[it].column_pos = column_pos;
				obs_dic[it].row_pos = row_pos;
				it++;
			}
		}
	}
	obs_dic[it].column_pos = -1;
	obs_dic[it].row_pos = -1;
	return (obs_dic);
}
