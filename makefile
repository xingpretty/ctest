
main:main.c
	gcc -o main main.c -lrt

timer_work:timer_work.c
	gcc -o timer_work timer_work.c -lrt

clean:
	rm main
	rm test
