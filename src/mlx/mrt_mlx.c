#include "mrt_error.h"
#include "mrt_render.h"

static bool	free_launch(t_mrt *v, bool destroy_windows)
{
	if (destroy_windows == true)
		mlx_destroy_window(v->mlx_ptr, v->mlx_win);
	free(v->mlx_ptr);
	return (error_bool(ERR_MLX));
}

bool	init_mrt_mlx(t_mrt *v)
{
	v->mlx_ptr = mlx_init();
	if (v->mlx_ptr == NULL)
		return (error_bool(ERR_MLX));
	v->mlx_win = mlx_new_window(v->mlx_ptr, SCR_WID, SCR_HGH, "RT");
	if (v->mlx_win == NULL)
		return (free_launch(v, false));
	v->mlx_img.img = mlx_new_image(v->mlx_ptr, SCR_WID, SCR_HGH);
	if (v->mlx_img.img == NULL)
		return (free_launch(v, true));
	v->mlx_img.addr = mlx_get_data_addr(v->mlx_img.img, &v->mlx_img.bpp, \
		&v->mlx_img.ll, &v->mlx_img.ed);
	return (true);
}
