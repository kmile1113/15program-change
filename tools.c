#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define DEFAULT_FILENAME "mydict.dat"
#define DEFAULT_HISTORY_FILENAME "history.dat"
#define TEMP_FILENAME "tem.dat"

void FileReadLine(FILE *file, char *buf)
{
   char nowch,i=0;

   nowch = fgetc(file);
   while (nowch !='\n' && nowch != EOF)
	{
	buf[i++]= nowch;
	nowch = fgetc(file);
	}
    buf[i] ='\0';
}


void FileWriteLine(FILE *file, char *buf)
{
    fputs(buf, file);
    fputc('\n', file);
}



int DictFindWord(FILE *file, char *word, char *exp){
	char e[80];

	fseek(file, 0, SEEK_SET);

	while (!feof(file))
{

 	FileReadLine(file, exp);

	if(strcmp(word, exp)== 0)
	{
	FileReadLine(file, exp);
	return 1;
	}

	FileReadLine(file, e);
}

	return 0;
}


void DictAddWord(FILE *file, char *word, char *exp)
{

   fseek(file, 0, SEEK_END);

   FileWriteLine(file, word);
   FileWriteLine(file, exp);
}

int DeleteWord(FILE *file, char *word, char *exp)
{
	FILE *ft;
	int i;
	char *tempfile=TEMP_FILENAME;
	ft = fopen(tempfile,"w");
	if(ft==NULL)
	{
	    printf("Brror: Cannot open the dictionary file.\n");
	    return 1;
	}
	fseek(file,0,SEEK_SET);
	fseek(ft,0,SEEK_SET);
	while (!feof(file))
 {
	i=0;
	FileReadLine(file,exp);     
	if(strcmp(exp,word)!=0)
        {
	fflush(ft);
	fprintf(ft,"%s",exp);
	fprintf(ft,"\n");
	FileReadLine(file,exp);
	FileWriteLine(ft,exp);
	}
	else
	{
	FileReadLine(file,exp);
	}
	while(exp[i]!='\0'){
	exp[i++]=0;
	}
 }
close(ft);
remove(DEFAULT_FILENAME);
rename(TEMP_FILENAME,DEFAULT_FILENAME);
}
