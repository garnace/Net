
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

#define link2           "link2" //name of named pipe                                                  

#define link4           "link4" //name of named pipe                                                  
#define link5           "link5" //name of named pipe                                                  
#define link6           "link6" //name of named pipe                                                  

#define MAX_BUF_SIZE    30

//n3.c                                                                                                
int main(int argc, char *argv[])
{
 
 
  //file descriptors                                                                                  
  int fd,fe, ret_val, count, numread;
  int f4d,f4e, ret_val4, count4, numread4;
  int f5d,f5e, ret_val5, count5, numread5;
  int f6d,f6e, ret_val6, count6, numread6;
  int sizeb=0;
  int sizeq=0;


  //buffers, buffer sizes                                                                             

  //buf35: buffer to deliver node1 message from node 3 to 5 (later used to send to 6 and 7)           

  char buf35[MAX_BUF_SIZE];


    char buf[MAX_BUF_SIZE];
    char buf4[MAX_BUF_SIZE];
    char buf5[MAX_BUF_SIZE];
    char buf6[MAX_BUF_SIZE];
    char n3m[MAX_BUF_SIZE];
    char n5mess[MAX_BUF_SIZE];
    char n6mess[MAX_BUF_SIZE];
    char n7mess[MAX_BUF_SIZE];

    int messRec4=0;
    int messRec5=0;
    int messRec6=0;


    /* Create the named - pipes 2,4,5,6*/
    ret_val = mkfifo(link2, 0666);

    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit (1);
    }


    ret_val4 = mkfifo(link4, 0666);

    if ((ret_val4 == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit (1);
    }

    ret_val5 = mkfifo(link5, 0666);

    if ((ret_val5 == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit (1);
    }
     
    ret_val6 = mkfifo(link6, 0666);

    if ((ret_val6 == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit (1);
    }




    /* End Create the named - pipe */



    for (;;)
      {

    /* Open the pipe for reading */
    fd = open(link2, O_RDONLY);

    /* Read from the pipe */
    numread = read(fd, buf, MAX_BUF_SIZE);

    /* Close the pipe */
    if (close(fd) == -1)
      {
         printf("An error occurred while closing the n3 link2 sr pipe\n");
         //exit(0);                                                                                   
      } 
    buf[numread] = '\0';

    //--------copy n1 message to buffer to send down network                                          

    sizeb = strlen(buf);
    strncpy (buf35,buf,sizeb);
    buf35[sizeb]=0;
    //    printf("N3 Server : Read From n1 pipe2 : %s\n", buf);                                       
    //printf("N3 Server : copied pe2 : %s\n", buf35);                                                 



    //----copy                                                                                        
     


    printf("n3, message : %s received\n", buf);





    //*********Pass/receive  message to links 4 5 6, or nodes 5,6,7                                   



    //************************************************************                                    

    //---------------------Link4-------------------------                                             




    // Open the pipe for writing                                                                      
    f4e = open(link4, O_WRONLY);

    // Read from the pipe                                                                             
      write(f4e, buf35, strlen(buf35));

      // Close the pipe                                                                               
    if (close(f4e) == -1)
      {                  
         printf("An error occurred while closing the n3 sw pipe\n");
         //exit(0);                                                                                   
      } 




    // Open the pipe for reading                                                                      
    f4d = open(link4, O_RDONLY);

    // Read from the pipe                                                                             
    numread4 = read(f4d, buf4, MAX_BUF_SIZE);

    // Close the pipe                                                                                 
    if (close(f4d) == -1)
      {
         printf("An error occurred while closing the n3 sr pipe\n");
         //exit(0);                                                                                   
      } 


    buf4[numread4] = '\0';
//------check received from n5                                                                        
    buf4[numread4] = '\0';
//------check received from n5                                                                        

    if (!strcasecmp(buf4,"N5DONE"))
      {
      messRec4 =1;
      //      printf ("n3 :messge from n5 %s link3 received\n",buf4);                                 
      }

    //printf("N3 Server : Read From the pipe4 from n5: %s\n", buf4);                                  




    //----------------------Link5                                                                     



    // Open the pipe for writing                                                                      
    f5e = open(link5, O_WRONLY);

    // write to the pipe                                                                              
      write(f5e, buf35, strlen(buf35));

      // Close the pipe                                                                               
    if (close(f5e) == -1)
      {                  
         printf("An error occurred while closing the n3 sw pipe\n");
         //exit(0);                                                                                   
      } 




    // Open the pipe for reading                                                                      
    f5d = open(link5, O_RDONLY);

    // Read from the pipe                                                                             
    numread5 = read(f5d, buf5, MAX_BUF_SIZE);

    // Close the pipe                                                                                 
    if (close(f5d) == -1)
      {
         printf("An error occurred while closing the n3 sr pipe\n");
        // exit(0);                                                                                   
         printf("An error occurred while closing the n3 sr pipe\n");
        // exit(0);                                                                                   
      }


    buf5[numread5] = '\0';
//------check received from n6                                                                        


    if (!strcasecmp(buf5,"N6DONE"))
      {
      messRec5 =1;
      //      printf ("n3 :messge from n6 %s link5 received\n",buf5);                                 
      } 

    //printf("N3 Server : Read From the pipe5 from n6: %s\n", buf5);                                  


    //---End Link5                                                                                    




    //-------------Link6                                                                              


    // Open the pipe for writing                                                                      
    f6e = open(link6, O_WRONLY);

    // write to the pipe                                                                              
      write(f6e, buf35, strlen(buf35));
              
      // Close the pipe                                                                               
    if (close(f6e) == -1)
      {                  
         printf("An error occurred while closing the n3 sw pipe\n");
         //exit(0);                                                                                   
      } 




    // Open the pipe for reading                                                                      

    f6d = open(link6, O_RDONLY);

    // Read from the pipe                                                                             
    numread6 = read(f6d, buf6, MAX_BUF_SIZE);

    // Close the pipe                                                                                 
    if (close(f6d) == -1)
      {
         printf("An error occurred while closing the n3 sr pipe\n");
         //exit(0);                                                                                   
      } 


    buf6[numread6] = '\0';
//------check received from n4                                                                        





    if (!strcasecmp(buf6,"N7DONE"))
      {
      messRec6 =1;
      //      printf ("n3 :messge from n7 %s link6 received\n",buf6);                                 
      }
       
    //printf("N3 Server : Read From the pipe6 from n7: %s\n", buf6);                                  



    //----End Link6                                                                                   
              

    //********* END Pass/receive message to links 4 5 6, or nodes 5,6,7                               

/* Open the pipe for writing */



    fe = open(link2, O_WRONLY);


    //--pack message to n1 on behalf of n5 n6 and n7---                                               

    //check node6                                                                                     

    //check node6                                                                                     
    if (!strcasecmp(buf5,"N6DONE"))
      {
        strncpy (n6mess,"N6DONE",strlen("N6DONE"));
        sizeq = strlen("N6DONE");
        n6mess[sizeq]=0;
      }
    else
      {
        strncpy (n6mess,"N6E",strlen("N6E"));
        sizeq = strlen("N6E");
        n6mess[sizeq]=0;
      }
    //check node7                                                                                     

    if (!strcasecmp(buf6,"N7DONE"))
      {
        strncpy (n7mess,"N7DONE",strlen("N7DONE"));
        sizeq = strlen("N7DONE");
        n7mess[sizeq]=0;
      }
    else
      {
        strncpy (n7mess,"N7E",strlen("N7E"));
        sizeq = strlen("N7E");
        n7mess[sizeq]=0;
      }
       
    //check node5                                                                                     

              
    if (!strcasecmp(buf4,"N5DONE"))
      {//Checks if n4 sent done message                                                               

        //if yes                                                                                      

        strncpy (n5mess,"N5DONE",strlen("N5DONE"));
        sizeq = strlen("N5DONE");
        n5mess[sizeq]=0;



        //      sprintf(n3m,"%s,%s","N3DONE",buf4);                                                   
        //      printf("--n3 sending %s\n",n3m);                                                      
        //      sprintf(n3m,"%s,%s","N3DONE",buf4);                                                   
        //      printf("--n3 sending %s\n",n3m);                                                      
      }
    else
      {
        //if no                                                                                       

        strncpy (n5mess,"N5E",strlen("N5E"));
        sizeq = strlen("N5E");
        n5mess[sizeq]=0;



        //      sprintf(n3m,"%s,%s","N3DONE","N5E");                                                  
        //      printf("--n3 Not sending %s\n",n3m);                                                  
      }

    //pack message for n1 to receive from link 2                                                      

    sprintf(n3m,"%s,%s,%s,%s","N3DONE",n5mess,n6mess,n7mess);


    //--end pack message---                                                                           



    //      write(fe, "N3DONE", strlen("N3DONE"));                                                    
    write(fe, n3m, strlen(n3m));
       
    /* Close the pipe */
    if (close(fe) == -1)
      {       
         printf("An error occurred while closing the sw pipe\n");
         //exit(0);                                                                                   
      }



    if (!strcasecmp(buf,"q") || !strcasecmp(buf,"QUIT"))
        break;


      }//for                                                                                          
    exit(0);
}

