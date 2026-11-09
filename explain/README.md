# explain/

One file per finished task of `PLAN.md`. Each explains how that task's code works and why.
Add a new file here when a task is merged (name it `<id>-<name>.md`).

| File | Task | Done by |
|---|---|---|
| [0.1-skeleton.md](0.1-skeleton.md) | Repo skeleton, Makefile, `.gitignore` | Abdullah |
| [0.2-get_next_line.md](0.2-get_next_line.md) | `get_next_line` | Abdullah |
| [0.3-structs.md](0.3-structs.md) | Header, includes and shared structs | Abdullah |
| [0.4-layout-and-cleanup.md](0.4-layout-and-cleanup.md) | Directory layout, `print_error`, `init_game`, `free_game` | Abdullah |
| [1.1-check-args.md](1.1-check-args.md) | Argument check | Abdullah |
| [1.2-read-file.md](1.2-read-file.md) | Read the file into lines | Abdullah |
| [1.3-textures.md](1.3-textures.md) | Parse `NO SO WE EA` | Abdullah |
| [1.4-colors.md](1.4-colors.md) | Parse `F` and `C` | Grace |
| [1.5-elements.md](1.5-elements.md) | Find the map start, require all 6 elements | Abdullah |
| [1.6-map.md](1.6-map.md) | Copy and validate the map grid | Grace |
| [1.7-cleanup.md](1.7-cleanup.md) | Parser review fixes | Grace |
| [2.1-player.md](2.1-player.md) | Find and validate the player spawn | Grace |
| [2.2-closed-map.md](2.2-closed-map.md) | Check the map is closed | Abdullah |
| [2.3-parsing-tests.md](2.3-parsing-tests.md) | Test maps and `tests/run_parsing.sh` | Abdullah |
| [3.1-window.md](3.1-window.md) | Window, image buffer, `put_pixel` | Abdullah |
| [4.1-player-view.md](4.1-player-view.md) | Set the player position, direction and camera plane | Grace |

Note about norminette: Grace's files carry the 42 header; Abdullah's files (tasks 0.x-1.5, `check_map.c`, `window.c`) do not, so `norminette` reports `INVALID_HEADER` on those. Every other norm error is still checked. With that header exception, `norminette src inc` is clean. "Done by" matches the Progress table in `PLAN.md`.
