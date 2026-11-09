#include "cub3d.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>

/* first fields of MiniLibX's internal t_xvar / t_win_list (mlx_int.h clashes with our t_img) */
typedef struct s_xv
{
	Display	*display;
}			t_xv;

typedef struct s_wl
{
	Window	window;
}			t_wl;

/* queue fake events, run the real loop: it must return, and free_game must leave no leak */
static void	push_key(t_game *g, int keysym)
{
	XEvent	ev;
	Display	*d;

	d = ((t_xv *)g->mlx)->display;
	ft_bzero(&ev, sizeof(ev));
	ev.type = KeyPress;
	ev.xkey.display = d;
	ev.xkey.window = ((t_wl *)g->win)->window;
	ev.xkey.keycode = XKeysymToKeycode(d, keysym);
	XPutBackEvent(d, &ev);
}

static void	push_close(t_game *g)
{
	XEvent	ev;
	Display	*d;

	d = ((t_xv *)g->mlx)->display;
	ft_bzero(&ev, sizeof(ev));
	ev.type = DestroyNotify;
	ev.xdestroywindow.display = d;
	ev.xdestroywindow.window = ((t_wl *)g->win)->window;
	ev.xdestroywindow.event = ev.xdestroywindow.window;
	XPutBackEvent(d, &ev);
}

static int	run(char *name, int mode)
{
	t_game	g;

	init_game(&g);
	if (init_window(&g))
		return (1);
	if (mode == 0)
	{
		push_key(&g, XK_Escape);
		push_key(&g, XK_a);
	}
	else if (mode == 1)
		push_close(&g);
	run_game(&g);
	free_game(&g);
	printf("%s: loop ended, freed\n", name);
	return (0);
}

int	main(void)
{
	return (run("ESC key", 0) || run("window close", 1));
}
