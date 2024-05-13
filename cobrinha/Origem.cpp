#include <SDL.h>
#include <vector>
#include <list>

SDL_Window* janela;
SDL_Renderer* render;
SDL_Event e;

float tile_unit = 25;

int janelaL = 25*25;
int janelaA = 25*25;

void iniciar()
{
	SDL_Init(SDL_INIT_VIDEO);

	janela = SDL_CreateWindow("snek", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, janelaL, janelaA, SDL_WINDOW_RESIZABLE);
	render = SDL_CreateRenderer(janela,-1,SDL_RENDERER_PRESENTVSYNC);
}
void deligar()
{
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(janela);
	SDL_Quit();
}

struct vi2d
{
	int x;
	int y;
};

bool rodando = true;



int tamanho;
int direcao;
vi2d posicao;
std::list <vi2d> snek;
int past_dir = 5;
bool dead = false;

vi2d maca;

void imput();

int main(int argc, char* args[])
{
	iniciar();

	direcao = 5;
	posicao = {3,7};
	maca = { 6,6 };
	int intervalo = 100;
	snek.push_back(posicao);
	tamanho = 1;

	while (rodando)
	{
		SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(render);

		past_dir = direcao;
		imput();

		switch (direcao)
		{
		case 1:
			posicao.y--;
			break;
		case 3:
			posicao.x--;
			break;
		case 5:
			posicao.x++;
			break;
		case 7:
			posicao.y++;
			break;
		}



		if(posicao.x != maca.x || posicao.y != maca.y)
			snek.pop_front();
		else
		{
			tamanho++;
			maca.x = rand() % 25;
			maca.y = rand() % 25;
		}

	


		vi2d newpos = {posicao.x,posicao.y};
		snek.push_back(newpos);
		

		SDL_SetRenderDrawColor(render, 0xFF, 0x00, 0x00, 0xFF);
		SDL_Rect mr = { tile_unit * maca.x,tile_unit * maca.y,tile_unit,tile_unit };
		SDL_RenderFillRect(render, &mr);

		if(!dead)
			SDL_SetRenderDrawColor(render, 0x00, 0xFF, 0x00, 0xFF);
		else
			SDL_SetRenderDrawColor(render, 0xFF, 0x00, 0x00, 0xFF);

		std::list<vi2d>::iterator p;
		int info = 0;
		for (p = snek.begin(); p !=snek.end(); p++)
		{
			info++;
			SDL_Rect quad = {p->x*tile_unit + 2,p->y*tile_unit + 2,tile_unit - 4,tile_unit - 4};
			if (info == tamanho)
				SDL_SetRenderDrawColor(render, 0x00, 0x90, 0x00, 0xFF);
			SDL_RenderFillRect(render, &quad);
			
			if (p->x == posicao.x && p->y == posicao.y && info!=tamanho)
			{
				dead = true;
			}
		}
		if (posicao.x * tile_unit >= janelaL || posicao.x < 0 || posicao.y * tile_unit>=janelaA || posicao.y < 0)
			dead = true;
		
		SDL_RenderPresent(render);
		SDL_Delay(intervalo);
	}
	deligar();
	return 0;
}

void imput()
{
	bool butao = false;
	while (SDL_PollEvent(&e))
	{
	switch (e.type)
	{
	case SDL_QUIT:
		rodando = false;
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
			
		case SDLK_LEFT:
			switch (past_dir)
			{
			case 1:
				direcao = 3;
				break;
			case 3:
				direcao = 7;
				break;
			case 7:
				direcao = 5;
				break;
			case 5:
				direcao = 1;
				break;
			}
			break;
		case SDLK_RIGHT:
			switch (past_dir)
			{
			case 1:
				direcao = 5;
				break;
			case 3:
				direcao = 1;
				break;
			case 7:
				direcao = 3;
				break;
			case 5:
				direcao = 7;
				break;
			}
			break;
		/*case SDLK_UP:
				direcao = 1;
			break;
		case SDLK_DOWN:
				direcao = 7;
			break;
			*/
		}
		break;
	}
}

}