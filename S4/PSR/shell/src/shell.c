/** \file
 * 
 **/

#include "shell.h"

//Liste de pid/commande � supprimer lors de l'arr�t du programme
static Liste l_handler=NULL;
//Chaine de char � supprimer lors de l'arr�t du programme
static char * input_handler=NULL;

//Fonction qui g�re la fin du programme (provoqu� par un signal ou non), qui d�salloue les ressources restantes
void handler(int signum)
{
	Liste l=l_handler;
	ListeElem tmp=l->t;
	while(tmp!=NULL)
	{
		kill(tmp->val.pid,9);
		free(tmp->val.commande);
		tmp=tmp->suiv;
	}
	freeListe(l);

	if(!estExit(input_handler))printf("\n");
	free(input_handler);
	exit(0);
}

int taille_tableau(char * tab)
{
	int i=0;
	while(tab[i] != '\0') i++;
	return i;
}

void freeArg(char ** tab)
{
	int i=0;
	while(tab[i]=='\0')
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int recherche(char * tab,char c)
{
	int i=0;
	while((tab[i] != '\0')&&(tab[i]!=c)) i++;
	return (tab[i] == c)? i : -1; 
}

void wait_hidden_child(Liste l)
{
	int i=0,pid=0;
	int status=0;
	ListeElem tmp=l->t;
	while(tmp != NULL)
	{
		pid=tmp->val.pid;
		status=0;
		if(waitpid(pid,&status,WNOHANG) > 0)
		{
			printf("[%d]+  Fini\t\t\t%s\n",i+1,tmp->val.commande);
			free(tmp->val.commande);
			tmp=tmp->suiv;
			supprIndice(l,i);
			i--;
		}
		else tmp=tmp->suiv;
		i++;
	}
	return;
}

char * elimine_espace_fin(char * input,int n)
{
	int i=n-1;
	while((input[i] == ' ')&&(i>=0)) i--;
	input[i+1]='\0';
	return input;
}

int compte_char(char * tab,char c)
{
	int i=0,j=0;
	while((tab[i] != '\0')&& (i<TAILLE_INPUT))
	{
		if(tab[i]==c) j++;
		i++;
	}
	return j;
}

char ** separation_argument(char * tab)
{
	int n=compte_char(tab,' ')+1;
	char ** arg=(char **)malloc(sizeof(char *)*n);
	char * ptr=NULL;
	int i=0;
	
	ptr=strtok(tab," ");
	
	while(ptr != NULL)
	{
		arg[i]=ptr;
		i++;
		ptr=strtok(NULL," ");
	}
	arg[i]=NULL;
	return arg;
}

//Teste simplement si les premi�res lettres de la chaine de caract�res sont "exit"
int estExit(char * t)
{
	return (t[0]=='e')&&(t[1]=='x')&&(t[2]=='i')&&(t[3]=='t');
}

void shell_aux()
{
	char * input=(char *)malloc(TAILLE_INPUT*sizeof(char));//Allocation de la chaine de caract�re pour g�rer la saisi au clavier
	int pid_child=0,taille=0;
	Liste l=listenouv();//Allocation de la liste
	l_handler=l;
	input_handler=input;//Mise en place des valeurs des variables globales pour la fin du programme (pour leur d�sallocation)
	int hide=0;//Variable qui vaut 1 si on lance le programme avec '&', 0 sinon
	int i=0;//indice du caract�re '&'
	int status;
	char ** arg=NULL;//Pointeur pour un tableau de chaine de caract�re
	Commande c;
	
	while(1)
	{
		do
		{
			printf("> : ");
			//Si on envoie un EOF ou on tape "exit" dans le terminal, cela provoque l'appel de la fonction qui arr�te le programme
			if((fgets(input,TAILLE_INPUT,stdin) == NULL) || estExit(input)) handler(0);//Provoque la d�sallocation des autres ressources puis la fin du programme
			wait_hidden_child(l);//On regarde si un/des processus de la liste de ps cach� est mort, et si c'est le cas, on affiche sa notification de d�c�s
		}
		while(input[0]=='\n');//Demande de saisi tant que l'utilisateur appuie sur Entr�e sans indiqu� de commande
		
		taille=taille_tableau(input);
		input[taille-1]='\0';//On remplace le '\n' en fin de chaine de caract�res par un '\0'
		
		i=recherche(input,'&');//On recherche le caract�re "&" pour indiqu� si oui ou non on doit cacher l'execution du processus
		if(i==-1) hide=0;
		else
		{
			hide=1;
			input[i]=' ';//Transforme le '&' par un espace
			input=elimine_espace_fin(input,taille);
			c.commande=malloc((taille+1)*sizeof(char));
			strcpy(c.commande,input);//Copie l'intitul� de la commande (tap� au clavier)
		}

		
		arg=separation_argument(input);//S�pare les arguments de la commande pour les envoyer � exec plus tard
		
		pid_child=fork();
		if(!pid_child)
		{
			execvp(arg[0],arg);//Lance l'exec de la commande saisi au clavier de la part du fils cr�er par un fork pour �a
		}
		else
		{
			c.pid=pid_child;
			if(!hide) waitpid(pid_child,&status,0);//Si on ne doit pas cacher l'execution du processus fils, on fait un waitpid simple sur le pid de ce processus
			else
			{
				adjq(l,c);//Sinon on ajoute la structure commande � la liste des processus cach�s
				printf("[%d] %d\n",l->taille,pid_child);//Affiche une notification de lancement de processus cach� (avec l'ordre d'insertion dans la liste, ainsi que le pid du processus)
			}
		}
		freeArg(arg);//Lib�re le tableau d'argument
	}
	return;
}

int shell()
{
	struct sigaction action;
	action.sa_handler=handler;
	sigaction(SIGINT,&action,NULL);

	shell_aux();
	
	return 0;
}
