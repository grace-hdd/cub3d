#!/bin/bash
# Parsing tests: builds the parser (tests/parse_main.c, no window, no display
# needed) with AddressSanitizer and runs every map.
#   tests/maps/valid/*.cub    must exit 0 and print nothing
#   tests/maps/invalid/*.cub  must exit 1, print "Error" first, no sanitizer report
# Run from anywhere: tests/run_parsing.sh

cd "$(dirname "$0")/.." || exit 1
BIN=$(mktemp -d)/cub3d_asan
trap 'rm -rf "$(dirname "$BIN")"' EXIT

make -s -C libft >/dev/null || exit 1
make -s -C minilibx-linux >/dev/null 2>&1
cc -g -fsanitize=address,undefined -Iinc -Ilibft -Iminilibx-linux \
	tests/parse_main.c src/parsing/*.c src/render/*.c src/utils/*.c \
	libft/libft.a minilibx-linux/libmlx.a -lXext -lX11 -lm -o "$BIN" || exit 1

pass=0
fail=0
check()
{
	local file=$1 want=$2 out rc
	out=$("$BIN" "$file" 2>&1 >/dev/null)
	rc=$?
	if [ "$rc" -ne "$want" ] || echo "$out" | grep -q "Sanitizer\|runtime error"; then
		echo "FAIL $file (rc=$rc) $(echo "$out" | head -1)"
		fail=$((fail + 1))
	elif [ "$want" -eq 1 ] && [ "$(echo "$out" | head -1)" != "Error" ]; then
		echo "FAIL $file (no 'Error' header)"
		fail=$((fail + 1))
	elif [ "$want" -eq 0 ] && [ -n "$out" ]; then
		echo "FAIL $file (unexpected output: $out)"
		fail=$((fail + 1))
	else
		pass=$((pass + 1))
	fi
}

for f in tests/maps/valid/*.cub; do check "$f" 0; done
for f in tests/maps/invalid/*.cub; do check "$f" 1; done
echo "passed: $pass  failed: $fail"
[ "$fail" -eq 0 ]
