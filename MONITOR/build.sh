#!/bin/sh
# for emulation uncomment line 4
fn=MONITOR
#defs="-D EMULA"
asl -i ../INCLUDE -cpu sc/mp ${defs} -L ${fn}.asm &&
p2bin ${fn} -r '49152-$' &&
p2hex ${fn} -r '49152-$'  -F Intel -l 32 &&
truncate -s 4096 ${fn}.bin
rm ${fn}.p
