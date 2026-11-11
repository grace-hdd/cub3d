#include "cub3d.h"

/* hard-coded 7x7 room; the player stands inside, nothing is parsed or drawn */
static char	g_rows[7][8] = {"1111111", "1000001", "1000001", "1000001",
	"1000001", "1000001", "1111111"};
static char	*g_grid[7];
static int	g_fails;

static void	setup(t_game *g, double x, double y, char spawn)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		g_grid[i] = g_rows[i];
		i++;
	}
	ft_bzero(g, sizeof(t_game));
	g->map.grid = g_grid;
	g->map.width = 7;
	g->map.height = 7;
	g->player.x = x - 0.5;
	g->player.y = y - 0.5;
	g->player.spawn = spawn;
	init_player_view(g);
}

static void	expect(char *name, t_ray *r, double dist, int side)
{
	int	ok;

	ok = fabs(r->perp_dist - dist) < 1e-9 && r->side == side;
	printf("%-26s hit=(%d,%d) side=%d dist=%.6f  %s\n", name, r->map_x,
		r->map_y, r->side, r->perp_dist, ok ? "ok" : "FAIL");
	g_fails += !ok;
}

static void	test_directions(void)
{
	t_game	g;
	t_ray	r;
	char	*names[4] = {"N center ray", "S center ray", "E center ray",
		"W center ray"};
	char	spawn[4] = {'N', 'S', 'E', 'W'};
	int		i;

	i = 0;
	while (i < 4)
	{
		setup(&g, 3.5, 3.5, spawn[i]);
		cast_ray(&g, WIN_W / 2, &r);
		expect(names[i], &r, 2.5, i < 2);
		i++;
	}
}

static void	test_edges(void)
{
	t_game	g;
	t_ray	r;
	int		x;
	int		flat;

	setup(&g, 1.5, 3.5, 'N');
	cast_ray(&g, 0, &r);
	expect("left col, near west wall", &r, 0.5 / 0.66, 0);
	cast_ray(&g, WIN_W - 1, &r);
	expect("right col, near west wall", &r, 2.5, 1);
	setup(&g, 3.5, 3.5, 'N');
	x = 0;
	flat = 1;
	while (x < WIN_W)
	{
		cast_ray(&g, x, &r);
		flat &= fabs(r.perp_dist - 2.5) < 1e-9 && r.side == 1;
		x++;
	}
	printf("%-26s all %d columns 2.5 (no fisheye)  %s\n", "flat wall", WIN_W,
		flat ? "ok" : "FAIL");
	g_fails += !flat;
}

int	main(void)
{
	test_directions();
	test_edges();
	printf("dda test: %s\n", g_fails ? "FAILED" : "ok");
	return (g_fails != 0);
}
