#include "cub3d.h"

static unsigned int	get(t_game *g, int x, int y)
{
	return (*(unsigned int *)(g->img.addr + y * g->img.line_len
		+ x * (g->img.bpp / 8)));
}

static int	check(char *name, int ok)
{
	if (!ok)
		printf("FAIL %s\n", name);
	return (!ok);
}

int	main(void)
{
	t_game	g;
	int		fails;

	init_game(&g);
	if (init_window(&g))
		return (free_game(&g), 1);
	fails = 0;
	put_pixel(&g.img, 0, 0, 0xFF0000);
	put_pixel(&g.img, WIN_W - 1, WIN_H - 1, 0x00FF00);
	put_pixel(&g.img, 640, 360, 0x0000FF);
	fails += check("top-left", get(&g, 0, 0) == 0xFF0000);
	fails += check("bottom-right", get(&g, WIN_W - 1, WIN_H - 1) == 0x00FF00);
	fails += check("center", get(&g, 640, 360) == 0x0000FF);
	fails += check("neighbor untouched", get(&g, 1, 0) == 0);
	put_pixel(&g.img, -1, 0, 0xFFFFFF);
	put_pixel(&g.img, 0, -1, 0xFFFFFF);
	put_pixel(&g.img, WIN_W, 0, 0xFFFFFF);
	put_pixel(&g.img, 0, WIN_H, 0xFFFFFF);
	fails += check("out of bounds ignored", get(&g, 0, 0) == 0xFF0000
			&& get(&g, WIN_W - 1, 0) == 0 && get(&g, 0, WIN_H - 1) == 0);
	mlx_put_image_to_window(g.mlx, g.win, g.img.ptr, 0, 0);
	free_game(&g);
	printf("pixel test: %s\n", fails ? "FAILED" : "ok");
	return (fails != 0);
}
