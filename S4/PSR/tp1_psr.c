#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>


#define MAXBUFF 50
#define TAILLELIGNE 8
#define TAILLEMOT 5

char getcharv2()
{
	char c;
	if(read(0,&c,1)<=0)c=EOF;
	return c;
}

char getcharv3()
{
	static char buffer[MAXBUFF];
	static int tailletotalbuffer=0;
	static int indicebuffer=0;
	char c;
	if(tailletotalbuffer==indicebuffer)
	{
		tailletotalbuffer=read(0,&buffer,MAXBUFF);
		if(tailletotalbuffer==0) return EOF;
		indicebuffer=0;
	}
	c=buffer[indicebuffer++];
	return c;
}

char getcharv4(char * buffer,int size)
{
	static int tailletotalbuffer=0;
	static int indicebuffer=0;
	static char c;
	if(tailletotalbuffer==indicebuffer)
	{
		tailletotalbuffer=read(0,buffer,size);
		if(tailletotalbuffer==0) return EOF;
		indicebuffer=0;
	}
	c=buffer[indicebuffer++];
	return c;
}

void lsl(char * file)
{
	struct stat s;
	stat(file,&s);
	
	switch (s.st_mode & S_IFMT)
	{
		case S_IFDIR:  printf("d");         break;
		case S_IFREG:  printf("-");       	break;
		default:       printf("?");         break;
	}
	(s.st_mode & S_IRUSR)?	printf("r")	: printf("-");
	(s.st_mode & S_IWUSR)?	printf("w")	: printf("-");
	(s.st_mode & S_IXUSR)?	printf("x")	: printf("-");
	(s.st_mode & S_IRGRP)?	printf("r")	: printf("-");
	(s.st_mode & S_IWGRP)?	printf("w")	: printf("-");
	(s.st_mode & S_IXGRP)?	printf("x")	: printf("-");
	(s.st_mode & S_IROTH)?	printf("r")	: printf("-");
	(s.st_mode & S_IWOTH)?	printf("w")	: printf("-");
	(s.st_mode & S_IXOTH)?	printf("x")	: printf("-");
	printf("\t%s\n",file);
}

void ls(char * file)
{
	DIR* dir=NULL;
	dir=opendir(file);
	char namefile[512];
	struct dirent * currentfile=NULL;
	
	while( (currentfile=readdir(dir))!=NULL)
	{
		if(currentfile->d_name[0]!='.')
		{
			strcpy(namefile,file);
			lsl(strcat(strcat(namefile,"/"),currentfile->d_name));
		}
	}
	closedir(dir);
}

void estdedans(char * mot)
{
	int dir=open("lexique.txt", O_RDONLY );
	int a=0,b=lseek(dir,0,SEEK_END)/TAILLEMOT,i;
	char t[6];
	int stop=1;
	t[5]='\0';
	lseek(dir,0,SEEK_SET);
	int stop=1;
	while((i!=(a+b)/2)&&stop)
	{
		i=(a+b)/2;
		lseek(dir,i*TAILLEMOT+2,SEEK_SET);
		read(dir,t,TAILLEMOT);
		
		if(strcmp(mot,t)==0) stop=0;
		else
		

/*int main(int argc,char ** argv)
{
	int i=atoi(argv[1]),s=0;
	char * b=malloc(i*sizeof(char));	
	while((s=read(0,b,i*sizeof(char)))>0) write(1,b,s*sizeof(char));
	free(b);
	return 0;
}
/*
int main()
{
	char c;
	while((c=getchar())!=EOF) putchar(c);
	return 0;

}*/

int main(int argc,char ** argv)
{
	return 0;
}
