#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>


const int WIDTH = 800;
const int HEIGHT = 400;
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE };
bool keys[5] = { false, false, false, false, false };

struct Orzel
{
	int x;
	int y;
	int speed;
	int boundx;
	int boundy;
	int lives;
	int score;
};


void InitOrzel(Orzel &statek);
void DrawOrzel(Orzel &statek);
void MoveLeft(Orzel &statek);
void MoveUp(Orzel &statek);
void MoveDown(Orzel &statek);
void MoveRight(Orzel &statek);


int main(void)
{
	bool done = false;
	int count = 0;
	bool redraw = true;
	const int FPS = 60;

	Orzel statek;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;


	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);
	if (!display)										//test display object
		return -1;

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font24 = al_load_font("segoeui.ttf", 24, 0);

	al_init_primitives_addon();
	al_install_keyboard();
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);


	InitOrzel(statek);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if (keys[UP])
				MoveUp(statek);
			if (keys[DOWN])
				MoveDown(statek);
			if (keys[LEFT])
				MoveLeft(statek);
			if (keys[RIGHT])
				MoveRight(statek);
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}


		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			DrawOrzel(statek);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

}

void InitOrzel(Orzel &statek)
{
	statek.x = 15;
	statek.y = HEIGHT / 2;
	statek.speed = 7;
	statek.boundx = 6;
	statek.boundy = 7;
	statek.score = 0;
	statek.lives = 3;

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
void MoveLeft(Orzel &statek)
{
	statek.x -= statek.speed;
	if (statek.x < 0)
		statek.x = 0;

}
void MoveUp(Orzel &statek)
{
	statek.y -= statek.speed;
	if (statek.y < 0)
		statek.y = 0;
}
void MoveDown(Orzel &statek)
{
	statek.y += statek.speed;
	if (statek.y > HEIGHT)
		statek.y = HEIGHT;

}
void MoveRight(Orzel &statek)
{
	statek.x += statek.speed;
	if (statek.x > 300)
		statek.x = 300;
}