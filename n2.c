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
#define link1           "link1" //name of named pipe                                                  
#define link3           "link3" //name of named pipe                                                  

#define MAX_BUF_SIZE    30

//n2.c                                                                                                

int main(int argc, char *argv[])
{

  //file descriptors for link pipes                                                                   
  int fd,fe, ret_val, count, numread;
    char buf[MAX_BUF_SIZE];
    char n2m[MAX_BUF_SIZE];
  int f3d,f3e, ret_val3, count3, numread3;
    char buf3[MAX_BUF_SIZE];

    //buffer of n1 message to deliver from nodes 2 to 4                                               

    char buf24[MAX_BUF_SIZE];
    char buf24c[MAX_BUF_SIZE];

	char* inPre;
	int sizePre=0;

	char gluePack[MAX_BUF_SIZE];
	
	int sizeGlue=0;
	int startGlue=0;

	char* inPost;
	int sizePost=0;

	char destNode[MAX_BUF_SIZE];
	int sizeDest=0;

	int packRec=0;
	int packRec4=0;
	int packDRec=0;

    //    char bufAll[6][MAX_BUF_SIZE]={"E","E","E","E","E","E"};                                     
    int sizeb = 0;
    int messRec3=0;


    /* Create the named - pipes for link1 link3*/
    ret_val = mkfifo(link1, 0666);


    if ((ret_val == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit (1);
    }
    ret_val3 = mkfifo(link3, 0666);

    if ((ret_val3 == -1) && (errno != EEXIST)) {
        perror("Error creating the named pipe");
        exit (1);
    }


    /* Create the named - pipe */

    for (;;)
      {
        /*----------------------Link1---------------------*/
    /* Open the pipe for reading */
    fd = open(link1, O_RDONLY);

    /* Read from the pipe */
    numread = read(fd, buf, MAX_BUF_SIZE);

    /* Close the pipe */
    if (close(fd) == -1)
      {
         printf("An n2l1rerror occurred while closing the sr pipe\n");
         //exit(0);                                                                                   
      }

    //copy n1 message to buffer to send to n4                                                         

    buf[numread] = '\0';
    sizeb = strlen(buf);
    strncpy (buf24,buf,sizeb);
    buf24[sizeb]=0;


	//A2******
	//make copy to check for packet strings with destination end

    strncpy (buf24c,buf,sizeb);
    buf24c[sizeb]=0;

	//get packet character

    inPre=strtok(buf24c,",");
    sizePre=strlen(inPre);


	//get destination characters

    inPost=strtok(NULL,",");

	if (inPost != NULL)
	{
//		startGlue=1;

    		sizePost=strlen(inPost);

                strncpy(destNode,inPost,sizePost);
                destNode[sizePost]=0;

                sizeDest=strlen(destNode);
                printf("destnt=%s,%d\n",inPost,sizePost);
                printf("destn=%s,%d\n",destNode,sizeDest);

		//check dest n2

		//if (!strcasecmp(destNode,"n2") && !strcasecmp(inPre,"\n"))

		if (!strcasecmp(destNode,"n2") )
				//n2 dest, start collecting packets
		{

			if ( !strcasecmp(inPre,"\n"))
			{
				printf("received n2:%s\n",gluePack);
				packRec=1;
			}
			else
			{
				if (startGlue ==0 && !strcasecmp(gluePack,"E"))
				{
					//start concatenating new pack message


					startGlue=1;

					strncpy (gluePack,inPre,sizePre);
					gluePack[sizePre]=0;
				}
				else
				{
					//get rest of message

					strncat(gluePack,inPre,sizePre);
				}
				printf("getting n2,%s\n",gluePack);
			}



		} 
		else if (!strcasecmp(destNode,"n4"))
				//n4 dest, start passing packets

		{
			printf("pass n4\n");
		}
		
		if (packRec==1)

		{
			printf("!!Sending Received confirmation to n1\n");
			packRec=0;

			//reset startGlue and gluePack to indicate empty
			//an packet and to start receiving new ones

			startGlue=0;
			strncpy(gluePack,"E",strlen("E"));
			sizeGlue=strlen("E");
			gluePack[sizeGlue]=0;
		}

	}
  else
	//******************* No destination
        {

                sizePost=strlen(" ");

                strncpy(destNode," ",sizePost);
                destNode[sizePost]=0;

                sizeDest=strlen(destNode);
                printf("no destination given\n");

// **********  *continue program like A1 ***************   }



    printf("n2, message : %s received \n", buf);
    //printf("N2 Server : copied pe1 : %s\n", buf24);                                                 

    //-----end copy n1 message to buffer to send to n4                                                


    //****Pass message to n4*******************                                                       

    //****Pass message to n4*******************                                                       


    // Open the pipe for reading                                                                      
    f3e = open(link3, O_WRONLY);

    // Read from the pipe                                                                             
      write(f3e, buf24, strlen(buf24));

      // Close the pipe                                                                               
    if (close(f3e) == -1)
      {
         printf("An n2l3werror occurred while closing the n2 sw pipe\n");
         //exit(0);                                                                                   
      } 






    // Open the pipe for reading                                                                      
    f3d = open(link3, O_RDONLY);

    // Read from the pipe                                                                             
    numread3 = read(f3d, buf3, MAX_BUF_SIZE);

    // Close the pipe                                                                                 
    if (close(f3d) == -1)
      {
         printf("An n2l3rerror occurred while closing the n2 sr pipe\n");
         //exit(0);                                                                                   
      }


    buf3[numread3] = '\0';
//------check received from n4                                                                        


//    if (!strcasecmp(buf3,"N4DONE"))                                                                 
    //    {                                                                                           
    //messRec3 =1;                                                                                    
      //            printf ("n2 :messge from n4 %s link3 received\n",buf3);                           
      //}                                                                                             

      //}                                                                                             




    //****end Pass message to n4*******************                                                   

    //return to pipe 1                                                                                
    /* Open the pipe for reading */
    fe = open(link1, O_WRONLY);




    //--pack message to n1 on behalf of n2 and n4---                                                  

    if (!strcasecmp(buf3,"N4DONE"))
      {//Checks if n4 sent done message                                                               

        //if yes                                                                                      

        sprintf(n2m,"%s,%s","N2DONE",buf3);
        //    write(fe, n2m, strlen(n2m));                                                            

        //      printf("--n2 sending %s\n",n2m);                                                      
      }
    else
      {
        //if no dont send anything                                                                    

        sprintf(n2m,"%s,%s","N2DONE","N4E");
        //      printf("--n2 Not sending %s\n",n2m);                                                  
      }


    //--end pack message---                                                                           



    /* Write to the pipe */
    //      write(fe, "N2DONE", strlen("N2DONE"));                                                    
    write(fe, n2m, strlen(n2m));

    /* Close the pipe */
    if (close(fe) == -1)
      {
         printf("An n2l1werror occurred while closing the n21sw pipe\n");
         //exit(0);                                                                                   
      }
    /*----------------------Link3----------------------*/


    //printf("N2 Server : Read From the pipe3 from n4: %s\n", buf3);                                  






    //-----------------------------------------------                                                 


    if (!strcasecmp(buf,"q") || !strcasecmp(buf,"QUIT"))
        break;

	}//else inPost

      }//for                                                                                          
    exit(0);
}

