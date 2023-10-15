//Handles the account, its type (admin/faculty/student), checks if the user is the right person by authentication and takes a reference of the current user
bool login_handler(bool isAdmin, bool isFaculty, int connFD, struct faculty *ptrTofID, struct student *ptrTosID)
{    
    ssize_t readBytes, writeBytes;            
    char readBuffer[1024];
    struct message msg;
    char tempBuffer[1024];
    struct faculty f;
    struct student s;

    memset(msg.buff, 0,sizeof(msg.buff));
    memset(readBuffer, 0,sizeof(readBuffer));        
    strcpy(msg.buff, "-------------------Please Enter credentials for Login-------------------\nEnter login ID: ");
    msg.response=1;
   	write(connFD, &msg, sizeof(msg));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
   
    bool userFound = false;
    if(isAdmin)
    {
        if (strcmp(readBuffer,ADMIN_LOGIN_ID) == 0)
            userFound = true;
    }
    else if(isFaculty)
    {      
        memset(tempBuffer, 0,sizeof(tempBuffer));        
        strcpy(tempBuffer, readBuffer);  
        //Getting the id from Login id     
        int i=0;
		while(readBuffer[i]!='_')
	    	i++;
        for(int j=i+1,k=0;j<strlen(readBuffer)+1;j++,k++)
             tempBuffer[k]=readBuffer[j];    
    	int ID=atoi(tempBuffer);
    	
        int facfd = open("./records/faculty", O_RDONLY);
        if (facfd == -1 || ID == 0)
        {   
        	memset(msg.buff, 0,sizeof(msg.buff));
            strcpy(msg.buff,"Invalid action!! Reopen application...\n" );
            msg.response=0;
            write(connFD, &msg, sizeof(msg));           
            perror("Error opening faculty file in read mode!");
			return false;
        }
        
        //offset check
        off_t end=lseek(facfd,0,SEEK_END);
        off_t offset = lseek(facfd, (ID-1) * sizeof(struct faculty), SEEK_SET);
        if (offset >= 0 && end > offset)
        {          
            struct flock readlock; 
			readlock.l_type = F_RDLCK; 
			readlock.l_whence = SEEK_SET; 
			readlock.l_start = offset; 
			readlock.l_len = sizeof(struct faculty); 
			readlock.l_pid = getpid(); 
			        
        	int lockingStatus = fcntl(facfd, F_SETLKW, &readlock);           
            readBytes = read(facfd, &f, sizeof(struct faculty));
            readlock.l_type = F_UNLCK;
            fcntl(facfd, F_SETLK, &readlock);            
            
		    if(strcmp(f.f_login_id, readBuffer) == 0)
		    	userFound = true;
		    close(facfd);
        }
        else
        {   
        	memset(msg.buff, 0,sizeof(msg.buff));
        	strcpy(msg.buff, "Invalid login id!! Reopen the application....\n");
            msg.response=0;           
            write(connFD, &msg, sizeof(msg));
        }
    }
    
    else
    {      
        memset(tempBuffer, 0,sizeof(tempBuffer));        
        strcpy(tempBuffer, readBuffer);  
        //Getting the id from Login id     
        int i=0;
		while(readBuffer[i]!='_')
	    	i++;
        for(int j=i+1,k=0;j<strlen(readBuffer)+1;j++,k++)
             tempBuffer[k]=readBuffer[j];    
    	int ID=atoi(tempBuffer);
    	
        int studfd = open("./records/student", O_RDONLY);
        if (studfd == -1 || ID == 0)
        {   
        	memset(msg.buff, 0,sizeof(msg.buff));
            strcpy(msg.buff,"Invalid action!! Reopen application...\n" );
            msg.response=0;
            write(connFD, &msg, sizeof(msg));           
            perror("Error opening student file in read mode!");
			return false;
        }
        
        //offset check
        off_t end=lseek(studfd,0,SEEK_END);
        off_t offset = lseek(studfd, (ID-1) * sizeof(struct student), SEEK_SET);
        if (offset >= 0 && end > offset)
        {          
            struct flock readlock; 
			readlock.l_type = F_RDLCK; 
			readlock.l_whence = SEEK_SET; 
			readlock.l_start = offset; 
			readlock.l_len = sizeof(struct faculty); 
			readlock.l_pid = getpid(); 
			        
        	int lockingStatus = fcntl(studfd, F_SETLKW, &readlock);           
            readBytes = read(studfd, &s, sizeof(struct student));
            readlock.l_type = F_UNLCK;
            fcntl(studfd, F_SETLK, &readlock);            
		    if(strcmp(s.s_login_id, readBuffer) == 0)
		    	userFound = true;
		    close(studfd);
        }
        else
        {   
        	memset(msg.buff, 0,sizeof(msg.buff));
        	strcpy(msg.buff, "Invalid login id!! Reopen the application....\n");
            msg.response=0;           
            write(connFD, &msg, sizeof(msg));
        }
    }
    
    if (userFound)
    {
        memset(msg.buff, 0,sizeof(msg.buff));      
        strcpy(msg.buff,"Enter your password: " );
        msg.response=1;
        write(connFD, &msg, sizeof(msg));        
        memset(readBuffer, 0,sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));
                
        if (isAdmin)
        {
            if (strcmp(readBuffer, ADMIN_PASSWORD) == 0)
                return true;
        }
        else if(isFaculty)
        {
            if (strcmp(readBuffer, f.f_password) == 0)
            {
            	*ptrTofID = f;
                return true;
            }
        }
        else
        {
            if (strcmp(readBuffer, s.s_password) == 0)
            {
            	*ptrTosID = s;
                return true;
            }
        }
        memset(msg.buff, 0,sizeof(msg.buff));       
        strcpy(msg.buff,"Invalid password for the given id!! Reopen the applicaton....\n" );
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
    }
    else
    {
        memset(msg.buff, 0,sizeof(msg.buff));     
        strcpy(msg.buff,"Invalid log-in ID!! Reopen the application...\n" );
        msg.response=0;
        write(connFD, &msg, sizeof(msg));   
    }    
    return false;
}
