#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*                                                                                                    
 http://developers.sun.com/solaris/articles/named_pipes.html                                          
n */

#define HALF_DUPLEX             "halfduplex" //name of named pipe                                     

#define link3           "link3" //name of named pipe                                                  

#define link4           "link4" //name of named pipe                                                  
#define link5           "link5" //name of named pipe                                                  
#define link6           "link6" //name of named pipe                                                  

#define MAX_BUF_SIZE    30

//n6.c                                                                                                

int main(int argc, char *argv[])
{
  int fd,fe, ret_val, count, numread;
    char buf[MAX_BUF_SIZE];
    char bufn6[MAX_BUF_SIZE];



    /* Check if an argument was specified. */


//Double check pipes                                                                                  

    ret_val = mkfifo(link5, 0666);

    if ((ret_val == -1) && (errno != EEXIST))
        {
        perror("E named pipe exists");
        exit (1);
        perror("E named pipe exists");
        exit (1);
        }


    /* Check if an argument was specified. */





    for (;;)
      {

        // Open the pipe for reading                                                                  
    fd = open(link5, O_RDONLY);

    // Read from the pipe                                                                             
    numread = read(fd, buf, MAX_BUF_SIZE);

    // Close the pipe                                                                                 
    if (close(fd) == -1)
      {
         printf("An n6l5rerror occurred while closing the sr pipe\n");
         //exit(0);                                                                                   
      }


    buf[numread] = '\0';

    printf("n6, message : %s received\n", buf);



    // Open the pipe for writing                                                                      
    fe = open(link5, O_WRONLY);

    // Read from the pipe                                                                             
      write(fe, "N6DONE", strlen("N6DONE"));

      // Close the pipe                                                                               
    if (close(fe) == -1)
      {
         printf("An n6l5werror occurred while closing the sw pipe\n");
         //exit(0);                                                                                   
         printf("An n6l5werror occurred while closing the sw pipe\n");
         //exit(0);                                                                                   
      }



    if (!strcasecmp(buf,"q") || !strcasecmp(buf,"QUIT"))
        break;


      }//for                                                                                          
    exit(0);
}

