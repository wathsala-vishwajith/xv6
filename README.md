Cmds

##adding a prog

Write your C program inside xv6 directory
cd xv6
vim myprog.c


Add some changes to Makefile
Add a line to UPROGS variable
UPROGS=\
myprog\

Add a line to EXTRA variable
EXTRA=\
myprog.c\

Let’s start the simulator and see
make clean
make