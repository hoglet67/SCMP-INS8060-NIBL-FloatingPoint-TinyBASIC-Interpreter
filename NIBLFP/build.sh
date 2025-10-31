#!/bin/sh
# for emulation uncomment line 4
fn=NIBLFP
#defs="-D EMULA"
asl -i ../INCLUDE -cpu sc/mp ${defs} -L ${fn}.asm &&
p2bin ${fn} -r '53248-$' &&
p2hex ${fn} -r '53248-$' -F Intel -l 32 &&
rm ${fn}.p
