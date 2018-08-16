all: connect connectbetter

connect: connect.c
	gcc connect.c -o connect

connectbetter: connectbetter.c
	gcc connectbetter.c -o connectbetter
