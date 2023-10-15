bool update_seats(int connFD);
bool remove_course(int connFD);
bool modify_course_details(int connFD);

//Professor removes a course from his teaching courses
bool remove_course(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1024];
    struct message msg;
    struct course c[50];
    struct course newc[50];
    size_t struct_size = sizeof(struct course);
    int num_elements = 0;
    int lockingStatus, k=0;
    off_t offset;
    char code[20];

    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter Course Code:\n" );
    msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(code,readBuffer);

    int course_fd = open("./records/courses", O_RDONLY);
    if (course_fd == -1 || strlen(code)==0)
    {
        // Student File doesn't exist       
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"No course exists...\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        return false;
    }
    
    struct flock readlock;
    readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = 0; 
	readlock.l_len = 0; 
	readlock.l_pid = getpid(); 
    lockingStatus = fcntl(course_fd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the courses file!\n");
        return false;
    }
    
    while (read(course_fd, &c[num_elements], sizeof(struct course)) != 0) {
        num_elements++;
    }

    // Release the lock when you're done.
    readlock.l_type = F_UNLCK;
    int unlockingStatus = fcntl(course_fd, F_SETLK, &readlock);
    if (unlockingStatus == -1) 
    {
        perror("Error while releasing read lock on the courses file!\n");
        return false;
    }
		
	if(num_elements == 0)
	{
		memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"No courses found..!!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));   
        return false;
	}
	bool found = false;
	memset(msg.buff, 0,sizeof(msg.buff));
	for (size_t i = 0; i < num_elements; i++) 
	{
		//Teacher is teaching the course and given course found, then update details
        if(strcmp(c[i].cfac_id, login_fac.f_login_id) == 0 && strcmp(c[i].c_code,code) == 0)
        {
        	found = true;
        	continue;
        }
        else
        	newc[k++] = c[i];       
    }
    if(found==false)
	{
		memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Given course not found in courses you are teaching..!!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));   
        return false;
	}
	
	course_fd = open("./records/courses", O_WRONLY);
    if (course_fd == -1)
    {
        perror("Error while opening courses file!\n");
        return false;
    }
    
    //Taking mandatory lock as changing the whole file
    readlock.l_type = F_WRLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = 0; 
	readlock.l_len = 0; 
	readlock.l_pid = getpid(); 
    lockingStatus = fcntl(course_fd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining write lock on the courses file!\n");
        return false;
    }
    
    // Write the modified data back to the file
    lseek(course_fd, 0, SEEK_SET);
    for(int i=0;i<k;i++)
    	write(course_fd, &newc[i], sizeof(struct course));
    	
    // Release the lock when you're done.
    readlock.l_type = F_UNLCK;
   	unlockingStatus = fcntl(course_fd, F_SETLK, &readlock);
    if (unlockingStatus == -1) 
    {
        perror("Error while releasing read lock on the courses file!\n");
        return false;
    }
    close(course_fd);    
	memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Course Removed!! Redirecting to the main menu...!\n");
    msg.response=0;
    write(connFD, &msg, sizeof(msg));
    return true;
}


//Professor edit the course details
bool modify_course_details(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1024];
    struct message msg;
    struct course c[50];
    size_t struct_size = sizeof(struct course);
    int num_elements = 0;
    int lockingStatus;
    off_t offset;
    char code[20];

    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter Course Code:\n" );
    msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(code,readBuffer);

    int course_fd = open("./records/courses", O_RDONLY);
    if (course_fd == -1 || strlen(code)==0)
    {
        // Student File doesn't exist       
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"No course exists...\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        return false;
    }
    
    struct flock readlock;
    readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = 0; 
	readlock.l_len = 0; 
	readlock.l_pid = getpid(); 
    lockingStatus = fcntl(course_fd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the courses file!\n");
        return false;
    }
    
    while (read(course_fd, &c[num_elements], sizeof(struct course)) != 0) {
        num_elements++;
    }

    // Release the lock when you're done.
    readlock.l_type = F_UNLCK;
    int unlockingStatus = fcntl(course_fd, F_SETLK, &readlock);
    if (unlockingStatus == -1) 
    {
        perror("Error while releasing read lock on the courses file!\n");
        return false;
    }
		
	if(num_elements == 0)
	{
		memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"No courses found..!!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));   
        return false;
	}
	bool found = false;
	memset(msg.buff, 0,sizeof(msg.buff));
	strcpy(msg.buff,"\n----------------- Courses Old Details -------------------- \n");
	for (size_t i = 0; i < num_elements; i++) 
	{
		//Teacher is teaching the course and given course found, then remove that course
        if(strcmp(c[i].cfac_id, login_fac.f_login_id) == 0 && strcmp(c[i].c_code,code) == 0)
        {
        	found = true;
        	sprintf(msg.buff + strlen(msg.buff), "\tCourse Name: %s\n\tCourse Code: %s\n\tCourse Credit : %d\n\tTotal Seats: %d\n\tAvailable seats : %d\n\n",\
c[i].c_name, c[i].c_code, c[i].c_credit, c[i].total_seats, c[i].avail_seats);
			msg.response=0;
			write(connFD, &msg, sizeof(msg)); 
			
			memset(msg.buff, 0,sizeof(msg.buff));    
    		strcpy(msg.buff,"Select the information you wish to modify:\n1. Course Name\n2. Course Code\n3. Course Credit\n4. Total Seats\nEnter your choice: " );
			msg.response=1;
			write(connFD, &msg, sizeof(msg));   
			readBytes = read(connFD, readBuffer, sizeof(readBuffer));
			int choice = atoi(readBuffer);
			if (choice == 0)
			{ 
				// A non-numeric string was passed to atoi
				memset(msg.buff, 0,sizeof(msg.buff));        
				strcpy(msg.buff, "Invalid choice...!! Redirecting to the main menu...!\n");        
				msg.response=0;
				write(connFD, &msg, sizeof(msg));        
				return false;
			}    
    
			memset(readBuffer, 0,sizeof(readBuffer));
			switch (choice)
			{
			case 1:
				memset(msg.buff, 0,sizeof(msg.buff));
    			strcpy(msg.buff, "Enter course's new name: ");
				msg.response=1;
				write(connFD, &msg, sizeof(msg));
				readBytes = read(connFD, readBuffer, sizeof(readBuffer));
				strcpy(c[i].c_name, readBuffer); 
				break;
			case 2:    
				memset(msg.buff, 0,sizeof(msg.buff));
				strcpy(msg.buff,"Enter course's new code: ");
				msg.response=1;
				write(connFD, &msg, sizeof(msg));
				memset(readBuffer, 0,sizeof(readBuffer));
				readBytes = read(connFD, readBuffer, sizeof(readBuffer));
			   	strcpy(c[i].c_code, readBuffer); 
			   	break;
			case 3:
				memset(msg.buff, 0,sizeof(msg.buff));
				strcpy(msg.buff,"Enter course's new credit: ");
			  	msg.response=1;
				write(connFD, &msg, sizeof(msg));    
				memset(readBuffer, 0,sizeof(readBuffer));
				readBytes = read(connFD, readBuffer, sizeof(readBuffer));
				int cred;
				if (is_numeric(readBuffer))
					cred = atoi(readBuffer); // Now, fAge contains the integer value
				else
					cred=-1;     
				if (cred <= 0)
				{
					// Either client has sent age as 0 (which is invalid) or has entered a non-numeric string 
					memset(msg.buff, 0,sizeof(msg.buff));
					strcpy(msg.buff, "Invalid Credit!! Redirecting to the main menu...!\n");      
					msg.response=0;
					write(connFD, &msg, sizeof(msg));       
					return false;
    			}
    			c[i].c_credit = cred;
    			break;
    		case 4:    
				memset(msg.buff, 0,sizeof(msg.buff));
				strcpy(msg.buff,"Enter course's new total seats: ");
			  	msg.response=1;
				write(connFD, &msg, sizeof(msg));    
				memset(readBuffer, 0,sizeof(readBuffer));
				readBytes = read(connFD, readBuffer, sizeof(readBuffer));
				int tot_seats, old_seats = c[i].total_seats;
				if (is_numeric(readBuffer))
					tot_seats = atoi(readBuffer); 
				else
					tot_seats = -1;     
				if (tot_seats <= 0)
				{
					// Either client has sent age as 0 (which is invalid) or has entered a non-numeric string 
					memset(msg.buff, 0,sizeof(msg.buff));
					strcpy(msg.buff, "Invalid No. of Seats!! Redirecting to the main menu...!\n");      
					msg.response=0;
					write(connFD, &msg, sizeof(msg));       
					return -1;
				}   
				c[i].total_seats = tot_seats;
				
				//Seats increased, no problem
				if(tot_seats >= old_seats)
					c[i].avail_seats = tot_seats;
				//enrolled students needs to be handled
				else
				{
					c[i].avail_seats = tot_seats;	
					bool up = update_seats(connFD);
				}
				break;	
			default:        
				memset(msg.buff, 0,sizeof(msg.buff));
				strcpy(msg.buff, "Invalid Choice!! Redirecting to the main menu...!\n");      
				msg.response=0;
				write(connFD, &msg, sizeof(msg));
				return false;
    		}	
    		break;	
        }
    }
    if(found==false)
	{
		memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Given course not found in courses you are teaching..!!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));   
        return false;
	}
	
	course_fd = open("./records/courses", O_WRONLY);
    if (course_fd == -1)
    {
        perror("Error while opening courses file!\n");
        return false;
    }
    
    //Taking mandatory lock as changing the whole file
    readlock.l_type = F_WRLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = 0; 
	readlock.l_len = 0; 
	readlock.l_pid = getpid(); 
    lockingStatus = fcntl(course_fd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining write lock on the courses file!\n");
        return false;
    }
    
    // Write the modified data back to the file
    lseek(course_fd, 0, SEEK_SET);
    ssize_t bytesWritten = write(course_fd, c, sizeof(struct course) * num_elements);
    if (bytesWritten != sizeof(struct course) * num_elements) 
    {
        perror("Error writing file!\n");
        return false;
    }
    // Release the lock when you're done.
    readlock.l_type = F_UNLCK;
   	unlockingStatus = fcntl(course_fd, F_SETLK, &readlock);
    if (unlockingStatus == -1) 
    {
        perror("Error while releasing read lock on the courses file!\n");
        return false;
    }
    close(course_fd);    
	memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Course details modified successfully!! Redirecting to the main menu...!\n");
    msg.response=0;
    write(connFD, &msg, sizeof(msg));
    return true;
}
