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

struct s_param
{
	int num_lines;
	char empty;
	char obs;
	char fill;
};

// AQUI NO SE SI PONER LAS CABECERAS QUE HAY EN EL OTRO ARCHIVO O UNA LIBRERIA

char			**write_x_in_matrix(char **matrix, int weigth,
					struct s_pos pos);
struct s_pos	find_c_obs(int column_pos, int row_pos, struct s_pos *obs_dic);

void			calc_weight(char **m, struct s_pos *obs_dic, int rc, int cc,
					struct s_pos res_p);

struct s_pos	*put_obstacles(char **matrix, struct s_pos *obs_dic, int rcnt,
					int ccnt);

char			**fill_matrix(char **matrix, char *buffer, int rcnt);

void			print_matrix(char **matrix, int row_count, int column_count);

int	ft_atoi(char *str, int pos)
{
	long	num;
	int cont;

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

struct s_param attributes (char *buffer)
{	
	int pos_buffer;
	int num;
	struct s_param params;

	num = 1;
	pos_buffer = 0;
	while(*(buffer + pos_buffer) != '\n')	
		pos_buffer++;
	params.num_lines = ft_atoi(buffer, pos_buffer - 3);
	params.fill = *(buffer + pos_buffer - 1);
	params.empty = *(buffer + pos_buffer - 3);
	params.obs = *(buffer + pos_buffer - 2);
	
	return (params);
}

int	read_file(char *file_name, int *row_count, int *column_count, char **buffer)
{
	int	file;
	int	i;
	int	len;
	struct s_param params;

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
	params = attributes(*buffer);
	while (++i < len)
	{
		if (*(*buffer + i) == '\n')
			++(*row_count);
		else if (!(*row_count))
			++(*column_count);
	}
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

int	algorithm(int rcnt, int ccnt, char *buffer)
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
	matrix = fill_matrix(matrix, buffer, rcnt);
	obs_dic = (struct s_pos *)malloc(sizeof(struct s_pos) * rcnt * ccnt);
	if (!obs_dic)
		return (1);
	obs_dic = put_obstacles(matrix, obs_dic, rcnt, ccnt);
	calc_weight(matrix, obs_dic, rcnt, ccnt, res_p);
	free_mat(matrix, obs_dic, rcnt);
	return (0);
}

int	main(int argc, char *argv[])
{
	int		row_count;
	int		column_count;
	int		cont;
	char	*buffer;

	cont = 1;
	// argc = 2;
	// argv[1] = "example2_file";
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
		return (1);
	if (!argc)
		return (1);
	while (cont < argc)
	{
		row_count = -1;
		column_count = 0;
		if (read_file(argv[cont], &row_count, &column_count, &buffer) == (-1))
			return (1);
		if (algorithm(row_count, column_count, buffer))
			return (1);
		write(1, "\n", 1);
		cont++;
	}
	free(buffer);
	return (0);
}
