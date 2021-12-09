/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:22:15 by dweeper           #+#    #+#             */
/*   Updated: 2021/12/09 18:19:27 by dweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_TREE_H
# define S_TREE_H

typedef struct	s_simple_command
{
	char	*command_path;
	char	*args_array;
}	t_sc

typedef struct	s_command
{
	struct t_sc	*sc;
	char		*in;
	char		*out;
}	t_com;

typedef struct	s_job
{
	struct t_com	*com;
	struct t_job	*next_job;	
}	t_job;

typedef struct	s_command_line
{
	struct t_job	*job;
	struct t_cl		*and_cl;
	struct t_cl		*semicolon_cl;	
}	t_cl;

#endif
