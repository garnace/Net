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

//n4.c                                                                                                

int main(int argc, char *argv[])
{
  int fd,fe, ret_val, count, numread;
    char buf[MAX_BUF_SIZE];
    char bufn4[MAX_BUF_SIZE];



    /* Check if an argument was specified. */


//Double check pipes                                                                                  

    ret_val = mkfifo(link3, 0666);

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
    fd = open(link3, O_RDONLY);

    // Read from the pipe                                                                             
    numread = read(fd, buf, MAX_BUF_SIZE);

    // Close the pipe                                                                                 
    if (close(fd) == -1)
      {
         printf("An n4l3rerror occurred while closing the sr pipe\n");
         //exit(0);                                                                                   
      }


    buf[numread] = '\0';

    printf("n4, message : %s received\n", buf);

    /* Convert to the string to upper case                                                            
    count = 0;                                                                                        
    while (count < numread) {                                                                         
        buf[count] = toupper(buf[count]);                                                             
        count++;                                                                                      
    }                                                                                                 
                                                                                                      
    printf("n4 : Converted String3 : %s\n", buf);                                                     
    */
    // Open the pipe for writing                                                                      




    fe = open(link3, O_WRONLY);

    // Read from the pipe                                                                             
      write(fe, "N4DONE", strlen("N4DONE"));

      // Close the pipe                                                                               
    if (close(fe) == -1)
      {
         printf("An n4l3werror occurred while closing the sw pipe\n");
         //exit(0);                                                                                   
      }



    if (!strcasecmp(buf,"q") || !strcasecmp(buf,"QUIT"))
        break;


      }//for                                                                                          
    exit(0);
}

