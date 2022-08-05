#! /bin/bash

COMANDO="sudo perf stat -e /power/energy-pkg/"
#APP="python3.7 ${METODO[j]}.py";
APP='';

for args in "$@"
do
    APP+=" $args";
done

echo $COMANDO $APP

date +%H:%M:%S.%N && $COMANDO $APP &> PerfResult.dat && date +%H:%M:%S.%N