# CODE.md – How the code written so far works

This file explains every file we have so far (tasks 0.1 to 1.1) and why each `#include` is there.

## Folder layout

```
inc/cub3d.h                  the only header: includes, structs, prototypes
src/main.c                   program entry point
src/parsing/check_args.c     task 1.1: check the command line
src/parsing/read_file.c      task 1.2: read the .cub file into lines
src/utils/error.c            error message, init and free of the game struct
src/utils/get_next_line.c    reads a file line by line
src/utils/get_next_line_utils.c   helper used by get_next_line
libft/                       our libft (not touched)
minilibx-linux/              the graphics library
tests/maps/                  test maps
```

## The includes in `inc/cub3d.h`

| Include | Why we need it |
|---|---|
| `<stdlib.h>` | `malloc`, `free`, `exit`, `size_t` |
| `<unistd.h>` | `read`, `write`, `close` |
| `<fcntl.h>` | `open` and the `O_RDONLY` flag |
| `<stdio.h>` | `printf` (allowed by the subject, useful for debugging) |
| `<math.h>` | `sin`, `cos`, `sqrt`, `fabs` for the raycasting (needs `-lm` at link time) |
| `"libft.h"` | our own helpers: `ft_strlen`, `ft_strncmp`, `ft_putstr_fd`, `ft_bzero`, `ft_strdup`, `ft_substr`, `ft_calloc`, ... |
| `"mlx.h"` | MiniLibX: window, image and key functions (used from Phase 3) |

Because every `.c` file only includes `cub3d.h`, each of them gets all of these automatically.

The header is wrapped in `#ifndef CUB3D_H ... #endif` (an *include guard*). If two files include it, the second inclusion is skipped, so the structs are not defined twice.

`BUFFER_SIZE` is defined with `#ifndef`, so it has a default of 42 but can be changed at compile time with `-D BUFFER_SIZE=...`.

## The structs

- `t_config`: what the `.cub` file says about looks. `tex[4]` holds the four texture paths (indexes `NO`, `SO`, `WE`, `EA`). `floor` and `ceiling` hold the colors as one int (`R << 16 | G << 8 | B`). Both start at `-1`, which means "not set yet". That is how we will detect a missing or duplicated `F`/`C` line.
- `t_map`: `grid` is an array of strings (one per row), `width` and `height` are its size. The grid will be rectangular, short rows padded with spaces.
- `t_player`: position `x`, `y`; direction `dir_x`, `dir_y`; camera plane `plane_x`, `plane_y` (used by the raycaster); `spawn` is the original character (`N/S/E/W`).
- `t_game`: groups the three above, plus `lines` (the raw lines of the `.cub` file, NULL-terminated) and `nb_lines`. Later it will also hold the mlx pointers. We pass one `t_game *` around instead of many arguments.

## `src/main.c`

```c
int main(int argc, char **argv)
{
	t_game	game;

	if (check_args(argc, argv))   // 1.1: bad arguments -> message printed, exit 1
		return (1);
	init_game(&game);             // zero everything, colors = -1
	free_game(&game);             // nothing allocated yet, but this is the cleanup pattern
	return (0);
}
```

Later phases will add parsing, the window and the game loop between `init_game` and `free_game`. Every error path must end with `free_game`.

## `src/parsing/check_args.c` (task 1.1)

`check_args` runs three checks in order and stops at the first failure:

1. **`argc != 2`**: the program name plus exactly one argument.
2. **`has_cub_extension`**: the path must be longer than 4 characters and its last 4 characters must be `.cub`. So `.cub` alone is rejected, and so is `map.txt`. It compares with `ft_strncmp(path + len - 4, ".cub", 4)`: pointer arithmetic jumps to the last 4 characters.
3. **`can_read_file`**: `open` with `O_RDONLY` fails if the file does not exist or has no permission. Opening a **directory** succeeds in Linux, so we also try `read(fd, &c, 1)`: on a directory it returns `-1`, on a normal file (even an empty one) it returns `>= 0`. We close the fd right away. The file is opened again later by the real parser, so no fd is leaked here.

On failure, `print_error` is called and its return value `1` is passed up.

## `src/parsing/read_file.c` (task 1.2)

`read_file(path, game)` loads the whole file into `game->lines`, one string per line, **without the trailing `\n`**. Blank lines are kept as empty strings `""`, so later tasks can tell where the map has a hole.

It reads the file **twice** (we have no linked list, and `realloc` is not allowed):

1. `count_lines` reads with `get_next_line` until it returns `NULL`, counting lines and freeing each one.
2. `read_file` allocates `nb_lines + 1` pointers with `ft_calloc` (the last one stays `NULL`), then `fill_lines` opens the file again and stores each line, calling `strip_newline` first.

Errors: a file that cannot be opened gives `cannot read the map file`; a file with zero lines gives `the map file is empty`; a failed `ft_calloc` gives `memory allocation failed`. A file holding only `"\n"` is **not** empty: it is one blank line, and the later parsing tasks will reject it because the elements are missing.

`fill_lines` frees any leftover line and calls `get_next_line(-1)` at the end, so the static buffer inside GNL is always released. `free_game` frees `lines`, and because `ft_calloc` zeroed the array, it is safe even if filling stopped halfway (`nb_lines` is set before filling).

In `main`, `read_file` runs right after `init_game`; on failure we call `free_game` and exit with 1.

## `src/utils/error.c`

- `print_error(msg)`: writes `Error\n` then the message to **stderr** (fd 2), returns `1`. Returning 1 lets us write `return (print_error("..."))` in one line. The subject requires the first line to be exactly `Error`.
- `init_game(game)`: `ft_bzero` sets every byte to 0 (pointers become `NULL`, numbers 0), then the two colors are set to `-1`.
- `free_game(game)`: frees the raw `lines`, the 4 texture paths and every row of the grid, then the grid itself, and sets pointers to `NULL`. Freeing `NULL` is safe, so this function can be called at any moment, even on a half-filled struct. That is why it is the single cleanup for every error path.

## `src/utils/get_next_line.c` and `get_next_line_utils.c`

`get_next_line(fd)` returns the next line **including its `\n`**, or `NULL` at the end of the file (or on error). A `static char *line` keeps the text that was read but not yet returned, between calls.

- `readfd`: reads `BUFFER_SIZE` bytes at a time and appends them to `line` with `ft_strjoin_gnl` until `line` contains a `\n` or the file ends.
- `init`: checks `fd` and `BUFFER_SIZE`, creates the empty string on the first call, then calls `readfd`.
- `split_current`: cuts `line` at the first `\n`. The first part (with the `\n`) is returned; the rest stays in the static variable. With no `\n` (last line) the whole thing is returned and the static is set to `NULL`.
- `get_next_line(-1)`: special call that frees the static buffer. Use it if we stop reading before the end of the file (for example on an error in the middle of parsing), otherwise that memory leaks.
- `ft_strjoin_gnl(s1, s2)`: like `ft_strjoin` but it **frees `s1`**, so `line = ft_strjoin_gnl(line, buf)` does not leak the old string.

Blank lines are returned as `"\n"`. We rely on this: the map must not contain empty lines, so the parser has to see them.

## The Makefile in short

- `-Iinc -Ilibft -Iminilibx-linux` tells the compiler where to find `cub3d.h`, `libft.h` and `mlx.h`.
- `libft.a` and `libmlx.a` are built by calling `make -C` on their folders. MiniLibX is built with `CC="cc -std=gnu17"` because its old code does not compile with the newest gcc default.
- `-lXext -lX11 -lm` link the X11 libraries MiniLibX needs and the math library.
- Object files go to `obj/`, mirroring the `src/` folders. Each `.o` depends on `inc/cub3d.h`, so changing the header recompiles everything. Running `make` twice does not relink.

## Note about norminette

The 42 header was removed from our files on purpose, so `norminette` reports `INVALID_HEADER` on them. Every other norm error is still checked, so read its output for anything that is not `INVALID_HEADER`.
