/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouhaik <ybouhaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:28:41 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/25 20:38:42 by ybouhaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 2147483647

struct			s_pos
{
	int			row_pos;
	int			column_pos;
};

struct			s_param
{
	int			num_lines;
	char		empty;
	char		obs;
	char		fill;
};

// AQUI NO SE SI PONER LAS CABECERAS QUE HAY EN EL OTRO ARCHIVO O UNA LIBRERIA

struct s_pos	find_c_obs(int column_pos, int row_pos, struct s_pos *obs_dic);

void			calc_weight(char **m, struct s_pos *obs_dic, int rc, int cc,
					struct s_pos res_p, struct s_param params);

struct s_pos	*put_obstacles(char **matrix, struct s_pos *obs_dic, int rcnt,
					int ccnt, struct s_param params);

char			**fill_matrix(char **matrix, char *buffer, int rcnt,
					struct s_param params);

int	ft_atoi(char *str, int pos)
{
	long	num;
	int		cont;

	cont = 0;
	num = 0;
	while (cont < pos)
	{
		num *= 10;
		num += str[cont] - '0';
		cont++;
	}
	return ((int)num);
}

struct s_param	attributes(char *buffer)
{
	int				pos_buffer;
	int				num;
	struct s_param	params;

	num = 1;
	pos_buffer = 0;
	while (*(buffer + pos_buffer) != '\n')
		pos_buffer++;
	params.num_lines = ft_atoi(buffer, pos_buffer - 3);
	params.fill = *(buffer + pos_buffer - 1);
	params.empty = *(buffer + pos_buffer - 3);
	params.obs = *(buffer + pos_buffer - 2);
	if (params.fill == params.empty || params.fill == params.obs
		|| params.obs == params.empty || pos_buffer < 4 || *(buffer
			+ pos_buffer) != '\n' || *(buffer + pos_buffer + 1) == '\0')
		params.num_lines = -1;
	return (params);
}

int long_lines(char *buffer, struct s_param *params, int pos, int i)
{
	int cont;
	cont = 0;
	while (*(buffer + pos) != '\n')
	{
		if (*(buffer + pos) != params->empty && *(buffer + pos) != params->obs)
			return (0);
		pos++;
		cont++;
	}
	if (i != cont)
		return (0);
	return (1);
}

int	valid_map(char *buffer, struct s_param *params, int row_count)
{
	int	cont;
	int	i;
	int rows;
	int pos;

	pos = 0;
	rows = 1;
	cont = 0;
	if (row_count != params->num_lines)
		return (-2);
	while (*(buffer + pos) != '\n')
		pos++;
	pos++;
	while (*(buffer + pos) != '\n')
	{
		pos++;
		cont++;
	}
	pos++;
	i = cont;
	while (rows < row_count)
	{	
		if (!long_lines(buffer, params, pos, i))
			return (0);
		pos++;
		rows++;
	}
	return (1);
}

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
			write(1, "map error\n", 11);
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
