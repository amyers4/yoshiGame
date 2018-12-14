CXX = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl2-config --cflags` -g -W -Wall -Werror -std=c++11 -Weffc++ -Wextra -pedantic -O0 -I `sdl2-config --prefix`/include/

LDFLAGS = `sdl2-config --libs` -lm -lexpat -lSDL2_ttf -lSDL2_image

OBJS = \
  renderContext.o \
	ioMod.o \
	parseXML.o \
	gameData.o \
	viewport.o \
	world.o \
	spriteSheet.o \
	image.o \
	imageFactory.o \
	ground.o\
	healthBar.o\
	menu.o\
	menuEngine.o\
	frameGenerator.o \
	sprite.o \
	multisprite.o \
	player.o\
	collisionStrategy.o\
	hud.o\
	health.o\
	enemy.o\
	chunk.o\
	explodingEnemy.o\
	goomba.o\
	twowaysprite.o \
	vector2f.o \
	clock.o \
	engine.o \
	main.o
EXEC = run

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
	rm -rf frames/*.bmp
