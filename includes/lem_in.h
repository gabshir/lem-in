/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 03:38:57 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/19 00:18:50 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include <stdio.h>
# include "mlx.h"
# include <limits.h>

# define ER	"ERROR: "
# define SECURE_MALLOC(a)	!(a) && memory_error()

# define ROOMS		map->rooms
# define ROOM_Q		map->room_q
# define C_QUANT	map->comb.quant
# define C_STEPS	map->comb.steps
// # define C_WAY		map->comb.way_arr
# define C_WAY		map->comb.paths
# define C_SUM_LEN	map->comb.sum_len

/*
**	Graphics macros and structures
*/

# define W_WIDTH	1920
# define W_HEIGHT	1080
# define BACK		0xF0FFFF
# define START		0x00CC00
# define END		0x0000FF
# define COMMON		0x000000
# define NAME		0xCE26C9
# define ANT		0x8B4513
# define INDENT		map->mlx.indent

typedef struct	s_img
{
	void	*img_ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win;
	t_img	pic;
	int		indent;
	int		y_len;
	int		x_len;
}				t_mlx;

/*
**	Algo structures
*/

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
	int		ant_num;
}				t_room;

typedef struct	s_path
{
	int		len;
	int		last_i;
	int		ants;
	t_room	**rooms;
}				t_path;

typedef	struct	s_comb
{
	int		quant;
	int		sum_len;
	int		steps;
	t_path	*paths;
}				t_comb;

typedef struct	s_map
{
	int		ants;
	size_t	room_q;
	t_room	start;
	t_room	end;
	t_room	**rooms;
	t_list	*way;
	t_list	*cut;
	t_comb	comb;

	t_mlx	mlx;
	int		fd;
}				t_map;

/*
 * get_map_info
 */

void	get_map_info(t_map *map, int print);
void	validate_axis(t_room *room, char *splitstr, char axis);
void	room_name_and_coords(t_room *room, char *line);
void	start_init(t_map *map, char *line, int print);
void	end_init(t_map *map, char *line, int print);
t_room	*create_room(t_map *map, char *line);
void	put_ptr_in_array(int penultimate, t_room **rooms, t_room *room);
t_room	**sorted_rooms_ptr_array(t_map *map, t_list **room_list);
void	check_name_duplicates(t_map *map);
void	create_link(t_map *map, char *name_fst, char *name_snd);
t_room	*find_room_by_name(t_map *map, char *r_name, int first, int last);
void	organize_links(t_map *map, char *line);
int		check_existing_links(t_list *links, char *r_name);
void	quantity_of_ants(t_map *map, char *line, int print);
void	start_map_info(t_map *map, char *line, int print);
void	organize_room(e_sort *time_to_sort, t_map *map, \
		char *line, t_list *room_list);
int		lstadd_room(e_sort time_to_sort, t_list **room_list, \
		t_map *map, char *line);
int		check_hash(char *line, char *edge, char *counter_edge);

/*
** ALGORITM
*/

void	way(t_map *map, int l);
int		shirina(t_map *map);
t_list *fiststart(t_list *start);
void	ft_listaddshirina(t_list **up_list, t_room *read);
int		shirinablok(t_map *map);
int		path_analysis(t_list **combo);
void	ft_saveway(t_room *end, t_list **way, int f, int d);
void	up_gl(t_list **obr, t_list **up_list, int *gl);

/*
** Restor Room
*/

void	restisp(t_list **way);
void	ft_restor(t_list **links);
void	restornap(t_list **way);
void	restorroom(t_map *map);

/*
** Free for Algoritms
*/

void	freeway(t_list **way);
int		finishfree(t_list **obr, t_list **up_list);
t_list	*deque(t_list *que);
void	ft_freedown(t_list **links, int n);

/*
**	Tools
*/

// float	connectivity(t_map *map);

/*
**	Ant flow
*/

void    ant_flow(t_map *map);
void	make_best_combination(t_map *map);

/*
**	Error
*/

int		memory_error(void);
void	error_specify_room(char *str);
void	dublication_room(char *str);
void	error_create_links(char *str);

/*
**	Debug
*/

void	debug_links(t_map *map);
void	ft_printway(t_list *obway);
void	print_que(t_list *que);
// void	print_combinations(t_map *map);
// void	print_one_comb(t_map *map);
void	print_best_comb(t_map *map);
void	print_path(t_path *path);


/*
**	Visual	##########################################################
*/

//	test

void	v_start_init(int fd, t_map *map, char *line, int print);
void	v_end_init(int fd, t_map *map, char *line, int print);
void 	start_vis_info(int fd, t_map *map, char *line, int print);
void	get_vis_info(int fd, t_map *map, int print);

#endif
