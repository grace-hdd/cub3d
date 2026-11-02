# cub3D – Team Plan

**Team:** Abdullah and Grace
**Scope:** mandatory part first. The bonus is decided only after the mandatory part is perfect (Phase 9).
**Deadline:** none fixed. We work phase by phase.

## Working rules
- **Pair on everything.** Each task has a driver (writes and commits) and a navigator (reads, questions, tests). The driver alternates as listed below.
- **One git branch per task:** `task/<id>-<name>` (e.g. `task/2.1-player`). Merge into `main` only when the task's "Done when" is met.
- **Before every merge:** `norminette src inc` shows no errors, `make` builds with `-Wall -Wextra -Werror`, no leaks.
- **Understand before you merge.** If code was written with help (a teammate, a peer, or an AI tool), both of us must be able to explain every line. This is a graded rule.
- **Leaks:** valgrind does not start on Abdullah's machine (glibc too new), so `tests/run_parsing.sh` uses AddressSanitizer. Do a final valgrind run on a school machine.

## Phase 1 – Parsing the config
| ID | Task | Driver | Done when |
|---|---|---|---|
| 1.1 | Argument check: exactly 1 argument, `.cub` extension, file can be opened | Abdullah | bad arguments give `Error\n` + a message |
| 1.2 | Read the file into lines, keeping blank lines | Grace | lines are correct on sample maps |
| 1.3 | Parse `NO SO WE EA`: any order, extra spaces, duplicates rejected, file must exist | Abdullah | all 4 paths stored |
| 1.4 | Parse `F` and `C`: `R,G,B` in 0-255, spaces tolerated, bad values rejected | Grace | colors stored as an int |
| 1.5 | Find where the map starts; all 6 elements are required before it; the map is last | Abdullah | an element after the map is rejected |
| 1.6 | Copy the map into a rectangular grid (short rows padded with spaces) | Grace | grid matches the file |

## Phase 2 – Map validation
| ID | Task | Driver | Done when |
|---|---|---|---|
| 2.1 | Find the player: exactly one `N/S/E/W`; store its x, y and direction in a `t_player` in the game struct | Grace | 0 or 2+ players rejected, position and direction correct |
| 2.2 | Check the map is closed: every `0` and the player cell must have 4 neighbors (up/down/left/right) that exist and are not a space | Abdullah | open maps rejected, maps containing spaces inside walls accepted |
| 2.3 | Add test maps for 2.1 and 2.2 to `tests/maps/` (no player, two players, hole in the wall, `0` next to a space, `0` on the border, spaces around the map) | Grace | all pass, no leaks |

## Phase 3 – Window and image
| ID | Task | Driver | Done when |
|---|---|---|---|
| 3.1 | mlx init, window, image buffer, `put_pixel` | Abdullah | a pixel can be drawn at any x,y |
| 3.2 | Draw floor and ceiling from the config colors | Grace | window shows the two colors |
| 3.3 | Clean exit: ESC and the red cross; destroy image, window and display; free everything | Abdullah | no leaks, no crash |

## Phase 4 – Raycasting core
| ID | Task | Driver | Done when |
|---|---|---|---|
| 4.1 | Set player position, direction and camera plane from the spawn character | Grace | correct starting direction for N/S/E/W |
| 4.2 | DDA: one ray per screen column; find the hit cell, which side was hit, and the perpendicular distance | Abdullah | distances verified by printing them on a hard-coded map |
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
| 7.3 | Full leak check, norminette on all files, `make re` clean, Makefile does not relink | Grace | zero leaks, zero norm errors |
| 7.4 | Window behavior: minimize, switch windows, resize | Abdullah | stays smooth |

## Phase 8 – README and defense prep
| ID | Task | Driver | Done when |
|---|---|---|---|
| 8.1 | `README.md`: first line in italics *This project has been created as part of the 42 curriculum by <login1>, <login2>*, then Description, Instructions, Resources (including how AI was used) | Grace | all required sections, in English |
| 8.2 | Each of us walks the other through parsing, DDA and texturing | both | both can answer "why this line?" |

## Phase 9 – Bonus (decide after Phase 8)
Candidates: wall collisions (partly done in 6.2), minimap, mouse look, doors, animated sprites. Bonus files must be `*_bonus.c/.h` and need a `bonus` Makefile rule.

## Order
```
2 (validation) ─────────────┐
3 ─ 4 ─ 5 ─ 6 (rendering) ──┴─ 7 ─ 8 ─ 9
```
Phase 2 is small and finishes the parser, so we start there. Phases 3–6 only need the shared structs, so they can start in parallel with Phase 2 if one of us is waiting.
