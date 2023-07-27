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

#ifndef BSQ_CALCWEIGHT_FUNCTIONS_H
# define BSQ_CALCWEIGHT_FUNCTIONS_H

# include "bsq.h"

struct	s_param;
struct	s_pos;

void			print_matrix(char **matrix, int row_count, int column_count);
char			**write_x_in_matrix(char **matrix, int weigth, struct s_pos pos,
					struct s_param params);
struct s_pos	find_c_obs(int column_pos, int row_pos, struct s_pos *obs_dic);

#endif
