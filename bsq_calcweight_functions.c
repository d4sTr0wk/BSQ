#include "bsq_calcweight_functions.h"

void	print_matrix(char **matrix, int row_count, int column_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < row_count)
	{
		j = 0;
		while (j < column_count)
		{
			write(1, &(matrix[i][j]), 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

char	**write_x_in_matrix(char **matrix, int weigth, struct s_pos pos, struct s_param params)
{
	int	row_pos;
	int	column_pos;

	column_pos = pos.cp;
	while (column_pos < pos.cp + weigth)
	{
		row_pos = pos.rp;
		while (row_pos < pos.rp + weigth)
		{
			matrix[row_pos][column_pos] = params.fill;
			row_pos++;
		}
		column_pos++;
	}
	return (matrix);
}

struct s_pos	find_c_obs(int column_pos, int row_pos, struct s_pos *obs_dic)
{
	int				it;
	int				found;
	struct s_pos	obs_pos;

	it = -1;
	found = 0;
	obs_pos.cp = -1;
	obs_pos.rp = -1;
	while (!found && obs_dic[++it].rp != -1)
	{
		if (obs_dic[it].cp >= column_pos
			&& obs_dic[it].rp == row_pos)
		{
			found = 1;
			obs_pos.cp = obs_dic[it].cp;
			obs_pos.rp = obs_dic[it].rp;
		}
	}
	return (obs_pos);
}