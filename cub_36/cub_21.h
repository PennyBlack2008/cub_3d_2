#ifndef _CUB_21_H_
# define _CUB_21_H_

#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// WIN SPEC
#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000
#define fov 60

// DEBUG
#define ERROR 0
#define SUCCESS 1
#define FILEEND 0

// KEY
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

// WALL
# define WALL 49 // ascii #1
# define NOT_WALL 48 // ascii #0

// NSEW
# define NORTH			0
# define SOUTH			1
# define EAST			2
# define WEST			3

/*
** Center of the Projection Plane = (160,100)
** Distance to the Projection Plane = 277 units
** Angle between subsequent rays = 60/320 degrees
*/

typedef struct	s_plot
{
	double		x;
	double		y;
}				t_plot;

typedef struct	s_plot_int
{
	double		x;
	double		y;
}				t_plot_int;

typedef struct			s_wall
{
	int					length;
	int					height;
}						t_wall;

typedef struct	s_minimap
{
	t_plot		plot;
}				t_minimap;

typedef struct			s_player
{
	// player figure
	int					width;
	int					height;
	int					color;

	// 화살표 각도(시야각)
	double				ang;
	double				projected_plane;

	// player 위치 <--- int로 바꿔야함
	int					x;
	int					y;
	char*				str_KEY_W; // 빨간색 끝에 적어줄 글자
	char*				str_KEY_D; // 파란색 끝에 적어줄 글자
}						t_player;

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

typedef struct  s_img
{
    void        *ptr;
    char        *addr; // 이 변수에 image 픽셀의 색을 넣어주는 것이 이미지를 만드는 것이다.
    int         bits_per_pixel;
    int         line_length;
    int         endian;

	int			x;
	int			y;
	int			tile_color;
}               t_img;

typedef struct	s_map
{
	char		**map;
	int			i;
	int			j;
	int			*curr_tex;
}				t_map;

typedef struct	s_ray
{
	t_plot_int	hit; // 벽에 부딛힌 좌표
	t_plot_int	wall; // hit 점이 위치한 wall의 왼쪽 위 좌표
	double		ang; // 플레이어 기준에서 ray 의 고유한 각도
	int			wall_NSEW; // 부딛힌 벽 방향 NO: 0, SO: 1, EA: 2, WE: 3
	int			ceiling;
	int			floor;
}				t_ray;


typedef struct 			s_win
{
	void				*mlx;
	void				*win;
	int					R_width;
	int					R_height;
	double				fov_ang;
	t_img				img;
	t_map				map;
	t_player			player;
	t_wall				wall;
	t_minimap			mini;
	t_tex				tex;
}						t_win;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color);
int						draw_player(t_win *w);
int						draw_grid(t_win *w);
int						draw_background(t_win *w);
void					draw_line(t_plot p1, t_plot p2, int color, t_win *w);
void					map_init(t_win *w);
void					draw_map(t_win *w);
void					draw_rectangle(t_win *w, int x, int y, int color);
int						is_wall(double x, double y, t_win *w);
int						rotate_right(t_win *w);
int						rotate_left(t_win *w);
int						move_forward(t_win *w);
int						move_back(t_win *w);
int						move_left(t_win *w);
int						move_right(t_win *w);
int						draw_a_ray(t_ray *r, t_win *w);
int						draw_rays(t_win *w);
void					draw_a_wall(int i, t_ray *r, t_win *w);
void					draw_minimap(t_ray *r, t_win *w);
void					draw_ceiling(int i, t_ray *r, t_win *w);
void					draw_floor(int i, t_ray *r, t_win *w);
double					normalize_angle(double ang);
void					set_plot_int(t_plot *plot, int x, int y);
int						get_which_wall(t_ray *r, t_win *w);

#endif