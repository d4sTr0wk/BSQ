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

	column_pos = pos.column_pos;
	while (column_pos < pos.column_pos + weigth)
	{
		row_pos = pos.row_pos;
		while (row_pos < pos.row_pos + weigth)
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