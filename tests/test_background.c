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
	g.cfg.ceiling = (225 << 16) | (30 << 8);
	g.cfg.floor = (220 << 16) | (100 << 8);
	if (init_window(&g))
		return (free_game(&g), 1);
	draw_background(&g);
	fails = 0;
	fails += check("ceiling top-left", get(&g, 0, 0) == (unsigned)g.cfg.ceiling);
	fails += check("ceiling top-right", get(&g, WIN_W - 1, 0)
			== (unsigned)g.cfg.ceiling);
	fails += check("last ceiling row", get(&g, 640, WIN_H / 2 - 1)
			== (unsigned)g.cfg.ceiling);
	fails += check("first floor row", get(&g, 640, WIN_H / 2)
			== (unsigned)g.cfg.floor);
	fails += check("floor bottom-right", get(&g, WIN_W - 1, WIN_H - 1)
			== (unsigned)g.cfg.floor);
	free_game(&g);
	printf("background test: %s\n", fails ? "FAILED" : "ok");
	return (fails != 0);
}
