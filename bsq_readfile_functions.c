#include "bsq_readfile_functions.h"

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

int long_lines(char *buffer, struct s_param *params, int *pos, int i)
{
	int cont;
	cont = 0;
	while (*(buffer + *pos) != '\n' && ++cont)
	{
		if (*(buffer + *pos) != params->empty && *(buffer + *pos) != params->obs)
			return (0);
		(*pos)++;
	}
	(*pos)++;
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
		return (0);
	while (*(buffer + pos++) != '\n')
		;
	while (*(buffer + (pos++)) != '\n')
		cont++;
	i = cont;
	while (rows < row_count)
	{	
		if (!long_lines(buffer, params, &pos, i))
			return (0);
		rows++;
	}
	return (1);
}