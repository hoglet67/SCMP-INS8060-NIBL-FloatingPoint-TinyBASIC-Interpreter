#!/bin/sh
# for emulation add -D EMULA
fn=NIBLFP
#defs="-D USETTY"
defs="-D USETTY -D INTERNAL"
#defs="-D EMULA"
#defs="-D EMULA -D INTERNAL"
#defs="-D KBPLUS"
asl -i ../INCLUDE -cpu sc/mp ${defs} -L ${fn}.asm &&
p2bin ${fn} -r '53248-$' &&
p2hex ${fn} -r '53248-$' -F Intel -l 32 &&
rm ${fn}.p
