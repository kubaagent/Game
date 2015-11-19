#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

//GLOBALS==============================
const int WIDTH = 800;
const int HEIGHT = 400;

void Initshuttle(Galaktyka &shuttle);
void Drawshuttle(Galactica &shuttle);

int main(void)
{
	bool done = false;

	Galactica shuttle;

	ALLEGRO_DISPLAY *display = NULL;

	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			
	if(!display)										//test display object
		return -1;

	al_init_primitives_addon();
	Initshuttle(shuttle);

	while(!done)
	{
		Drawshuttle(shuttle);
		
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}

	al_destroy_display(display);						
	return 0;
}

void Initshuttle(Galactica &shuttle)
{
	shuttle.x = 20;
	shuttle.y = HEIGHT / 2;
	shuttle.ID = PLAYER;
	shuttle.lives = 3;
	shuttle.speed = 7;
	shuttle.boundx = 6;
	shuttle.boundy = 7;
	shuttle.score = 0;
}

void Drawshuttle(Galactica &shuttle)
{
	al_draw_filled_rectangle(shuttle.x, shuttle.y - 9, shuttle.x + 10, shuttle.y - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(shuttle.x, shuttle.y + 9, shuttle.x + 10, shuttle.y + 7, al_map_rgb(255, 0, 0));

	al_draw_filled_triangle(shuttle.x - 12, shuttle.y - 17, shuttle.x + 12, shuttle.y, shuttle.x - 12, shuttle.y + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(shuttle.x - 12, shuttle.y - 2, shuttle.x + 15, shuttle.y + 2, al_map_rgb(0, 0, 255));
}