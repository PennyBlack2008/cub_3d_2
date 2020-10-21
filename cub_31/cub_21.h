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
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define fov 60

// DEBUG
# define ERROR 0
# define SUCCESS 1
# define FILEEND 0

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
# define WALL			49 // ascii #1
# define NOT_WALL		48 // ascii #0

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

typedef struct	s_wall
{
	double		length; // 가로, 세로 같도록 똑같은 변수 사용!
	int			height;
}				t_wall;


typedef struct	s_ray
{
	double		ang;
	double		x;
	double		y;

	int		floor;
	int		ceiling;
}				t_ray;

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
	int					pdi;
	int					pdj;

	// player 위치
	int					x;
	int					y;
	char*				str_KEY_W; // 빨간색 끝에 적어줄 글자
	char*				str_KEY_D; // 파란색 끝에 적어줄 글자
}						t_player;

typedef struct  s_img
{
    void        *ptr;
    char        *addr; // 이 변수에 image 픽셀의 색을 넣어주는 것이 이미지를 만드는 것이다.
    int         bits_per_pixel;
    int         line_length;
    int         endian;

	// for image size
	int			width;
	int			height;

}               t_img;

typedef struct	s_map
{
	char		**map;
	int			i;
	int			j;
}				t_map;


typedef struct 			s_win
{
	void				*mlx;
	void				*win;
	int					R_width;
	int					R_height;
	t_img				img;
	t_map				map;
	t_player			player;
	t_wall				wall;
	t_minimap			mini;
}						t_win;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color);
int						draw_player(t_win *w);
int						draw_background(t_win *w);
void					draw_line(int p1_x, int p1_y, int p2_x, int p2_y, int color, t_win *w);
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
int						cast_a_ray(t_win *w, t_ray *r);
int						cast_rays(t_win *w);
void					draw_wall(int i, t_ray *r, t_win *w);
void					draw_minimap(t_ray *r, t_win *w);
void					draw_ceiling(int i, t_ray *r, t_win *w);
void					draw_floor(int i, t_ray *r, t_win *w);

#endif