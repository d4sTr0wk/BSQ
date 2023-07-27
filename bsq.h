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

#ifndef BSQ_H
# define BSQ_H

# include "bsq_algorithm_functions.h"
# include "bsq_calcweight_functions.h"
# include "bsq_readfile_functions.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 2147483647

struct				s_pos
{
	int				rp;
	int				cp;
};

struct				s_param
{
	int				num_lines;
	char			empty;
	char			obs;
	char			fill;
};

struct				s_all
{
	struct s_pos	counter;
	int				cont;
	int				error;
	char			*buffer;
	struct s_param	params;
};
int					main(int argc, char *argv[]);
int					algorithm(struct s_pos counter, char *buffer,
						struct s_param params, int i);
int					read_file(char *file, struct s_pos *counter, char **buffer,
						struct s_param *p);
int					ft_file(char *file_name, int *len, char **buffer);
struct s_all		ini(struct s_all types, char **argv, int *ok);

#endif
