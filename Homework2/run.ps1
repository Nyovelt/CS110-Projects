$CC="gcc"
$CFLAGS="-Wpedantic -Wall -Wextra -Werror -std=c89"

Invoke-Expression "$CC $CFLAGS doubll2d.c -o doubll2d.o"
