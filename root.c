
#include "root.h"
#include "renderer.h"
#include "keyin.h"
#include "cut.h"

int main ( int argc, char * argv[] ) 
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );

	// The window contains the surface.

	Root nlinst ( root, setup () );
	SDL_Window * nlinst ( window, root -> window );
	SDL_Surface * nlinst ( screenSurface, root -> screen );
	SDL_Event ev;

	Adjunct nlinst ( adj, adjunctInst ( 10, 0, 10, 10.0 ) );

	adjunctLink ( adj, 10, 0, 20, 10.0 );

	int delay = 0;

	while ( 1 )
	{
		Vecdir motion = OO;

		while ( SDL_PollEvent ( &ev ) )
		{
			if ( ev.type == SDL_QUIT )
			{
				terminateRoot ( root );

				_CrtDumpMemoryLeaks();

				return EXIT_SUCCESS;
			}

			else if ( ev.type == SDL_KEYDOWN )
			{
				ev.key.keysym.sym;
			}
		}

		if ( delay == 25 )
		{
			int numkeys = 0;
			const Uint8 * keyStates = SDL_GetKeyboardState ( &numkeys );
			motion = readKeyboardState ( numkeys, keyStates );

			delay = 0;
		}

		else
		{
			delay ++;
		}

		SDL_FillRect ( screenSurface, NULL, SDL_MapRGB ( screenSurface -> format, 0x00, 0x00, 0x00 ) );

		adjunctMove ( adj, motion, 4.0 );
		adjunctDebug ( adj, screenSurface );

		SDL_UpdateWindowSurface ( window );
	}

	_CrtDumpMemoryLeaks ();

	return EXIT_SUCCESS;
}

static SDL_Window * windowSetup ( int width, int height )
{
	// Attempt to initialize SDL and a window. Failures will shut down the program.

	if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 )
	{
		fprintf ( stderr, "SDL initialization failure: %s\n", SDL_GetError () );
		exit ( EXIT_FAILURE );
	}

	if ( IMG_Init ( IMG_INIT_PNG ) != IMG_INIT_PNG )
	{
		fprintf ( stderr, "IMG initialization failure: PNG support uninitialized.\n");
		exit ( EXIT_FAILURE );
	}

	SDL_Window * window = NULL;
	window = SDL_CreateWindow
	(
		"Mired", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 
		SDL_WINDOW_SHOWN
	);

	if ( window == NULL )
	{
		fprintf(stderr, "Window creation failure: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return window;
}

Root setup ()
{
	Root root = NULL;
	root = malloc ( sizeof ( struct root_s ) );

	if ( root == NULL ) return NULL;

	root -> window = NULL;
	root -> screen = NULL; 
	root -> eater = NULL;

	root -> window = windowSetup ( WIN_HZ, WIN_VT );
	printf ( "Successfully initialized window for display\n" );
	root -> screen = SDL_GetWindowSurface ( root -> window );
	root -> eater = defineEater();
	printf ( "Designated resource eater\n" );

	return root;
}

ResourceEater defineEater ()
{
	ResourceEater eater = NULL;

	eater = malloc ( sizeof ( struct res_eat_s ) );

	if ( eater == NULL ) return NULL;

	eater -> surface_set = NULL;
	eater -> surface_set = malloc ( 0 );
	eater -> surfaces = 0;

	return eater;
}

void dismantleRoot ( Root root )
{
	if ( root == NULL ) return;
	SDL_DestroyWindow ( root -> window );
	SDL_FreeSurface ( root -> screen );
	if ( root -> eater != NULL ) eat ( root -> eater );

	root -> window = NULL;
	root -> screen = NULL;
	root -> eater = NULL;

	free ( root );
	root = NULL;
}

void terminateRoot ( Root root )
{
	dismantleRoot ( root );
	printf ( "Dismantled root data\n" );

	IMG_Quit();
	printf ( "Closed SDL IMG\n" );

	SDL_Quit();
	printf ( "Closed SDL2\n" );
}

void trackSurface ( Root root, SDL_Surface * surface )
{
	ResourceEater eater = root -> eater;

	if ( eater == NULL ) 
	{
		fprintf ( stderr, "Attempted to track resource with NULL eater.\n" );
		return;
	}

	SDL_Surface ** set = eater -> surface_set;

	if ( set == NULL )
	{
		fprintf ( stderr, "Attempted to track resource with malformed eater.\n");
		return;
	}

	SDL_Surface ** checker;

	eater -> surfaces ++;

	checker = realloc 
	(
		set, 
		eater -> surfaces * sizeof ( SDL_Surface )
	);

	if ( checker != NULL )
	{
		eater -> surface_set = checker;
		eater -> surface_set[ eater -> surfaces - 1 ] = surface;
	}
}

void eat ( ResourceEater eater )
{
	if ( eater == NULL ) return;

	if ( eater -> surface_set != NULL ) 
	{
		for ( size_t ix = 0; ix < eater -> surfaces; ix ++)
		{
			SDL_Surface * surface = NULL;
			surface = eater -> surface_set[ ix ];

			if ( surface != NULL )
			{
				printf ( "Attempting to free surface set index %zu.\n", ix );

				SDL_FreeSurface ( surface );
				surface = NULL;
				eater -> surface_set[ ix ] = NULL;
			}
		}

		free ( eater -> surface_set );
		eater -> surface_set = NULL;
	}

	free ( eater );
	eater = NULL;

	printf ( "Resource Eater terminated.\n" );
}