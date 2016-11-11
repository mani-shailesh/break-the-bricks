compile_rule: src/constants.h src/game.h src/objects.cpp src/util.cpp src/game.cpp src/main.cpp src/objects.h src/util.h
	g++ src/constants.h src/game.h src/objects.cpp src/util.cpp src/game.cpp src/main.cpp src/objects.h src/util.h -lGL -lGLU -lglut -o break_the_bricks
	chmod 777 break_the_bricks
	./break_the_bricks