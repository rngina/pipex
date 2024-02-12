/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:01:12 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/12 15:25:42 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pid1;
	int		pid2;

	if (argc == 5)
	{
		init_pipex(&pipex, argv, envp);
		process(&pipex, envp, &pid1, &pid2);
	}
	else
	{
		ft_putstr_fd("Invalid number of arguments\n", STDOUT_FILENO);
		return (1);
	}
	return (pipex.exit_code);
}
