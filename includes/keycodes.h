#ifndef KEYCODES
#define KEYCODES

#ifdef __linux__
#define LTURN 65363
#define RTURN 65361

#define FORWARD 122
#define LEFT 0
#define RIGHT 1
#define BACK 115
#define ESCAPE 65307

#else
#define LTURN 124
#define RTURN 123
#define FORWARD 13
#define LEFT 0
#define RIGHT 1
#define BACK 2
#define ESCAPE 53

#endif
#endif
