# cub3D – Team Plan

**Team:** Abdullah and Grace
**Scope:** mandatory part first. The bonus is decided only after the mandatory part is perfect (Phase 9).
**Deadline:** none fixed. We work phase by phase.

## Working rules
- **Pair on everything.** Each task has a driver (writes and commits) and a navigator (reads, questions, tests). The driver alternates as listed below.
- **One git branch per task:** `task/<id>-<name>` (e.g. `task/2.1-player`). Merge into `main` only when the task's "Done when" is met.
- **Before every merge:** `norminette src inc` shows no errors (except `INVALID_HEADER` on files without the 42 header; Grace's files have it, Abdullah's do not: decide one rule), `make` builds with `-Wall -Wextra -Werror`, no leaks.
- **Understand before you merge.** If code was written with help (a teammate, a peer, or an AI tool), both of us must be able to explain every line. This is a graded rule.
- **Leaks:** valgrind does not start on Abdullah's machine (glibc too new), so our test scripts (`tests/run_parsing.sh`, `tests/test_pixel.c`) compile with AddressSanitizer (`-fsanitize=address`). Do a final valgrind run on a school machine.

## Progress (who finished what)
Updated from `git log`. "Planned" is the driver in the phase tables; the last column is who actually did it.
| Task | Planned | Done by | Notes |
|---|---|---|---|
| 0.1-0.4 | Abdullah | Abdullah | |
| 1.1-1.3 | Abdullah | Abdullah | |
| 1.4 colors | Grace | Grace | Abdullah fixed the Makefile, the wiring and the digit overflow |
| 1.5 elements | Abdullah | Abdullah | |
| 1.6 map grid | Grace | Grace | Abdullah removed an unused variable (build), ignored trailing blank lines |
| 1.7 cleanup | Grace | Grace | Abdullah: `\r` strip in `read_file.c`, `parse_map.c` split for the norm |
| 2.1 player | Grace | Grace | |
| 2.2 closed map | Abdullah | Abdullah | |
| 2.3 tests | Grace | **Abdullah** | reassigned: Abdullah wrote the maps and `tests/run_parsing.sh` |
| 3.1 window | Abdullah | Abdullah | |
| 3.2 background | Grace | **Abdullah** | reassigned at Grace's turn; done after 3.3 |
| 3.3 clean exit | Abdullah | Abdullah | |
| 4.1 player view | Grace | Grace | done early, before Phase 3 |
| 4.2 DDA | Abdullah | Abdullah | |

Count: 19 of 33 tasks done (Abdullah 14, Grace 5). Left: Abdullah 6 (5.1, 5.3, 6.2, 6.4, 7.2, 7.4), Grace 7 (4.3, 5.2, 6.1, 6.3, 7.1, 7.3, 8.1), both 1 (8.2). Next: 4.3 (Grace, needs 4.2's `cast_ray`) and 5.1 (Abdullah).

## Open issues
- ~~norminette~~ fixed: `parse_map.c` split into `parse_map.c` + `parse_map_utils.c`, `player_view.c` header realigned, CRLF line endings removed from 3 files. `norminette src inc` now reports only `INVALID_HEADER` (on files without the 42 header).
- Header rule is inconsistent (see Working rules).
- Final valgrind run on a school machine (valgrind does not start here).
- `tests/maps/{empty,sample,valid_min}.cub` are old stubs and unused: delete or reuse.

## Phase 0 – Project setup (added after review)
The repo had gaps that block every later phase: `cub3d.h` sat in the root while the Makefile and norminette use `inc/`, `main.c` was empty, libft had no `get_next_line`, and MLX does not compile with a new gcc (C23 default).
| ID | Task | Driver | Done when |
|---|---|---|---|
| 0.1 | Repo skeleton: move the header to `inc/cub3d.h` (with include guards), minimal `main.c`, `.gitignore` (objects, `libft.a`, MLX build files, binary), `tests/maps/`, Makefile fixes (`-Iinc`, MLX built with `CC="cc -std=gnu17"`) | Abdullah | `make` builds `cub3D` from clean, `make` again does not relink, `git status` shows no build files ✅ **DONE (Abdullah)** |
| 0.2 | Add `get_next_line` (in `src/utils/`, reusing libft functions, no duplicates). Used to read the `.cub` file. The `ft_lst*` bonus functions are not needed and were not added | Abdullah | `libft.a` builds, GNL works on a file, stdin and an empty file with no leaks ✅ **DONE (Abdullah)** |
| 0.3 | Shared structs in `inc/cub3d.h`: `t_config` (paths, colors), `t_map` (grid, width, height), `t_player`, `t_game`. Agree on them together before Phases 1 and 3 start | Abdullah | both agree; header passes norminette ✅ **DONE (Abdullah)** |
| 0.4 | Directory layout: `src/parsing/`, `src/render/`, `src/utils/` (norm: max 5 functions per file, max 25 lines per function) and a central `free_all` / `error_exit` helper | Abdullah | Makefile lists all files; helper frees everything on any error path ✅ **DONE (Abdullah)** |

Notes for the next phases (from what 0.1-1.1 taught us):
- Every error path must end in `free_game`, and `get_next_line(-1)` must be called if we stop reading before the end of the file (it frees the static buffer).
- Blank lines come back from GNL as `"\n"`, so the parser can see them (needed to reject empty lines inside the map).
- Each new parsing task should come with its own test script and maps in `tests/` (the old `run_args.sh` was deleted; recreate a single `tests/run_parsing.sh` that covers 1.x and 2.x).
- Norm limits: max 25 lines per function, max 5 functions per file, max 4 parameters. Plan files accordingly (e.g. `parse_texture.c`, `parse_color.c`, `parse_map.c`).
- `parse_elements` (1.5) is the parsing entry point called by `main`; 1.6 and 2.x are added after it. Element lines after the map start are rejected there, but bad characters and empty lines inside the map are 1.6's job.
- Color values take 1-3 digits only (`ft_atoi` has no overflow guard); `0000` is rejected on purpose.
- Document each task in its own file in `explain/` (`<id>-<name>.md`) when it is merged.

## Phase 1 – Parsing the config
| ID | Task | Driver | Done when |
|---|---|---|---|
| 1.1 | Argument check: exactly 1 argument, `.cub` extension, file can be opened | Abdullah | bad arguments give `Error\n` + a message (tested by hand with 8 cases: no arg, 2 args, bad extension, `.cub`, missing file, directory, valid file) ✅ **DONE (Abdullah)** |
| 1.2 | Read the file into lines (using GNL from 0.2), keeping blank lines; reject an empty file | Abdullah | lines are correct on sample maps (tested with ASan on sample, empty, no-trailing-newline and blank-only files) ✅ **DONE (Abdullah)** |
| 1.3 | Parse `NO SO WE EA`: any order, extra spaces, duplicates rejected, unknown identifiers rejected, file must exist and end in `.xpm` | Abdullah | all 4 paths stored ✅ **DONE (Abdullah)** |
| 1.4 | Parse `F` and `C`: `R,G,B` in 0-255, spaces tolerated, bad values rejected | Grace | colors stored as an int ✅ **DONE (Grace)**; Abdullah fixed the Makefile, the wiring and the digit overflow (see `explain/1.4-colors.md`) |
| 1.5 | Find where the map starts; all 6 elements are required before it; the map is last | Abdullah | an element after the map is rejected ✅ **DONE (Abdullah)**; `parse_elements` replaces the temporary driver and saves `game->map_start` (see `explain/1.5-elements.md`) |
| 1.6 | Copy the map into a rectangular grid (short rows padded with spaces); reject empty lines inside the map and any character other than `01NSEW` and space. Start at `game->map_start` (set by 1.5) and run to the last line | Grace | grid matches the file ✅ **DONE (Grace)** |
| 1.7 | Cleanup of 1.4/1.5 review items: accept `\r` and `\v\f` in `is_space` (CRLF files); split `*str++ != ','` into a helper; replace the compound literal in `is_element_line` (norm); run `norminette src inc`; add `tests/run_parsing.sh` with maps for colors (valid, `256`, `-1`, `1,2`, `1,2,3,4`, `1,,3`, duplicate, bare `F`) and elements (missing, order, after the map, no map); commit style: one convention (`task N.N >...`) | Grace | norminette clean, script passes with ASan, no leaks ✅ **DONE (Grace)**; Abdullah added the `\r` strip in `read_file.c` and `tests/run_parsing.sh` came with 2.3. norminette items fixed by Abdullah (see Open issues) |

## Phase 2 – Map validation
| ID | Task | Driver | Done when |
|---|---|---|---|
| 2.1 | Find the player: exactly one `N/S/E/W`; store its x, y and direction in a `t_player` in the game struct | Grace | 0 or 2+ players rejected, position and direction correct ✅ **DONE (Grace)** |
| 2.2 | Check the map is closed: every `0` and the player cell must have 4 neighbors (up/down/left/right) that exist and are not a space | Abdullah | open maps rejected, maps containing spaces inside walls accepted ✅ **DONE (Abdullah)** (see `explain/2.2-closed-map.md`) |
| 2.3 | Add test maps for 2.1 and 2.2 to `tests/maps/` (no player, two players, hole in the wall, `0` next to a space, `0` on the border, spaces around the map) | Abdullah | all pass, no leaks ✅ **DONE (Abdullah)** (planned for Grace; done by Abdullah) (`tests/run_parsing.sh`, 20 maps; see `explain/2.3-parsing-tests.md`) |

## Phase 3 – Window and image
| ID | Task | Driver | Done when |
|---|---|---|---|
| 3.1 | mlx init, window, image buffer, `put_pixel` | Abdullah | a pixel can be drawn at any x,y ✅ **DONE (Abdullah)** (see `explain/3.1-window.md`) |
| 3.2 | Draw floor and ceiling from the config colors | Abdullah (planned: Grace) | window shows the two colors ✅ **DONE (Abdullah)** (see `explain/3.2-background.md`) |
| 3.3 | Clean exit: ESC and the red cross; destroy image, window and display; free everything | Abdullah | no leaks, no crash ✅ **DONE (Abdullah)** (see `explain/3.3-clean-exit.md`) |

## Phase 4 – Raycasting core
| ID | Task | Driver | Done when |
|---|---|---|---|
| 4.1 | Set player position, direction and camera plane from the spawn character | Grace | correct starting direction for N/S/E/W ✅ **DONE (Grace)** |
| 4.2 | DDA: one ray per screen column; find the hit cell, which side was hit, and the perpendicular distance | Abdullah | distances verified by printing them on a hard-coded map ✅ **DONE (Abdullah)** (`tests/test_dda.c`, see `explain/4.2-dda.md`) |
| 4.3 | Wall height from distance; draw flat-colored vertical lines | Grace | 3D corridor visible, no fisheye |

## Phase 5 – Textures
| ID | Task | Driver | Done when |
|---|---|---|---|
| 5.1 | Load the 4 XPM files into images; error if loading fails; free at exit | Abdullah | all 4 load and are freed |
| 5.2 | Choose the texture from the hit side and ray direction (N/S/E/W) | Grace | each face shows its own texture |
| 5.3 | Compute `wall_x`, `tex_x` and the `tex_y` step; draw the textured column; no mirrored textures | Abdullah | textures look correct from every side |

## Phase 6 – Controls
| ID | Task | Driver | Done when |
|---|---|---|---|
| 6.1 | Key press/release state (`mlx_hook` 2 and 3) and a per-frame loop hook | Grace | holding keys is smooth |
| 6.2 | W/A/S/D movement with a wall check | Abdullah | cannot walk through walls |
| 6.3 | Left/right arrows rotate the view | Grace | smooth rotation, correct direction |
| 6.4 | Frame timing with `gettimeofday` so speed does not depend on the machine | Abdullah | same feel at any frame rate |

## Phase 7 – Integration and hardening
| ID | Task | Driver | Done when |
|---|---|---|---|
| 7.1 | Connect parser to game (replace the hard-coded map) | Grace | our test maps run |
| 7.2 | Bad-input test run: empty file, no player, open map, bad colors, missing texture, huge map, directory as argument | Abdullah | never crashes, always `Error\n` + message |
| 7.3 | Full leak check, valgrind run on a school machine, norminette on all files, `make re` clean, Makefile does not relink | Grace | zero leaks, zero norm errors (ignoring `INVALID_HEADER`) |
| 7.4 | Window behavior: minimize, switch windows, resize | Abdullah | stays smooth |

## Phase 8 – README and defense prep
| ID | Task | Driver | Done when |
|---|---|---|---|
| 8.1 | `README.md`: first line in italics *This project has been created as part of the 42 curriculum by <login1>, <login2>*, then Description, Instructions, Resources (including how AI was used) | Grace | all required sections, in English |
| 8.2 | Each of us walks the other through parsing, DDA and texturing | both | both can answer "why this line?" |

## Phase 9 – Bonus (decide after Phase 8)
Candidates: wall collisions (partly done in 6.2), minimap, mouse look, doors, animated sprites. Bonus files must be `*_bonus.c/.h` and need a `bonus` Makefile rule.

## Order
Phase 0 comes first. Then:
```
2 (validation) ─────────────┐
3 ─ 4 ─ 5 ─ 6 (rendering) ──┴─ 7 ─ 8 ─ 9
```
Phase 2 is small and finishes the parser, so we start there. Phases 3–6 only need the shared structs, so they can start in parallel with Phase 2 if one of us is waiting.
