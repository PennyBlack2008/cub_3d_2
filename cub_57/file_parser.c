/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:19:55 by jikang            #+#    #+#             */
/*   Updated: 2020/11/11 21:19:58 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_identifier(t_win *win, char *line, t_list **lst)
{
	if (*line)
	{
		if (ft_strncmp(line, "R ", 2) == 0)
			parse_resolution(win, line + 2, 'R');
		else if (ft_strncmp(line, "NO ", 3) == 0)
			parse_texture(win, line + 3, 'N');
		else if (ft_strncmp(line, "SO ", 3) == 0)
			parse_texture(win, line + 3, 'S');
		else if (ft_strncmp(line, "WE ", 3) == 0)
			parse_texture(win, line + 3, 'W');
		else if (ft_strncmp(line, "EA ", 3) == 0)
			parse_texture(win, line + 3, 'E');
		else if (ft_strncmp(line, "S ", 2) == 0)
			parse_texture(win, line + 2, 's');
		else if (ft_strncmp(line, "F ", 2) == 0)
			parse_color(win, line + 2, 'F');
		else if (ft_strncmp(line, "C ", 2) == 0)
			parse_color(win, line + 2, 'C');
		else if (*line == ' ' || *line == '0' || *line == '1' || *line == '2')
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(line)));
		else
			error_handler("Invalid .cub file!", 0);
	}
}

static void	del(void *content)
{
	free(content);
}

void		file_parser(t_win *win, char *file)
{
	char		*line;
	int			fd;
	t_list		*lst;
	int			ret;

	lst = NULL;
	if ((fd = open(file, O_RDONLY)) < 0)
		error_handler("Cannot open the file!", errno);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		parse_identifier(win, line, &lst);
		free(line);
		if (ret == 0)
			break ;
	}
	parse_map(win, lst);
	ft_lstclear(&lst, del);
	close(fd);
}
