/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:30:10 by jikang            #+#    #+#             */
/*   Updated: 2020/11/12 13:51:22 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

# define WIN_WIDTH		1000
# define WIN_HEIGHT		1000
# define FOV			60

# define ERROR			0
# define SUCCESS		1
# define FILEEND		0

# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define KEY_LEFT		123
# define KEY_RIGHT		124

# define KEY_F			3
# define KEY_G			5
# define KEY_H			4

# define KEY_ESC		53

/*
** WALL
*/

# define WALL 			49
# define NOT_WALL		48
# define SPRITE			50

/*
** NSEW
*/
# define NORTH			0
# define SOUTH			1
# define EAST			2
# define WEST			3

/*
** Center of the Projection Plane = (160,100)
** Distance to the Projection Plane = 277 units
** Angle between subsequent rays = 60/320 degrees
*/

typedef struct			s_plot
{
	double				x;
	double				y;
}						t_plot;

typedef struct			s_plot_int
{
	double				x;
	double				y;
}						t_plot_int;

typedef union			u_color
{
	int					color;
	struct
	{
		unsigned char	b:8;
		unsigned char	g:8;
		unsigned char	r:8;
		unsigned char	t:8;
	}					trgb;
}						t_color;

typedef struct			s_wall
{
	double				length;
	double				height;
}						t_wall;

/*
** s_sprite
** int i : ray 번호
** double dist : 플레이어와 sprite 거리
*/

typedef struct			s_sprite
{
	int					i;
	double				dist;
}						t_sprite;

typedef struct			s_sprite_var
{
	double				dist_to_spr;
	double				pjtd_height;
	double				o_pjtd_height;
	double				pjtd_width;
	double				o_pjtd_width;
	double				scale_h;
	double				scale_w;
}						t_sprite_var;

/*
** s_player
** 1. player figure: width, height, color
** 2. player 가 보는 각도 및 plane: ang, projected_plane
** 3. player 위치: plot, facing
*/

typedef struct			s_player
{
	int					width;
	int					height;
	int					color;
	double				ang;
	double				projected_plane;
	t_plot				plot;
	char				facing;
}						t_player;

typedef struct			s_tex
{
	void				*ptr;
	int					*addr;
	int					bpp;
	int					len;
	int					endian;
	int					width;
	int					height;
}						t_tex;

typedef struct			s_img
{
	void				*ptr;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					x;
	int					y;
	int					tile_color;
}						t_img;

/*
** s_map_info
** 1. texture 벽과 스프라이트
** 2. 그리고 천장과 바닥의 rgb값
*/

typedef struct			s_map_info
{
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
	char				*sprite_texture;
	t_color				fl_rgb;
	t_color				cl_rgb;
}						t_map_info;

typedef struct			s_map
{
	char				**map;
	char				*map_1d;
	int					map_width;
	int					map_height;
	int					*curr_tex[5];
	t_map_info			info;
}						t_map;

/*
** s_ray
** 1. hit: 벽에 부딛힌 좌표
** 2. ang: 플레이어 기준에서 ray의 고유한 각도
** 3. wall_NSEW: 부딛힌 벽 방향 NO: 0, SO: 1, EA: 2, WE: 3
*/

typedef struct			s_ray
{
	t_plot				hit;
	t_plot				wall;
	t_plot				spr_hit;
	t_plot				spr_map;
	double				scale_h;
	double				ang;
	int					wall_nsew;
	double				ceiling;
	double				floor;
}						t_ray;

typedef struct			s_win
{
	void				*mlx;
	void				*win;
	int					r_width;
	int					r_height;
	double				fov_ang;
	int					num_sprite;
	t_img				img;
	t_map				map;
	t_player			player;
	t_wall				wall;
	t_tex				tex[5];
}						t_win;

/*
** bresenhem.c
*/

void					draw_line(t_plot p1, t_plot p2, int color, t_win *w);

/*
** draw_ceiling.c
*/

void					draw_ceiling(int i, t_ray *r, t_win *w);

/*
** draw_floor.c
*/

void					draw_floor(int i, t_ray *r, t_win *w);

/*
** draw_sprite.c
*/

void					draw_a_sprite(int i, t_ray *r, t_win *w);

/*
** draw_wall.c
*/

void					draw_a_wall(int i, t_ray *r, t_win *w);

/*
** file_parser.c
*/

void					file_parser(t_win *win, char *file);

/*
** init.c
*/

int						init_struct_win(t_win *w);

/*
** map_validator.c
*/

void					map_validtator(t_win *win);

/*
** map.c
*/

void					map_init(t_win *w);
int						is_wall(double x, double y, t_win *w);

/*
** move.c
*/

int						move_forward(t_win *w);
int						move_back(t_win *w);
int						move_left(t_win *w);
int						move_right(t_win *w);

/*
** rotate.c
*/

int						rotate_right(t_win *w);
int						rotate_left(t_win *w);

/*
** parse.c
*/

void					parse_resolution(t_win *win, char *line,
								char identifier);
void					parse_texture(t_win *win, char *line, char identifier);
void					parse_color(t_win *win, char *line, char identifier);
void					parse_map(t_win *win, t_list *lst);

/*
** raycasting.c
*/

int						cast_rays(t_win *w);

/*
** screenshot.c
*/

int						screenshot(t_win *w);

/*
** sort_sprite.c
*/

void					draw_sprites(t_sprite *spr, t_ray *r, t_win *w);

/*
** draw_sprite.c
*/

void					draw_a_sprite(int i, t_ray *r, t_win *w);

/*
** utils 파일
*/

/*
** utils_part_a.c
*/

void					my_mlx_pixel_put(t_img *img, int x, int y, int color);
unsigned int			my_mlx_pixel_get(t_img *img, int x, int y);
double					normalize_angle(double ang);
void					set_plot(t_plot *plot, double x, double y);
int						draw_background(t_win *w);

/*
** utils_part_b.c
*/

void					save_plot(t_plot *dst_plot, t_plot *src_plot);
int						color_rgb(int r, int g, int b);
int						safer_free_pp(void **pp);
int						safer_free_p(void *p);
void					error_handler(char *s, int num);

/*
** utils_part_c.c
*/

int						shut_down(t_win *w);
int						check_resol(char **tmp);
int						ft_isspace(int c);
int						check_color(char **tmp);
double					hy_pot(double x, double y);

/*
** utils_part_d.c
*/

void					forward(t_win *w);
void					backward(t_win *w);
void					leftward(t_win *w);
void					rightward(t_win *w);
double					ft_floor(double x);

#endif
