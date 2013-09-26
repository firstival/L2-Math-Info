#include "io.h"

extern int (*compte_voisins_vivants) (int, int, grille);
extern void (*set_continue_vie) (int, int, grille);
static int temps = 0;

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf("|---");
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i,j, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("temps t = %d\n", temps);
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		for (j=0; j<c ; ++j){
			if (est_vivante(i,j,g))
				printf ("| %d ",g.cellules[i][j]);
			else if (! est_viable(i,j,g))
				printf ("| X ");
			else // cellule morte
				printf ("|   ");
		}
		printf("|\n");
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 6);
}

void affiche_grille_cairo(grille g,cairo_surface_t * surface)
{
    int i=0,j=0;
    float pas = 1.0 / 8.0;
    cairo_t *cr;
    char duree[20]={0};
    sprintf(duree,"Temps : %d", temps);
    //cairo_test_extents_t te;
    cr=cairo_create(surface);
    cairo_set_source_rgb(cr,1,1,1);
    cairo_paint(cr);

    cairo_set_source_rgb(cr,0.2,0.4,0.4);
    cairo_rectangle(cr,0,0,g.nbc*PIXEL,ENTETE);
    cairo_fill(cr);

    cairo_select_font_face(cr,"Georgia",CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr,ENTETE / 3.5);
    cairo_set_source_rgb(cr,1,1,1);
    cairo_move_to(cr,g.nbc/5*PIXEL,ENTETE / 2);
    cairo_show_text(cr,duree);
    if (set_continue_vie == set_ne_viellit_pas)
    {
        //cairo_text_extents(cr,tab[2],&te);
        cairo_move_to(cr,g.nbc/2*PIXEL,ENTETE / 3);
        cairo_show_text(cr,"Vieillissement désactivé");
    }
    else
    {
        //cairo_text_extents(cr,tab[1],&te);
        cairo_move_to(cr,g.nbc/2*PIXEL,ENTETE / 3);
        cairo_show_text(cr,"Vieillissement activé");
    }


    if (compte_voisins_vivants == compte_voisins_cyclique)
    {
        //cairo_text_extents(cr,tab[3],&te);
        cairo_move_to(cr,g.nbc/2*PIXEL,ENTETE/2 + ENTETE / 4);
        cairo_show_text(cr,"Voisinage cyclique");
    }
    else
    {
        //cairo_text_extents(cr,tab[4],&te);
        cairo_move_to(cr,g.nbc/2*PIXEL,ENTETE/2 + ENTETE / 4);
        cairo_show_text(cr,"Voisinage non cyclique");
    }



    for(j=0;j<g.nbc;j++)
    {
        for(i=0;i<g.nbl;i++)
        {
            if(est_vivante(i,j,g))
            {

                cairo_rectangle(cr,j*PIXEL,i*PIXEL+ENTETE,PIXEL,PIXEL);
                cairo_set_source_rgb(cr,(float)(g.cellules[i][j]-1)*pas,(float)(g.cellules[i][j]-1)*pas,(float)(g.cellules[i][j]-1)*pas);
                cairo_fill(cr);
            }
            else if (! est_viable(i,j,g))
            {
                cairo_rectangle(cr,i*PIXEL,j*PIXEL,PIXEL+ENTETE,PIXEL);
                cairo_set_source_rgb(cr,1,0,0);
                cairo_fill(cr);
            }
        }
    }
    cairo_destroy(cr);
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				temps ++;
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'c' :
			{ // touche "c" pour activer / desactiver le voisinage cyclique
				if (compte_voisins_vivants == compte_voisins_cyclique){
					compte_voisins_vivants = compte_voisins_non_cyclique;
					printf("voisinage non cyclique    \n");
				}
				else {
					compte_voisins_vivants = compte_voisins_cyclique;
					printf("voisinage cyclique      \n");
				}

				while(getchar() != '\n');
				printf("\n\e[%dA",3);
				break;
			}
			case 'v' :
			{ // touche "v" pour activer/desactiver le viellissement des cellules
				if (set_continue_vie == set_ne_viellit_pas){
					set_continue_vie = set_viellit;
					printf("viellissement ON     \n");
				}
				else {
					set_continue_vie = set_ne_viellit_pas;
					printf("viellissement OFF    \n");
				}
				while(getchar() != '\n');
				printf("\n\e[%dA",3);
				break;
			}
			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	}
	return;
}

void debut_jeu_cairo(grille *g, grille *gc)
{
    int stop=1;

    Display *display=NULL;
    Window rootwin,win;
    XEvent e;
    int screen;

    if(!(display=XOpenDisplay(NULL)))
    {
        fprintf(stderr,"Erreur : Impossible d'ouvrir une connexion avec X");
        exit(1);
    }
    screen=DefaultScreen(display);
    rootwin=RootWindow(display,screen);
    win=XCreateSimpleWindow(display,rootwin,20,20,g->nbc*PIXEL,g->nbl*PIXEL + ENTETE,0,BlackPixel(display,screen),WhitePixel(display,screen));
    XStoreName(display,win,"Jeu de la vie");
    XSelectInput(display,win,ExposureMask|ButtonPressMask|KeyPressMask);
    XMapWindow(display,win);

    cairo_surface_t * cs=NULL;
    cs=cairo_xlib_surface_create(display,win,DefaultVisual(display,0),g->nbc*PIXEL,g->nbl*PIXEL + ENTETE);
    affiche_grille_cairo(*g,cs);

    while(stop)
    {
        XNextEvent(display,&e);
        switch (e.type)
        {
            /*case Expose :
            {
                affiche_grille_cairo(*g,cs);
                break;
            }*/
            case ButtonPress :
            {
                if(e.xbutton.button==Button1)
                {
                    evolue(g,gc);
                    temps ++;
                    affiche_grille_cairo(*g,cs);
                }
                else if(e.xbutton.button==Button3)
                {
                    stop=0;
                }
                break;
            }
            case KeyPress:
            {
                if(e.xkey.keycode==XKeysymToKeycode(display,XK_v))
                {
                    if (set_continue_vie == set_ne_viellit_pas)
                    {
                        set_continue_vie = set_viellit;
                        printf("viellissement ON\n");
                    }
                    else
                    {
                        set_continue_vie = set_ne_viellit_pas;
                        printf("viellissement OFF\n");
                    }
                }
                else if(e.xkey.keycode==XKeysymToKeycode(display,XK_c))
                {
                    if (compte_voisins_vivants == compte_voisins_cyclique)
                    {
                        compte_voisins_vivants = compte_voisins_non_cyclique;
                        printf("voisinage non cyclique\n");
                    }
                    else
                    {
                        compte_voisins_vivants = compte_voisins_cyclique;
                        printf("voisinage cyclique\n");
                    }
                }
                affiche_grille_cairo(*g,cs);
                break;
            }
        }
    }

    cairo_surface_destroy(cs);
    XCloseDisplay(display);
}
