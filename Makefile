all:
	gcc -o app  main.cpp window.cpp direction.cpp ball.cpp basket.cpp -lpthread -lncurses -lstdc++
