#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define DEFAULT_FILENAME "mydict.dat"
#define DEFAULT_HISTORY_FILENAME "history.dat"
#define TEMP_FILENAME "tem.dat"
int JiaoZhun(void){
	int enter;
getchar();
while(1){
	printf("\n***********amend your dictionary**************************\n");
	printf("*1.add_word   2.delete_word   3.replace_word  4:quit            *\n");
	printf("*****************************************************************\n");
	printf("Please choose:");
	scanf("%d",&enter);

	switch(enter)
		{
			case 1:
				Add();
			    break;
			case 2:
				Delete();
				break;
			case 3:				
				Change();
				break;
			case 4:
				return 1;
			default :
				printf("Invalid data cmd.\n");
		}

}
}

int Add(){
	int i,res;
	char *dictfilename = DEFAULT_FILENAME;
	char *historyname= DEFAULT_HISTORY_FILENAME;
	FILE *dictfile;
	FILE *history;
	char nowch;
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
	getchar();
	while(1){
	i=res=0;
	printf("\n########################################## Add ############################################");
	printf("\nIf you want to quit ,please enter #");
	printf("\nPlease enter the word you want to add in your dictionary:");
	while((nowch=getchar())!='\n'){
	cmdbuf[i++]=nowch;
	}
	cmdbuf[i]='\0';
	if(strcmp(cmdbuf,"#")==0){
	close(dictfilename);
	close(history);
	return 1;
	}

	i=0;
	printf("Please enter the expression you want to add in your dictionary:");
	while((nowch=getchar())!='\n'){
	expbuf[i++]=nowch;
	}
	expbuf[i]='\0';
	DictAddWord(dictfile, cmdbuf, expbuf);
/*end*/	
	i=0;
	while(cmdbuf[i]!='\0'){
	cmdbuf[i++]=0;
	}	
	i=0;
	while(expbuf[i]!='\0'){
	expbuf[i++]=0;
	}
}
}

int Delete(){
	int i,res;
	char *dictfilename = DEFAULT_FILENAME;
	FILE *dictfile;
	FILE *history;
	char nowch;
	char cmdbuf[100], wordbuf[80],expbuf[80];

	dictfile = fopen(dictfilename,"rt+");
	if (dictfile == NULL)
	{
	    printf("Brror: Cannot open the dictionary file.\n");
	    return 1;
	}

	getchar();

	i=res=0;

	printf("\n########################################## Delete ############################################");
	printf("\nIf you want to quit ,please enter #");
	printf("\n The word you want to delete:");
	
	while((nowch=getchar())!='\n'){
	cmdbuf[i++]=nowch;
	}
	cmdbuf[i]='\0';

	if(strcmp(cmdbuf,"#")==0){
	close(dictfilename);
	return 1;
	}
	else{
		DeleteWord(dictfile,cmdbuf,expbuf);
	}
	
	return 1;

}




int Change(){
	int enter;
	getchar();
	while(1){
	printf("if you want to end,please enter 2:\n");	
	printf("if you want to change your word,please enter 1:\n");
	printf("your choice:");
	scanf("%d",&enter);
	switch(enter)
		{
			case 1:
					if(Change_Word()==1)
					printf("change successful\n\n");
			    break;
			case 2:
				getchar();
				return 1;
			default :
				printf("Invalid data cmd.\n");
		}
	}

}

int Change_Word(){
	int i,res,flag=0;
	char *dictfilename = DEFAULT_FILENAME;
	char *tempfilename = TEMP_FILENAME;
	FILE *dictfile;
	FILE *tempfile;
//	FILE *history;
	char nowch;
	char old_cmdbuf[100], new_cmdbuf[100], wordbuf[80],expbuf[80],new_expbuf[80];

	dictfile = fopen(dictfilename,"rt+");
	if (dictfile == NULL)
	{
	    printf("Brror: Cannot open the dictionary file.\n");
	    return 1;
	}
	tempfile = fopen(tempfilename,"w");
	if (dictfile == NULL)
	{
	    printf("Brror: Cannot open the dictionary file.\n");
	    return 1;
	}
	fseek(dictfile, 0, SEEK_SET);
	fseek(tempfile, 0, SEEK_SET);
	printf("\n####################################### replace your words #########################################");
	printf("\nplease enter the old_word you want to change:");
	getchar();
	i=res=0;
	while((nowch=getchar())!='\n'){
	old_cmdbuf[i++]=nowch;
	}
	old_cmdbuf[i]='\0';
	//printf("%s\n",old_cmdbuf);
	
	i=0;
	printf("\nIf you only want to change the expression,please just enter the same word");	
	printf("\nplease enter the new_word you want to change:");
	while((nowch=getchar())!='\n'){
	new_cmdbuf[i++]=nowch;
	}
	new_cmdbuf[i]='\0';

	if(strcmp(old_cmdbuf,"#")==0){
	close(dictfilename);
	close(tempfilename);	
	return flag;
	}
	while (!feof(dictfile))
 {
	FileReadLine(dictfile, expbuf);
	fflush(tempfile);
	if(strcmp(expbuf,old_cmdbuf)!=0)
	{
	FileWriteLine(tempfile, expbuf);
	while(expbuf[i]!='\0'){
	expbuf[i++]=0;
	}
	FileReadLine(dictfile, expbuf);
	fflush(tempfile);
	FileWriteLine(tempfile, expbuf);
	while(expbuf[i]!='\0'){
	expbuf[i++]=0;
	}
	}
	else
	{
	flag=1;
	while(expbuf[i]!='\0'){
	expbuf[i++]=0;
	}
	fflush(tempfile);
	FileWriteLine(tempfile, new_cmdbuf);
	i=0;
	printf("please enter the new_expression you want to change:");
	while((nowch=getchar())!='\n'){
	new_expbuf[i++]=nowch;
	}
	new_expbuf[i]='\0';
	if(strcmp(new_expbuf,"@")==0)
		{
		FileReadLine(dictfile, expbuf);
		fflush(tempfile);
		FileWriteLine(tempfile, expbuf);	
	while(expbuf[i]!='\0'){
	expbuf[i++]=0;
	}
		}
	else
		{
		FileReadLine(dictfile, expbuf);
	while(expbuf[i]!='\0'){
	expbuf[i++]=0;
	}
		fflush(tempfile);
		FileWriteLine(tempfile, new_expbuf);	
		}
	}
	
 }
close(dictfile);
close(tempfile);
remove(DEFAULT_FILENAME);
rename(TEMP_FILENAME,DEFAULT_FILENAME);
return flag;
}
