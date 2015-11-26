#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

struct Orzel
{
	int x;
	int y;
};

const int WIDTH = 800;
const int HEIGHT = 400;

void InitOrzel(Orzel &statek);
void DrawOrzel(Orzel &statek);


int main(void)
{
	bool done = false;
	int count = 0;

	Orzel statek;

	ALLEGRO_DISPLAY *display = NULL;

	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			
	if(!display)										//test display object
		return -1;

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font24 = al_load_font("segoeui.ttf", 24, 0);

	al_init_primitives_addon();
	InitOrzel(statek);

	while(!done)
	{
		DrawOrzel(statek);

		count++;
		al_draw_textf(font24, al_map_rgb(255, 255, 0), 25, 50, 0, "Timer: %i", count);
		
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}

	al_destroy_display(display);						
	return 0;
}

void InitOrzel(Orzel &statek)
{
	statek.x = 15;
	statek.y = HEIGHT / 2;
	
}

void DrawOrzel(Orzel &statek)
{
	//left dzida
	al_draw_filled_rectangle(statek.x, statek.y - 9, statek.x + 10, statek.y - 7, al_map_rgb(255, 0, 0));
	//right dzida
	al_draw_filled_rectangle(statek.x, statek.y + 9, statek.x + 10, statek.y + 7, al_map_rgb(255, 0, 0));
	//statek
	al_draw_filled_triangle(statek.x - 12, statek.y - 17, statek.x + 12, statek.y, statek.x - 12, statek.y + 17, al_map_rgb(0, 255, 0));
	//fotel kapitana
	al_draw_filled_rectangle(statek.x - 12, statek.y - 2, statek.x + 15, statek.y + 2, al_map_rgb(0, 0, 255));
}