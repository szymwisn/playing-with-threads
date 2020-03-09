all:
	gcc -o app  main.cpp window.cpp direction.cpp ball.cpp -pthread -lncurses -lstdc++
