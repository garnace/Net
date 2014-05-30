/*******************************                                                                      
COURSE:CIS 3210                                                                                       
PROGRAM:n1.c                                                                                          
AUTHOR:Aiken Van Spyk                                                                                 
                                                                                                      
DESCRIPTION:                                                                                          
This program is the first of a 7 nodes network program and makes use                                  
of course sample client server code.                                                                  
                                                                                                      
 **************************/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*                                                                                                    
 http://developers.sun.com/solaris/articles/named_pipes.html                                          
 */

#define HALF_DUPLEX             "halfduplex" //name of named pipe                                     
#define link1           "link1" //name of named pipe                                                  
#define link2           "link2" //name of named pipe                                                  
       
//#define MAX_BUF_SIZE  255                                                                           
#define MAX_BUF_SIZE    30




    /* Create the named - pipes 2,4,5,6                                                               
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
                                                                                                      
*/




int main(int argc, char *argv[])
{      
  //file descriptors                                                                                  

  int fd,fe;
  int f2d,f2e;
    int ret_val, count, numread;
    int ret_val2, count2, numread2;

    //buffers                                                                                         

    char buf2[MAX_BUF_SIZE];
    char buf[MAX_BUF_SIZE];
    char bufs[MAX_BUF_SIZE];
    char bufs2[MAX_BUF_SIZE];
    char bufs3[MAX_BUF_SIZE];
    char bufsn5[MAX_BUF_SIZE];
    char bufs3[MAX_BUF_SIZE];
    char bufsn5[MAX_BUF_SIZE];
    char bufsn3[MAX_BUF_SIZE];
    char bufn2[MAX_BUF_SIZE];
    char bufn2a[MAX_BUF_SIZE];
    char messPack24[MAX_BUF_SIZE];
    char messPack35[MAX_BUF_SIZE];


    //List of node buffers of messages returned intitialized to 'E"                                   
    //Contains NXDONE if node received message otherwise NXE                                          

    char bufAll[6][MAX_BUF_SIZE]={"E","E","E","E","E","E"};

        //Temporary User input buffer before space token                                              



        char tempCheck[MAX_BUF_SIZE];
        //char*  tempU;                                                                               
        int sizeCheck=0;


        char* tempCheckS;
        //char*  tempU;                                                                               
        int sizeCheckS=0;

        char tempU[MAX_BUF_SIZE];
        //char*  tempU;                                                                               
        int sizeU=0;

        //char tempU[MAX_BUF_SIZE];                                                                   
        char*  tempUU;
        int sizeUU=0;
        //input before space                                                                          

        //char inPre[MAX_BUF_SIZE];                                                                   
        char* inPre;
        int sizePre=0;



        char inPrePack[MAX_BUF_SIZE];
        //char* inPre;                                                                                
        int sizePrePack=0;
        //char* inPre;                                                                                
        int sizePrePack=0;

        //Temporary User input buffer before space token                                              

//      char fullPack[MAX_BUF_SIZE];                                                                  
        char* fullPack;
        int sizefPack=0;

    //node buffers parsed from messages                                                               

    char* tempB;
    char* tempBN3;
    char* tempBN5;
    char* tempBN6;
    char* tempBN7;
    char* tempC;


    //not really used                                                                                 
    char* tempCN3;
    char* tempCN5;
    char* tempCN6;
    char* tempCN7;

    //message received flags for link1, link2                                                         
    int messRec=0;
    int messRec2=0;


    //node buffer lengths                                                                             
    int sizetB=0;
    int sizetBN3=0;
    int sizetBN5=0;
    int sizetBN6=0;
    int sizetBN7=0;
    int sizetC=0;

    //not really used                                                                                 
    int sizetCN3=0;
    int sizetCN5=0;
    int sizetCN6=0;
    int sizetCN7=0;

    //user text buffers and lengths                                                                  

    //user text buffers and lengths                                                                   
    int sizetBuf=0;
    int suL=0;
    char userLine[MAX_BUF_SIZE];
    char userL[MAX_BUF_SIZE];
    char userLC[MAX_BUF_SIZE];
    char destNode[MAX_BUF_SIZE];
    char* destNodeT;

        int countr=0;
        int sizeDestT=0;
        int sizePack=0;
        int sizePack2=0;
        int sizeDest=0;
        int sizeDest2=0;
        int countPack24=0;
        int countPack35=0;

    /* Check if an argument was specified. */


//Double check pipes                                                                                  

    ret_val = mkfifo(link2, 0666);

    if ((ret_val == -1) && (errno != EEXIST))
        {
        perror("E named pipe exists");
        exit (1);
        }


    /* Check if an argument was specified. */




    ret_val2 = mkfifo(link1, 0666);

    if ((ret_val == -1) && (errno != EEXIST))
        {
        perror("E named pipe exists");
        exit (1);
        }
        exit (1);
        }





    if (argc != 2) {
        printf("Usage : %s <string to be sent to the server>\n", argv[0]);
        exit (1);
    }


//      sleep(1);                                                                                     
        printf("Enter text to send, or q to quit\n");

//use fgets for spaces                                                                                
   // scanf ("%s",&userLine);                                                                         
    fgets (userLine,sizeof userLine,stdin);
    suL=strlen( userLine);
    userLine[suL-1]='\0';

    suL=strlen( userLine);

    printf("wrote %s,%d\n",userLine,suL);
        printf("wrote %c\n",userLine[0]);


    //strncpy (bufs,buf,numread);                                                                     
    strncpy (userLC,userLine,suL);

    userLC[suL]=0;

    sizePack=strlen(userLC);

    printf("copied %s size %d\n",userLC,sizePack);
    destNode[0]=userLC[sizePack-2];
    destNode[1]=userLC[sizePack-1];
    destNode[2]=0;

        sizeDest=strlen(destNode);
    printf("destNode %s size %d,%d\n",destNode,sizePack,sizeDest);

        if (suL >1 )
        for (countr=0;countr< suL ;countr++)
        if (suL >1 )
        for (countr=0;countr< suL ;countr++)
        {
                printf("wr---%c\n",userLine[countr]);
        }
//      exit(0);                                                                                      
    //loop through links until quit                                                                   
    for (;;)

      {
        //check link 1 and link2 for message received flags for sub nodes                             
        //being done.                                                                                 

        if (messRec2 ==1 && messRec ==1)
          {
        printf("All nodes confirmed done:\n");
        //reset                                                                                       

          messRec2 = 0;
        messRec = 0;

          }




        //wait to allow node confirmations messages to finish                                         

//      sleep(1);                                                                                     
        printf("Enter text to send, or q to quit\n");

//use fgets for spaces                                                                                
   // scanf ("%s",&userLine);                                                                         
    fgets (userLine,sizeof userLine,stdin);
    suL=strlen( userLine);
    userLine[suL-1]=0;

    suL=strlen( userLine);


    //strncpy (bufs,buf,numread);                                                                     
    strncpy (userLC,userLine,suL);

    userLC[suL]=0;
    userLC[suL]=0;

        tempUU=&userLine[0];
        printf("tempUU=%s\n",tempUU);

//      strncpy (tempU,userLine,suL);                                                                 
//      tempU[suL]=0;                                                                                 
     inPre  = strtok(tempUU," ");
    sizePre = strlen(inPre);

    sizePack=strlen(inPre);
        printf("inPre=%s,%d\n",inPre,sizePre);


        strncpy(inPrePack,inPre,sizePack);
        inPrePack[sizePack]=0;


        //check that destination is given                                                             

        destNodeT=strtok(NULL," ");
        if (destNodeT !=NULL)
        {
                sizeDestT=strlen(destNodeT);

                strncpy(destNode,destNodeT,sizeDestT);
                destNode[sizeDestT]=0;

                sizeDest=strlen(destNode);
                printf("destnt=%s,%d\n",destNodeT,sizeDestT);
                printf("destn=%s,%d\n",destNode,sizeDest);
        }
        else
        {

                sizeDestT=strlen(" ");

                strncpy(destNode," ",sizeDestT);
                destNode[sizeDestT]=0;

                sizeDest=strlen(destNode);
                printf("no destination given\n");
        }

//      strncpy(destNode,destNodeT,sizeDestT);                                                        

//      strncpy(destNode,destNodeT,sizeDestT);                                                        
//      destNode[sizeDestT]=0;                                                                        


   // sizePack=strlen(inPre);                                                                         

    printf("copied %s size %d,sul%d\n",userLC,sizePack,suL);
    //destNode[0]=userLC[sizePack-2];                                                                 
    //destNode[1]=userLC[sizePack-1];                                                                 
    //destNode[2]=0;                                                                                  
//      sizeDest=strlen(destNode);                                                                    
    printf("destNode %s size %d,%d\n",destNode,sizePack,sizeDest);

    if (!strcasecmp(destNode,"n2") || !strcasecmp(destNode,"n4"))
        {
                printf("proceed n24 loop:%s\n",destNode);
                for (countPack24=0;countPack24<sizePack +1;countPack24++)
                {
                //sprintf(messPack24,"%c,%s\n",userLC[countPack24],destNode);                         
                if (countPack24==sizePack)
                sprintf(messPack24,"%c,%s\n",'\n',destNode);
                else
                sprintf(messPack24,"%c,%s\n",inPrePack[countPack24],destNode);

                printf("sent %s,part of %s\n",messPack24,inPrePack);
                }
                //if (inPrePack[sizePack]==0)                                                         

                if (inPrePack[sizePack]==0)
                        printf("end of pack\n");
                printf("sent %s,part of %s\n",messPack24,inPrePack);
                tempCheckS=strtok(messPack24,",");
                if (!strcasecmp(tempCheckS,"\n"))
                        printf("End of pack parsed\n");
        }


    else if (!strcasecmp(destNode,"n3") || !strcasecmp(destNode,"n5")|| !strcasecmp(destNode,"n6") ||\
 !strcasecmp(destNode,"n7"))
        {
                printf("proceed n35 loop:%s\n",destNode);
        }
    else if (!strcasecmp(userLine,"q") || !strcasecmp(userLine,"QUIT"))//multicast q                  
        {
    else if (!strcasecmp(userLine,"q") || !strcasecmp(userLine,"QUIT"))//multicast q                  
        {

    /*  client-serv modified--------------------*/

    /* Open the pipe for writing                                                                      
    if (!strcasecmp(userLine,"q") || !strcasecmp(userLine,"QUIT"))                                    
        break;                                                                                        
    */



    //******************* begin pipe links ******************                                         


    /*--------------------Link1---------------------------*/
            fd = open(link1, O_WRONLY);
            //    fd = open(HALF_DUPLEX, O_RDONLY);                                                   

    /* Write to the pipe */
    //write(fd, argv[1], strlen(argv[1]));                                                            
            write(fd,userLine ,strlen(userLine));
            //    numread = read(fd, buf, MAX_BUF_SIZE);                                              

    //close(fd);                                                                                      
        if (close(fd)== -1)
          {
         printf("An n1 l1error occurred while closing the cw pipe\n");
         //exit(0);                                                                                   

          }




        //sleep(5);                                                                                   
        //sleep(1);                                                                                   
        //      while (messRec ==0)                                                                   
        //{                                                                                           

    fe = open(link1, O_RDONLY);

    /* Read from the pipe */
    numread = read(fe, buf, MAX_BUF_SIZE);

    numread = read(fe, buf, MAX_BUF_SIZE);

    /* Close the pipe */
    if (close(fe) == -1)
      {
         printf("An n1l1readerror occurred while closing thecr pipe\n");
         //exit(0);                                                                                   
      }


    buf[numread] = '\0';

    //    (char*)&(bufn2[0])  = strtok((char *)buf,",");                                              
    strncpy (bufs,buf,numread);



    //********Parse string for passed messages from n2 and n4                                         

    //**Parse n2                                                                                      

    bufs[numread]=0;
     tempB  = strtok(buf,",");
    sizetB = strlen(tempB);
    //change    strncpy (bufn2,tempB,sizetB);                                                         
    strncpy (bufAll[0],tempB,sizetB);
    //bufn2[sizetB]=0;                                                                                
    bufAll[0][sizetB]=0;

    //**Parse n4                                                                                      

    tempC  = strtok(NULL,",");
    sizetC = strlen(tempC);
    //change strncpy (bufn2a,tempC,sizetC);                                                           
    strncpy (bufAll[2],tempC,sizetC);
    //bufn2a[sizetC]=0;                                                                               
    bufAll[2][sizetC]=0;






    //check for confirmation of node2                                                                 

    //check for confirmation of node2                                                                 



      if (!strcasecmp(bufAll[0],"N2DONE"))
      {

        //modify message received flag                                                                

      messRec =1;
      // printf ("Confirmation received: from n2 link1 %s;%s received\n",bufs,bufAll[0]);             
      printf ("N1: Confirmation received: from n2 link1 sub-nodes :%s;%s received messages\n",bufAll[\
0],bufAll[2]);
      }
      else
      {   
      messRec =0;
      //      printf ("Confirmation NOT received: from n2 link1 %s;%s received\n",bufs,bufAll[0]);    
      printf ("Confirmation NOT received: from n2 link1 %s;%s received\n",bufAll[0],bufAll[2]);
      }
      //          }//messRec                                                                          


    /*---------------------Link2------------------------*/


            f2d = open(link2, O_WRONLY);
            //    fd = open(HALF_DUPLEX, O_RDONLY);                                                   

            // Write to the pipe                                                                      

            write(f2d,userLine ,strlen(userLine));
            //    numread = read(fd, buf, MAX_BUF_SIZE);                                              

    //close(fd);                                                                                      
        if (close(f2d)== -1)
          {
         printf("An n1l2werror occurred while closing the cw pipe\n");
         //exit(0);                                                                                   

          }


        //Wait for response                                                                           

        //Wait for response                                                                           

        //sleep(5);                                                                                   
        //      while (messRec2==0)                                                                   
        //{                                                                                           

    f2e = open(link2, O_RDONLY);

    // Read from the pipe                                                                             
    numread2 = read(f2e, buf2, MAX_BUF_SIZE);

    // Close the pipe                                                                                 
    if (close(f2e) == -1)
      {
         printf("An n1l2rerror occurred while closing the n1 link2 cr pipe\n");
         //exit(0);                                                                                   
      }


    buf2[numread2] = '\0';


    //----------get parse of n3                                                                       
    //first save copy in bufs2                                                                        

    strncpy (bufs2,buf2,numread2);

    //********Parse string for passed messages from n2 and n4                                         

    //**Parse n3                                                                                      

    bufs2[numread2]=0;
     tempBN3  = strtok(buf2,",");
    sizetBN3 = strlen(tempBN3);
    //change    strncpy (bufn2,tempB,sizetB);                                                         
    strncpy (bufAll[1],tempBN3,sizetBN3);
    //bufn2[sizetB]=0;                                                                                
    bufAll[1][sizetBN3]=0;

    //---parse n5                                                                                     

    tempBN5  = strtok(NULL,",");
    sizetBN5 = strlen(tempBN5);
    //change strncpy (bufn2a,tempC,sizetC);                                                           
    strncpy (bufAll[3],tempBN5,sizetBN5);
    //change strncpy (bufn2a,tempC,sizetC);                                                           
    strncpy (bufAll[3],tempBN5,sizetBN5);
    //bufn2a[sizetC]=0;                                                                               
    bufAll[3][sizetBN5]=0;

    //---parse n6                                                                                     

    tempBN6  = strtok(NULL,",");
    sizetBN6 = strlen(tempBN6);
    //change strncpy (bufn2a,tempC,sizetC);                                                           
    strncpy (bufAll[4],tempBN6,sizetBN6);
    //bufn2a[sizetC]=0;                                                                               
    bufAll[4][sizetBN6]=0;

    //---parse n7                                                                                     

    tempBN7  = strtok(NULL,",");
    sizetBN7 = strlen(tempBN7);
    //change strncpy (bufn2a,tempC,sizetC);                                                           
    strncpy (bufAll[5],tempBN7,sizetBN7);
    //bufn2a[sizetC]=0;                                                                               
    bufAll[5][sizetBN7]=0;



    //Confirm                                                                                         

    //    printf ("Confirmation: from n3 link2 sub-nodes :%s;%s;%s;%s;%s received messages\n",bufs2,b\
ufAll[1],bufAll[3],bufAll[4],bufAll[5]);                                                              



    //-------end parse of n5                                                                          


    //check nodes 4,5,6,7 are done, then set messRec2 flag to 1 if they are                           
    if (!strcasecmp(bufAll[1],"N3DONE") && !strcasecmp(bufAll[3],"N5Done") && !strcasecmp(bufAll[4],"\
N6DONE") && !strcasecmp(bufAll[5],"N7DONE"))
      {

        //    printf ("Confirmation: from n3 link2 sub-nodes :%s;%s;%s;%s;%s received messages\n",buf\
s2,bufAll[1],bufAll[3],bufAll[4],bufAll[5]);                                                          
    printf ("N1: Confirmation received: from n3 link2 sub-nodes :%s;%s;%s;%s received messages\n",buf\
All[1],bufAll[3],bufAll[4],bufAll[5]);

All[1],bufAll[3],bufAll[4],bufAll[5]);

      messRec2 =1;

      }
    else
      { 


        printf ("N1: Waiting confirmations from n3 link2 sub-nodes:%s\n",bufs2);

      messRec2 =0;
      // printf ("messge from n3 link2 %s received\n",bufAll[1]);                                     
      } 

    //    }//messRec2                                                                                 


      /*    */


/* Open the pipe for writing */
//    if (!strcasecmp(userLine,"q") || !strcasecmp(userLine,"QUIT"))                                  
    if ((!strcasecmp(userLine,"q") || !strcasecmp(userLine,"QUIT")) && (messRec2 == 1) && (messRec ==\
 1))
      {
        printf("All nodes confirmed done: shutting down now on quit\n");
        break;
      }
       
        }// multicast q                                                                               

    }//for                                                                                            

    exit(0);
}

