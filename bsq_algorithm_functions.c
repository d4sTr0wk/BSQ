#include "bsq_algorithm_functions.h"

char	**fill_matrix(char **matrix, char *buffer, int rcnt, struct s_param params)
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
		if ((*(buffer + pos_buffer) == params.obs) || (*(buffer + pos_buffer) == params.empty))
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

struct s_pos	*put_obstacles(char **matrix, struct s_pos *obs_dic, int rcnt,
		int ccnt, struct s_param params)
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
			if (matrix[row_pos][column_pos] == params.obs)
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

void	calc_weight(char **m, struct s_pos *obs_dic, int rc, int cc,
		struct s_pos res_p, struct s_param params)
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
			if (m[row_pos][column_pos] != params.obs)
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
						if (rc - row_pos < candidate_weight)
							candidate_weight = rc - row_pos;
						else
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
	print_matrix(write_x_in_matrix(m, greater_weight, res_p, params), rc, cc);
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
