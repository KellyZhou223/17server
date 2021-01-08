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

  //create the two pipes receiver and sender
  mkfifo("sender", 0644);
  mkfifo("receiver", 0644);

  //create read connection to the receiving end
  fd1 = open("receiver", O_RDONLY);

  //create write connection to the sending end
  fd2 = open("sender", O_WRONLY);

  remove("./receiver");

  while (1){

    //read from the receiving end
    int r = read(fd1, line, sizeof(line));

    //process the line (ROT13)
    for (i=0; line[i]; i++){
      if (line[i] >= 'a' && line[i] <= 'z')
        line[i]=(((line[i]+13)-'a')%26)+'a';

      else if (line[i] >= 'A' && line[i] <= 'Z')
        line[i]=(((line[i]+13)-'A')%26)+'A';
    }

    //write processed line to the sending end
    write(fd2, line, sizeof(line));
  }

  return 0;
}
