#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(){
  int fd1, fd2, i;
  char line[100];

  //open write connection to the receiving end
  fd2 = open("receiver", O_WRONLY);

  //open read connection to the sending end
  fd1 = open("sender", O_RDONLY);

  remove("./sender");

  while (1){

    //prompt user input of a string
    printf("enter a string: \n");
    fgets(line, sizeof(line), stdin);

    //remove new line character from end
    for (i=0; line[i]; i++){
      if (line[i]=='\n')line[i]='\0';
    }

    //write the inputted line to the receiving end
    write(fd2, line, sizeof(line));

    //read the processed line from the sending end
    read(fd1, line, sizeof(line));

    //output the processed message
    printf("Message: [%s]\n", line);
  }

  return 0;
}
