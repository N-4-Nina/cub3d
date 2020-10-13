CUB=cub3d;MAP=map2.cub;valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --log-file=valgrind_log ./$CUB $MAP;grep -A1 "valgrind" valgrind_log|grep $CUB
