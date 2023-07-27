#include "bsq.h"

int	read_file(char *file_name, int *row_count, int *column_count, char **buffer,
		struct s_param *params)
{
	int	file;
	int	i;
	int	len;
	
	file = open(file_name, O_RDONLY);
	if (file == -1)
		return (-1);
	len = read(file, *buffer, BUFFER_SIZE);
	if (len == -1)
	{
		close(file);
		return (-1);
	}
	i = -1;
	*params = attributes(*buffer);
	if (params->num_lines == -1)
		return (-2);
	while (++i < len)
	{
		if (*(*buffer + i) == '\n')
			++(*row_count);
		else if (!(*row_count))
			++(*column_count);
	}
	if (!valid_map(*buffer, params, *row_count))
		return (-2);
	if (close(file) == -1)
		return (-1);
	return (0);
}



int	algorithm(int rcnt, int ccnt, char *buffer, struct s_param params)
{
	char			**matrix;
	int				i;
	struct s_pos	*obs_dic;
	struct s_pos	res_p;

	i = -1;
	res_p.column_pos = -1;
	res_p.row_pos = -1;
	matrix = (char **)malloc(sizeof(char *) * rcnt);
	if (matrix == NULL)
		return (1);
	while (++i < rcnt)
	{
		matrix[i] = (char *)malloc(sizeof(char) * ccnt);
		if (matrix[i] == NULL)
			return (1);
	}
	matrix = fill_matrix(matrix, buffer, rcnt, params);
	obs_dic = (struct s_pos *)malloc(sizeof(struct s_pos) * rcnt * ccnt);
	if (!obs_dic)
		return (1);
	obs_dic = put_obstacles(matrix, obs_dic, rcnt, ccnt, params);
	calc_weight(matrix, obs_dic, rcnt, ccnt, res_p, params);
	free_mat(matrix, obs_dic, rcnt);
	return (0);
}

int	main(int argc, char *argv[])
{
	int				row_count;
	int				column_count;
	int				cont;
	int				error;
	char			*buffer;
	struct s_param	params;

	cont = 1;
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
		return (1);
	if (!argc)
		return (1);
	while (cont < argc)
	{
		row_count = -1;
		column_count = 0;
		error = read_file(argv[cont], &row_count, &column_count, &buffer,
				&params);
		if (error == (-1))
			return (1);
		else if (error == (-2))
		{
			write(2, "map error\n", 11);
			return (1);
		}
		if (algorithm(row_count, column_count, buffer, params))
			return (1);
		write(1, "\n", 1);
		cont++;
	}
	free(buffer);
	return (0);
}
