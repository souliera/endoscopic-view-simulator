all:
	g++ -o a.out mpr.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

clean:
	find . -type f -iname *.o -delete

mrproper:
	find . -type f -iname *.out -delete
