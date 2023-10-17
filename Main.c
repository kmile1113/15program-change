#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define DEFAULT_FILENAME "mydict.dat"
#define DEFAULT_HISTORY_FILENAME "history.dat"
#define TEMP_FILENAME "tem.dat"


int main(void){
	int enter;
	printf("***** Welcome to word space ***\n*");
 chmod("login.sh", S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);
                system("./login.sh");

while(1){
		printf("*****************************************************************\n");
		printf("*1.word_dictionary   2.amend_word  3.word_exercise 4.Vocabulary Builder  5.quit    *\n");
		printf("*****************************************************************\n");
		printf("Please choose:");
	scanf("%d",&enter);
	switch(enter)
		{
			case 1:
				ChaXun();
			    break;
			case 2:
				JiaoZhun();
				break;
			case 3:	
				chmod("ex.sh", S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH); 					
				system("./ex.sh");
				break;
			case 4:
				system("cat history.dat");
				break;
			case 5:
				return 0;
			default :
				printf("Invalid data cmd.\n");
		}

   }
}
