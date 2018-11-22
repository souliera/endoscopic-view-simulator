all:
	g++ -o volumic.out volumic.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11 -g
	g++ -o mpr.out mpr.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11 -g

clean:
	find . -type f -iname *.o -delete

mrproper:
	find . -type f -iname *.out -delete
