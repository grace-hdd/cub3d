# explain/

One file per finished task of `PLAN.md`. Each explains how that task's code works and why.
Add a new file here when a task is merged (name it `<id>-<name>.md`).

| File | Task |
|---|---|
| [0.1-skeleton.md](0.1-skeleton.md) | Repo skeleton, Makefile, `.gitignore` |
| [0.2-get_next_line.md](0.2-get_next_line.md) | `get_next_line` |
| [0.3-structs.md](0.3-structs.md) | Header, includes and shared structs |
| [0.4-layout-and-cleanup.md](0.4-layout-and-cleanup.md) | Directory layout, `print_error`, `init_game`, `free_game` |
| [1.1-check-args.md](1.1-check-args.md) | Argument check |
| [1.2-read-file.md](1.2-read-file.md) | Read the file into lines |
| [1.3-textures.md](1.3-textures.md) | Parse `NO SO WE EA` |

Note about norminette: the 42 header was removed from our files on purpose, so `norminette` reports `INVALID_HEADER`. Every other norm error is still checked.
