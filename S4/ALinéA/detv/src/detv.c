/** \file
 * Source : detvs
 **/

#include "detv.h"

FILE * fichier=NULL;
int * pid_child=NULL;

void handler_sigalrm_ech(int signum)
{
	fclose(fichier);
	
	fprintf(stderr,"Erreur : Temps maximum du calcul par triangularisation depasse\n");
	exit(0);
}

void handler_sigalrm_rec(int signum)
{
	fclose(fichier);
	
	fprintf(stderr,"Erreur : Temps maximum du calcul par recursion depasse\n");
	exit(0);
}

//Handler du père s'il reçoit un SIGINT
void handler_sigint(int signum)
{
	int i=0;
	/* Envoie un SIGALRM à ses deux fils pour provoquer leur mort de manière propre */
	kill(pid_child[0],SIGALRM);
	kill(pid_child[1],SIGALRM);
	for(i=0;i<2;i++) wait(NULL);//Attente pour enregistrer la mort des fils
	exit(0);
}

int main(int argc,char ** argv)
{
	if(argc < 5)
	{
		printf("Usage : detv <taille_min> <inc> <nb_matrices> <foutput>\n");
		exit(1);
	}
	srand(time(NULL));
	
	int taille_min=atoi(argv[1]);
	int inc=atoi(argv[2]);
	int nb_matrice=atoi(argv[3]);
	char * foutput=argv[4];
	int pid[2];
	int i=0,n=0,t1,t2;
	FILE * f=NULL;
	Matrix m=NULL;
	E resultat;
	
	struct sigaction action;
	
	
	for(i=0;i<2;i++)
	{
		pid[i]=fork();
		if(!pid[i]) break;
	}
	
	if((!pid[i]) && (i==0)) //Déterminant avec la fonction récursive
	{
		action.sa_handler=handler_sigalrm_rec;
		sigaction(SIGALRM,&action,NULL);//Mise en place de la redirection du SIGALRM
		
		//Ouverture du fichier avec le bon nom
		char * file=malloc((strlen(foutput)+5)*sizeof(char));
		strcpy(file,foutput);
		strcat(file,"_rec");
		f=fopen(file,"w");
		free(file);
		fichier=f;
		
		for(i=0;i<nb_matrice;i++)
		{
			n=taille_min+i*inc;
			m=newMatrix(n,n);// Création d'une matrice à la bonne taille
			m=randomMatrix(m);// Mise en place d'élément aléatoire dans la matrice
			t1=time(NULL);
			alarm(TEMPS_MAX);//Mise en place de l'alarm, SIGALRM se declanchera dans TEMPS_MAX secondes
			resultat=m_determinant_rec(m);//Calcul du déterminant
			t2=time(NULL);
			fprintf(f,"%d %d\n",n,t2-t1);//Ecriture dans le fichier du temps de calcul de la fonction
			deleteMatrix(m);
			fflush(f);
		}
		fclose(f);
	}


	if((!pid[i]) && (i==1)) // Déterminant avec la fonction de triangularisation
	{
		action.sa_handler=handler_sigalrm_ech;
		sigaction(SIGALRM,&action,NULL);//Mise en place de la redirection du SIGALRM
		
		char * file=malloc((strlen(foutput)+5)*sizeof(char));
		strcpy(file,foutput);
		strcat(file,"_ech");
		f=fopen(file,"w");
		free(file);
		fichier=f;
		
		//Ouverture du fichier avec le bon nom
		for(i=0;i<nb_matrice;i++)
		{
			n=taille_min+i*inc;
			m=newMatrix(n,n);// Création d'une matrice à la bonne taille
			m=randomMatrix(m);// Mise en place d'élément aléatoire dans la matrice
			t1=time(NULL);
			alarm(TEMPS_MAX);//Mise en place de l'alarm, SIGALRM se declanchera dans TEMPS_MAX secondes
			resultat=m_determinant_triangle(m);//Calcul du déterminant
			t2=time(NULL);
			fprintf(f,"%d %d\n",n,t2-t1);//Ecriture dans le fichier du temps de calcul de la fonction
			deleteMatrix(m);
			fflush(f);
		}
		fclose(f);
	}
	else // Cas du père
	{
		pid_child=pid;
		action.sa_handler=handler_sigint;
		sigaction(SIGINT,&action,NULL);//Redirection du signal SIGINT
		
		for(i=0;i<2;i++) wait(NULL); // Attente de la mort des fils
	}
	
	return 0;
}
