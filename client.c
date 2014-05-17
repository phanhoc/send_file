#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#define PORT 5000
#define MAXMSG 1024

char packet[MAXMSG];

char* get_file_name(char* path_to_file_name ){
  char* file_name;
  file_name = path_to_file_name;
  if(strstr(path_to_file_name,"/")==NULL){
    fprintf(stdout,"Already file name\n");
  }
  else{
    file_name = strstr(path_to_file_name,"/")+1;
    while(strstr(file_name,"/")!=NULL)
      file_name = strstr(file_name,"/")+1;
  }
  return file_name;
}

void send_file(char *path_to_file_name,int sockfd){
  FILE *fd = fopen(path_to_file_name,"r");
  fseek(fd,0,SEEK_END);
  int size = ftell(fd);
  fseek(fd,0,SEEK_SET);
  if (size%MAXMSG) size = size/MAXMSG + 1;
  else size = size/MAXMSG;
  fprintf(stdout,"Packets : %i\n",size);
  
  char msg[30];
  memset(&msg,'\0', sizeof(msg));
  snprintf(msg,sizeof(msg),"%s",get_file_name(path_to_file_name));
  fprintf(stdout,"%s\n",msg);
  if(send(sockfd,msg,strlen(msg),0)<0) fprintf(stdout,"send name fail");
  usleep(1000);
  
  memset(&msg,'\0', sizeof(msg));
  snprintf(msg,sizeof(msg),"%i",size);
  if (send(sockfd,msg,strlen(msg),0)<0) fprintf(stdout,"send size loi");
  usleep(1000);
  
  int count = 0;
  while(!feof(fd)){
    int wasRead = fread(packet,sizeof(char),MAXMSG,fd);
    send(sockfd,packet,(sizeof(char)*wasRead),0);
    fprintf(stdout,"Count: %i\n",count);
    count++;    
    usleep(1000);
  }
}

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[MAXMSG];    
    struct sockaddr_in serv_addr; 

    if(argc != 3)
    {
        printf("\n Usage: %s <ip of server> <path to file name>\n",argv[0]);
        return 1;
    } 

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)		// khoi tao socket
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 	// khoi tao chi tiet va setup server muon ket noi

    serv_addr.sin_family = AF_INET;	// IPv4
    serv_addr.sin_port = htons(PORT); // setup port

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)	// convert IP
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)	// connect to socket
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
/*
    if ( (n = read(sockfd, recvBuff, sizeof(recvBuff))) > 0)	// nhan du lieu tu server
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    }
*/    
    send_file(argv[2],sockfd);
    
   /* 
   FILE *fd = fopen(argv[2],"r");
   fseek(fd,0,SEEK_END);
   int size = ftell(fd);
   fseek(fd,0,SEEK_SET);
   if (size%MAXMSG) size = size/MAXMSG + 1;
   else size = size/MAXMSG;
   fprintf(stdout,"Packets : %i\n",size);
   
   char msg[30];
   memset(&msg,'\0', sizeof(msg));
   snprintf(msg,sizeof(msg),"%s",get_file_name(argv[2]));
   fprintf(stdout,"%s\n",msg);
   if(send(sockfd,msg,strlen(msg),0)<0) fprintf(stdout,"send name fail");
   usleep(1000);
   
   memset(&msg,'\0', sizeof(msg));
   snprintf(msg,sizeof(msg),"%i",size);
   if (send(sockfd,msg,strlen(msg),0)<0) fprintf(stdout,"send size loi");
   usleep(1000);
   
   int count = 0;
   while(!feof(fd)){
    int wasRead = fread(packet,sizeof(char),MAXMSG,fd);
    send(sockfd,packet,(sizeof(char)*wasRead),0);
    fprintf(stdout,"Count: %i\n",count);
    count++;    
    usleep(1000);
  }
  */
   
   
  //fprintf(stdout,"Count: %i\n",count);   
    /*
    char msg[30] = "giao_trinh_C++.pdf\n";
    if (write(sockfd,msg,strlen(msg))<0) fprintf(stdout,"write loi");
    
    FILE *fd = fopen("/home/dz/Downloads/giao-trinh-lap-trinh-c_dh-mo-tphcm.pdf","r");
    fseek(fd,0,SEEK_END);
    int size = ftell(fd);
    fseek(fd,0,SEEK_SET);
    if (size%MAXMSG) size = size/MAXMSG + 1;
    else size = size/MAXMSG;
    fprintf(stdout,"packets : %i\n\n\n",size);
    
    memset(&msg,0, sizeof(msg));
    snprintf(msg,sizeof(msg),"%i\n",size);
    if (write(sockfd,msg,strlen(msg))<0) fprintf(stdout,"write loi");
    
    
    char ptr[MAXMSG];
    memset(&ptr, 0, sizeof(ptr));    
    int i = 0;
    int result;
    int count = 0;
    
    fflush(stdout);
    */
    
    /*
    
    //while ((result=fread(ptr,1,1024,fd))>0) {
    for (i;i<1;i++) {
      result=fread(ptr,1,1024,fd);
      write(sockfd,ptr,result);
      fprintf(stdout,"%s",ptr);
      fflush(stdout);
      //memset(&ptr, 0, sizeof(ptr));
      count++;
      usleep(10000);
    }
    
    fprintf(stdout,"Count: %i\n",count);
    
    */
    
    //result=fread(ptr,1,1024,fd);
    //fprintf(stdout,"%s\n",ptr);
    //if (send(sockfd,ptr,result,0)>0) fprintf(stdout,"send thanh cong\n");
    
    /*
    while ((result=fread(ptr,1,1024,fd))>0) {
      if (send(sockfd,ptr,result,0)>0) fprintf(stdout,"send thanh cong\n");
      count++;
      if(read(sockfd, recvBuff, sizeof(recvBuff))>0) fprintf(stdout,"%s\n",recvBuff);
    }
    fprintf(stdout,"Count: %i\n",count);
    fprintf(stdout,"Out ch trinh\n");
    */
    return 0;
}
