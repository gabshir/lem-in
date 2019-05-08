/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 03:38:57 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/07 20:00:46 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include <stdio.h>

// # define START_ROOM	1
// # define END_ROOM	2
# define ER	"ERROR: "

# define ROOMS	map->rooms
# define ROOM_Q	map->room_q

typedef enum	e_sort
{
	not_sorted, sorted
}				e_sort;

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
	int		n;
	int		f;
	int 	isp;
	int		gl;
	t_list	*links;
	t_list	*way;
}				t_room;

typedef struct	s_map
{
	int		error;
	int		ants;
	int		room_q;
	int		short_ways;
	t_room	start;
	t_room	end;
	t_room	**rooms;
	t_list	*p;
	int		f;
	t_list	*way;
}				t_map;

void	validate_axis(t_map *map, t_room *room, char *splitstr, char axis);
void	room_name_and_coords(t_map *map, t_room *room, char *line);
void	check_hash(t_map *map, char *line, char *edge, char *counter_edge);
void	start_init(t_map *map, char *line, int fd);
void	end_init(t_map *map, char *line, int fd);
t_room	*create_room(t_map *map, char *line);
void	put_ptr_in_array(int penultimate, t_room **rooms, t_room *room);
t_room	**sorted_rooms_ptr_array(t_map *map, t_list **room_list);
void	check_name_duplicates(t_map *map);
t_room	*find_room_by_name(t_map *map, char *r_name, int first, int last);
void	create_link(t_map *map, char *name_fst, char *name_snd);
void	organize_links(t_map *map, char *line);
int		check_existing_links(t_list *links, char *r_name);

int		algorithm_begins(t_map map);
int		glubina(t_map *map);
void	ft_listaddglubina(t_list **up_list, t_list *new);
void	way(t_map *map);
void	ft_freedown(t_list **links, int n);

int		links_quantity(t_room *room);

void	debug_links(t_map *map);

#endif
