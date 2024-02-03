#ifndef KEYS_H
# define KEYS_H

# if OS == 1
	# define ESC 65307
	# define UP 65362
	# define LEFT 65361
	# define RIGHT 65363
	# define DOWN 65364
	# define L_SQRB 91
	# define R_SQRB 93
	# define W 119
	# define S 115
	# define A 97
	# define D 100
	# define E 101
	# define NUM_1 49
	# define NUM_2 50
	# define Z 122
	# define C 99
# else
	# define ESC 53
	# define UP 126
	# define LEFT 123
	# define RIGHT 124
	# define DOWN 125
	# define L_SQRB 33
	# define R_SQRB 30
	# define W 13
	# define S 1
	# define A 0
	# define D 2
	# define E 14
	# define Z 6
	# define C 8
	// Arbitratry values, update later.
	# define NUM_1 18 // edit cam
	# define NUM_2 19 // edit light
	// see if I can implement the mouse on time.
	// # define MAC_9 44 // previous object
	// # define MAC_0 45 // next object
	# define MOUSE_1 1
# endif

#endif
