/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:27:22 by pchennia          #+#    #+#             */
/*   Updated: 2024/11/07 13:31:38 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>

# define WIN_WIDTH 1080
# define WIN_HEIGHT 1000

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

# define GO_RIGHT 1
# define GO_LEFT 2
# define GO_FORWARD 4
# define GO_BACKWARD 8
# define LOOK_RIGHT 16
# define LOOK_LEFT 32

# define TURN 0.05
# define SPEED 10
# define SENSITIVITY 0.05f

# define NONE 0xFF000000
# define BLACK 0x00000000

// Bitmask flags for each setting
# define NO_FLAG  1
# define SO_FLAG  2
# define WE_FLAG  4
# define EA_FLAG  8
# define F_FLAG   16
# define C_FLAG   32

# define LIST_INITIAL_SIZE 1000
# define VALID_CHARS "10NWES"
# define PLAYER_ORIENTATION_CHARS "NWES"
# define STOP_READING 5
# define CLEAN_LINE 1

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture
{
	char			*path;
	void			*image;
}	t_texture;

typedef struct s_temp_data
{
	int				fd;
	int				flags;
	void			*mlx;
	t_texture		textures_info[4];
	char			*path_name;
	int				has_start;
	int				successful;
}	t_temp_data;

typedef struct s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	c;		
	unsigned int	f;		
}	t_tex;

typedef struct s_win
{
	void	*ptr;	
	int		x;		
	int		y;		
}	t_win;

typedef struct s_img
{
	void			*ptr;
	unsigned int	*adr;
}	t_img;

typedef struct s_map
{
	char		**tab;
	int			x;
	int			y;
}	t_map;

typedef struct s_ray
{
	double		x;	
	double		y;	
	int			angle_index;
	double		v;	
	double		h;	
}	t_ray;

typedef struct s_hit
{
	double		x;	
	double		y;	
	double		d;	
}	t_hit;

typedef struct s_stk
{
	double			x;
	double			y;
}	t_stk;

typedef struct s_dir
{
	double			x;
	double			y;
}	t_dir;

typedef struct s_all
{
	double		pos_x;
	double		pos_y;
	void		*mlx;
	t_win		win;
	t_img		img;
	t_map		map;
	int			key_control;
	t_ray		ray;
	t_hit		hit;
	t_stk		*stk;
	t_tex		tex;
	t_dir		dir;
	t_temp_data	temp_data;
}	t_all;

//parser
int				parse_data(t_all *datca, char *path);
int				parse_map(t_all *data, int fd);
int				store_settings(t_all *data, char **line);
int				store_texture(t_temp_data *data, char **line,
					int texture_index, const char *keyword);
int				read_texture(t_all *data, t_temp_data *temp);
int				store_color(t_all *data, char **line,
					int color_index, const char *keyword);
int				validate_and_clean(char **input_string, const char *keyword);
int				get_direction(char special_char, t_all *data, ssize_t pos_x);
int				map_contained(t_all *data);
int				contains_spaces(const char *str);
int				valid_name(char *str);

//utils
char			*cub_get_next_line(int fd, int action);
size_t			ft_count_words(char const *str, char sep);
size_t			ft_strclen(const char *str, char cond);
int				put_error(char *error_msg, char *additonal, int exit_code);

//memory
void			del_data(t_all *data);

//utils.c
int				close_window(t_all *data);

				/* RENDERING */
//key.c
int				key_hold(int key, void *arg);
int				key_release(int key, void *arg);
void			rotate_left_right(t_all *data, double c);
void			move_forward_or_back(t_all *data, double c);
void			move_left_or_right(t_all *data, double c);

// movement.c
void			display_screen(t_all *s);
int				movement(t_all *data);

// screen.c
unsigned int	get_wall_tex_color(t_all *s, double i);
void			display_vertical_wall_section(t_all *s, int size);
int				height_of_wall(t_all *s);

// ray.c
void			init_ray(t_all *data);
void			calculate_ray_vector(t_all *data);
void			identify_ray_direction(t_all *data);
void			find_vertical_wall_hit(t_all *data);
void			find_horizontal_wall_hit(t_all *data);

// init.c
void			init_struct1(t_all *data);
void			init_struct2(t_all *data);
int				init_window(t_all *data);

#endif