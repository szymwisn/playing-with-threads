all:
	gcc -o app  main.cpp window.cpp direction.cpp ball.cpp -lpthread -lncurses -lstdc++
