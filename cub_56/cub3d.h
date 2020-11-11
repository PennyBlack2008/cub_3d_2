#ifndef _CUB3D_H_
# define _CUB3D_H_

#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <unistd.h>
#include <stdio.h> // 꼭 지우기
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// WIN SPEC
#define WIN_WIDTH	1000
#define WIN_HEIGHT	1000
#define fov			60

// DEBUG
#define ERROR		0
#define SUCCESS		1
#define FILEEND		0

// KEY
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2

# define KEY_LEFT	123
# define KEY_RIGHT	124

# define KEY_F		3
# define KEY_G		5
# define KEY_H		4

# define KEY_ESC	53

// WALL
# define WALL 		49 // ascii #1
# define NOT_WALL	48 // ascii #0
# define SPRITE		50 // ascii #2

// NSEW
# define NORTH		0
# define SOUTH		1
# define EAST		2
# define WEST		3

/*
** Center of the Projection Plane = (160,100)
** Distance to the Projection Plane = 277 units
** Angle between subsequent rays = 60/320 degrees
*/

typedef struct		s_plot
{
	double			x;
	double			y;
}					t_plot;

typedef struct		s_plot_int
{
	double			x;
	double			y;
}					t_plot_int;

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

typedef struct		s_wall
{
	double			length;
	double			height;
}					t_wall;

typedef struct		s_minimap
{
	t_plot			plot;
}					t_minimap;

typedef struct		s_sprite
{
	int				i; // ray 번호
	double			dist; // 플레이어와 sprite 거리 차이
}					t_sprite;


typedef struct		s_player
{
	// player figure
	int				width;
	int				height;
	int				color;

	// 화살표 각도(시야각)
	double			ang;
	double			projected_plane;

	// player 위치 <--- int로 바꿔야함
	t_plot			plot;
	char			facing;
}					t_player;

typedef struct		s_tex
{
	void			*ptr;
	int				*addr;
	int				bpp;
	int				len;
	int				endian;

	// xpm image size
	int				width;
	int				height;
}					t_tex;


typedef struct  	s_img
{
    void			*ptr;
    char			*addr; // 이 변수에 image 픽셀의 색을 넣어주는 것이 이미지를 만드는 것이다.
    int				bits_per_pixel;
    int				line_length;
    int				endian;

	int				x;
	int				y;
	int				tile_color;
}            	   t_img;

typedef struct				s_map_info
{
	// texture
	char					*NO_texture; // North texture
	char					*SO_texture; // South texture
	char					*WE_texture; // West wall texture
	char					*EA_texture; // East wall texture
	char					*sprite_texture; // sprite texture

	// FL RGB
	t_color					FL_RGB; // Floor color

	// CL RGB
	t_color					CL_RGB; // Ceiling color
}							t_map_info;

typedef struct		s_map
{
	char			**map;
	char			*map_1d;
	int				map_width;
	int				map_height;
	int				*curr_tex[5];
	t_map_info		info;
}					t_map;

typedef struct		s_ray
{
	t_plot			hit; // 벽에 부딛힌 좌표
	t_plot			wall; // hit 점이 위치한 wall의 왼쪽 위 좌표
	t_plot			spr_hit;
	t_plot			spr_map;
	double			scale_h;
	double			ang; // 플레이어 기준에서 ray 의 고유한 각도
	int				wall_NSEW; // 부딛힌 벽 방향 NO: 0, SO: 1, EA: 2, WE: 3
	double			ceiling;
	double			floor;
}					t_ray;


typedef struct 		s_win
{
	void			*mlx;
	void			*win;
	int				R_width;
	int				R_height;
	double			fov_ang;
	int				num_sprite;
	t_img			img;
	t_map			map;
	t_player		player;
	t_wall			wall;
	t_minimap		mini;
	t_tex			tex[5];
}					t_win;

int    				render_next_frame(t_win *w);

// bresenhem.c
void				draw_line(t_plot p1, t_plot p2, int color, t_win *w);

// map.c
int					is_wall(double x, double y, t_win *w);
// void				draw_rectangle(t_win *w, int x, int y, int color);
// void				draw_map(t_win *w);
void				map_init(t_win *w);
// void				draw_sprite_in_minimap(t_win *w);

// move.c
int					rotate_right(t_win *w);
int					rotate_left(t_win *w);
int					move_forward(t_win *w);
int					move_back(t_win *w);
int					move_left(t_win *w);
int					move_right(t_win *w);

// raycasting.c
int					cast_a_ray(t_ray *r, t_win *w);
int					cast_rays(t_win *w);

/*
** drawing files
*/

// draw_wall.c
void				draw_a_wall(int i, t_ray *r, t_win *w);

// draw_ceiling.c
void				draw_ceiling(int i, t_ray *r, t_win *w);

// draw_floor.c
void				draw_floor(int i, t_ray *r, t_win *w);

// draw_sprite.c
void				draw_a_sprite(int i, t_ray *r, t_win *w);

// player.c
int					draw_player(t_win *w);

// minimap.c
// void				draw_minimap(t_ray *r, t_win *w);
// int					draw_grid(t_win *w);

// utils.c
double				normalize_angle(double ang);
void				set_plot(t_plot *plot, double x, double y);
int					draw_background(t_win *w);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
void				save_plot(t_plot *dst_plot, t_plot *src_plot);
unsigned int		my_mlx_pixel_get(t_img *img, int x, int y);
int					color_rgb(int r, int g, int b);
int					safer_free_pp(void **pp);
int					safer_free_p(void *p);
int					ft_isspace(int c);
int					check_color(char **tmp);
void				error_handler(char *s, int num);

// screenshot.c
int					screenshot(t_win *w);
int					exit_game(t_win *w, int a);
int					exit_error(t_win *w, int a, char const *str);

void				file_parser(t_win *win, char *file);
void				map_validtator(t_win *win);
void				parse_resolution(t_win *win, char *line, char identifier);
void				parse_texture(t_win *win, char *line, char identifier);
void				parse_color(t_win *win, char *line, char identifier);
void				parse_map(t_win *win, t_list *lst);
static int			get_map_width(t_list *lst);

// sort_sprite.c
void				draw_sprites(t_sprite *spr, t_ray *r, t_win *w);
int					check_resol(char **tmp);

#endif