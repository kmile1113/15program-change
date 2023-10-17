#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define DEFAULT_FILENAME "mydict.dat"
#define DEFAULT_HISTORY_FILENAME "history.dat"
#define TEMP_FILENAME "tem.dat"
int ChaXun(void){
	int i,res;
	char *dictfilename = DEFAULT_FILENAME;
	char *historyname= DEFAULT_HISTORY_FILENAME;
	FILE *dictfile;
	FILE *history;
	char nowch,choice;
	char cmdbuf[100], wordbuf[80],expbuf[80];

	dictfile = fopen(dictfilename,"a+");
	if (dictfile == NULL)
	{
	    printf("Brror: Cannot open the dictionary file.\n");
	    return 1;
	}
	history = fopen(historyname,"a+");
	if (history == NULL)
	{
	    printf("Brror: Cannot open the dictionary file.\n");
	    return 1;
	}
	printf("\n****************This is your dictionary******************");
	printf("\nIf you want to quit ,please enter #");
	printf("\nplease enter word you want query :");
	getchar();
	while (1)
 {
	i=res=0;
	while((nowch=getchar())!='\n'){
	cmdbuf[i++]=nowch;
	}


	cmdbuf[i]='\0';

	if(strcmp(cmdbuf,"#")==0){
	close(dictfilename);
	close(history);
	return 1;
	}

	res =DictFindWord(dictfile, cmdbuf, expbuf);
	if(res == 1)
	{
		printf("\nWord: %s\n", cmdbuf);
		printf("Bxpression:%s", expbuf);
		printf("\n------");
		fseek(history, 0, SEEK_END);
		FileWriteLine(history, cmdbuf);
		FileWriteLine(history, expbuf);
		printf("\nIf you want to quit ,please enter #");
		printf("\nIf you want to continue ,please enter the word :");
	}
	else
	{
		printf("\nword '%s' not exist", cmdbuf);
		printf("\n------");
		printf("\nIf you want to quit ,please enter #");
		printf("\nIf you want to continue ,please enter the word :");
	}

	
	i=0;
	while(cmdbuf[i]!='\0'){
	cmdbuf[i++]=0;
	}
 }
}

