#include <stdio.h>
#include "../minilibx/mlx.h"
#include "../libft/libft.h"
#include <math.h>

typedef struct		s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				len;
	int				endian;

	// for xpm image
	int				width;
	int				height;
}					t_img;

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

typedef struct		s_win
{
	void			*mlx;
	void			*ptr;
	t_img			img;
	t_tex			tex[2];
	int				*curr_tex[2];
}					t_win;

void					my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char				*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
	printf("%d\n", color);
}

int					get_color_tex(double x, double y, double scale_w, double scale_h, t_win *w, int k)
{
	int				color;
	double			px, py;

	px = floor(x / scale_w);
	py = floor(y / scale_h);
	color = w->curr_tex[k][(int)(w->tex[k].height * py + px)];
	return (color);
}

int					main()
{
	t_win			win;
	int				i, j; // 텍스쳐 추출 while 용
	int				k;
	double			scale_w, scale_h;
	int				color;

	// window 설정
	win.mlx = mlx_init();
	win.ptr = mlx_new_window(win.mlx, 500, 500, "veryluckymanjinwoo");

	// 첫 번째 이미지(화면 전체 담당)
	win.img.ptr = mlx_new_image(win.mlx, 500, 500);
	win.img.addr = mlx_get_data_addr(win.img.ptr, &win.img.bpp, &win.img.len, &win.img.endian);

	k = 0;
	while (k < 2)
	{
		// 두 번째 이미지(텍스쳐 이미지 받아오는 것 담당): 이미지 값을 win.curr_tex에 저장하고 win.tex.ptr 은 폐기
		if (k == 0)
			win.tex[k].ptr = mlx_xpm_file_to_image(win.mlx, "wall_1.xpm", &win.tex[k].width, &win.tex[k].height);
		if (k == 1)
			win.tex[k].ptr = mlx_xpm_file_to_image(win.mlx, "pillar.xpm", &win.tex[k].width, &win.tex[k].height);
		win.tex[k].addr = (int *)mlx_get_data_addr(win.tex[k].ptr, &win.tex[k].bpp, &win.tex[k].len, &win.tex[k].endian);

		win.curr_tex[k] = (int *)ft_calloc((win.tex[k].height * win.tex[k].width), sizeof(int));
		i = 0;
		while (i < win.tex[k].height)
		{
			j = 0;
			while (j < win.tex[k].width)
			{
				win.curr_tex[k][(int)win.tex[k].width * i + j] = win.tex[k].addr[(int)win.tex[k].width * i + j];
				j++;
			}
			i++;
		}
		mlx_destroy_image(win.mlx, win.tex[k].ptr);
		k++;
	}

	// 두 번째 이미지를 윈도우에 출력해보기
	k = 0;
	scale_w = 2;	scale_h = 2;
	i = 0;
	while (i < win.tex[k].width * scale_w) // width
	{
		j = 0;
		while (j < win.tex[k].height * scale_h) // height
		{
			color = get_color_tex(i, j, scale_w, scale_h, &win , 0);
			my_mlx_pixel_put(&win.img, i, j, color);
			j++;
		}
		i++;
	}

	k = 1;
	// 두 번째 이미지를 윈도우에 출력해보기
	scale_w = 2;	scale_h = 2;
	i = 0;
	while (i < win.tex[k].width * scale_w) // width
	{
		j = 0;
		while (j < win.tex[k].height * scale_h) // height
		{
			color = get_color_tex(i, j, scale_w, scale_h, &win, 1);
			if (color != 0)
				my_mlx_pixel_put(&win.img, i, j, color);
			j++;
		}
		i++;
	}

	mlx_put_image_to_window(win.mlx, win.ptr, win.img.ptr, 0, 0);
	mlx_loop(win.mlx);

	return (0);
}
