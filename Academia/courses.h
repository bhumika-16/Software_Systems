bool update_seats(int connFD);
bool enroll_course(int connFD);
bool view_enroll_course(int connFD);
bool drop_course(int connFD);
bool update_seats(int connFD);

//Student enroll in a course available in course catalog
bool enroll_course(int connFD)
{
    ssize_t readBytes, writeBytes;  
    char readBuffer[20];   
    char enroll_code[20];         
    char buff[1024];
    struct message msg;
    struct course c[50];
    struct enroll e;
    struct enroll en[100];
    size_t struct_size = sizeof(struct course);
    int num_elements = 0;
    
    int course_fd = open("./records/courses", O_RDONLY);
    if (course_fd == -1)
    {        
        perror("Error while seeking to required courses record!\n");
        return false;
    }
    
    //Input the course code and checking if course code is valid
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff, "Enter the Course Code you want to enroll: ");
    msg.response=1;
    write(connFD, &msg, sizeof(msg));
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(enroll_code, readBuffer);   
    
    struct flock readlock;
    readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = 0; 
	readlock.l_len = 0; 
	readlock.l_pid = getpid(); 
    int lockingStatus = fcntl(course_fd, F_SETLKW, &readlock);
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
	for (size_t i = 0; i < num_elements; i++) 
        if(strcmp(c[i].c_code, enroll_code) == 0)
        	found = true;

    if(found==false)
	{
		memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Given course code not found..!!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));   
        return false;
	}
	
	memset(msg.buff, 0,sizeof(msg.buff)); 	
    strcpy(msg.buff, "Enrolling into the given course....\n");
    msg.response=0;
	write(connFD, &msg, sizeof(msg)); 	
	
	//Enrolling the student for that particular course by appending it to enroll file
	int enroll_fd = open("./records/enroll", O_CREAT | O_APPEND | O_RDWR, S_IRWXU);
    if (enroll_fd == -1)
    {        
        perror("Error while seeking to required enrolled courses record!\n");
        return false;
    }
    strcpy(e.stud_login_id,login_stud.s_login_id);
    strcpy(e.course_code,enroll_code);
    e.active_status = true;
    
    bool enroll_done = false;    
    readlock.l_type = F_WRLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = 0; 
	readlock.l_len = 0; 
	readlock.l_pid = getpid(); 
    lockingStatus = fcntl(enroll_fd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the enrolled courses file!\n");
        return false;
    }
    //Checking if previously same enrolled or not
    while (read(enroll_fd, &en[num_elements], sizeof(struct enroll)) != 0) 
    {
    	//Same student enrolled in same course
    	if(strcmp(en[num_elements].course_code,e.course_code)==0 && strcmp(en[num_elements].stud_login_id,e.stud_login_id)==0 && en[num_elements].active_status==true)
    		enroll_done = true;
        num_elements++;
    }
    if(enroll_done==false)
    writeBytes = write(enroll_fd, &e, sizeof(struct enroll));  

    // Release the lock when you're done.
    readlock.l_type = F_UNLCK;
    unlockingStatus = fcntl(enroll_fd, F_SETLK, &readlock);
    if (unlockingStatus == -1) 
    {
        perror("Error while releasing read lock on the courses file!\n");
        return false;
    }
        
    if(enroll_done==true)
    {
    	memset(msg.buff, 0,sizeof(msg.buff));   
		strcpy(msg.buff, "You have already enrolled for this course...!!\n");     
		msg.response=0;
		write(connFD, &msg, sizeof(msg));
		return false;
	}
    else
    {
    	bool up = update_seats(connFD);
    	memset(msg.buff, 0,sizeof(msg.buff));   
		strcpy(msg.buff, "Successfully enrolled for this course...!!\n");     
		msg.response=0;
		write(connFD, &msg, sizeof(msg));
		return true;
	}
	memset(msg.buff, 0,sizeof(msg.buff));   
	strcpy(msg.buff, "Program Failed...!!\n");     
	msg.response=0;
	write(connFD, &msg, sizeof(msg));
    return false;
}

//View all the enrolled courses of the logged in student
bool view_enroll_course(int connFD)
{
	ssize_t readBytes, writeBytes;  
    char readBuffer[20];   
    char enroll_code[20];         
    char buff[1024];
    struct message msg;
    struct course c[50];
    struct enroll e;
    struct enroll en[100];
    int num_elements = 0;
    
	int enroll_fd = open("./records/enroll", O_RDONLY);
    if (enroll_fd == -1)
    {        
        perror("Error while seeking to required enrolled courses record!\n");
        return false;
    }
    
    bool enroll_done = false;    
    struct flock readlock;
    readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = 0; 
	readlock.l_len = 0; 
	readlock.l_pid = getpid(); 
    int lockingStatus = fcntl(enroll_fd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the enrolled courses file!\n");
        return false;
    }
    
    memset(msg.buff, 0,sizeof(msg.buff));
	strcpy(msg.buff,"\n----------------- Your Enrolled Courses Details -------------------- \n");
    while (read(enroll_fd, &en[num_elements], sizeof(struct enroll)) != 0) 
    {
    	//Student enrolled in some course
    	if(strcmp(en[num_elements].stud_login_id,login_stud.s_login_id)==0 && en[num_elements].active_status==true)
    	{
    		enroll_done = true;
    		sprintf(msg.buff + strlen(msg.buff), "\tCourse Code: %s\n",en[num_elements].course_code);
    	}
        num_elements++;
    }

    // Release the lock when you're done.
    readlock.l_type = F_UNLCK;
    int unlockingStatus = fcntl(enroll_fd, F_SETLK, &readlock);
    if (unlockingStatus == -1) 
    {
        perror("Error while releasing read lock on the courses file!\n");
        return false;
    }
        
    if(enroll_done==false)
    {
    	memset(msg.buff, 0,sizeof(msg.buff));   
		strcpy(msg.buff, "You have not enrolled for any course...!!\n");     
		msg.response=0;
		write(connFD, &msg, sizeof(msg));
		return false;
	}
	
    strcat(msg.buff, "\n\nRedirecting to main menu....\n");
    msg.response=0;
	write(connFD, &msg, sizeof(msg)); 
    return true;
}





//Student dropping the course from courses he/she is enrolled in
bool drop_course(int connFD)
{
	ssize_t readBytes, writeBytes;  
    char readBuffer[20];   
    char enroll_code[20];         
    char buff[1024];
    struct message msg;
    struct course c[50];
    struct enroll e;
    struct enroll en[100];
    int num_elements = 0;
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff, "Enter your enrolled course code you wish to drop: ");
    msg.response=1;
    write(connFD, &msg, sizeof(msg));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(enroll_code, readBuffer); 
    
    int enroll_fd = open("./records/enroll", O_RDONLY);
    if (enroll_fd == -1)
    {        
        perror("Error while seeking to required enrolled courses record!\n");
        return false;
    }
    
    bool enroll_done = false;    
    struct flock readlock;
    readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = 0; 
	readlock.l_len = 0; 
	readlock.l_pid = getpid(); 
    int lockingStatus = fcntl(enroll_fd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the enrolled courses file!\n");
        return false;
    }
    
    while (read(enroll_fd, &en[num_elements], sizeof(struct enroll)) != 0) 
    {
    	//Student enrolled in some course
    	if(strcmp(en[num_elements].stud_login_id,login_stud.s_login_id)==0 && strcmp(en[num_elements].course_code,enroll_code)==0)
    	{
    		enroll_done = true;
    		en[num_elements].active_status = false;
    	}
        num_elements++;
    } 
    
    // Release the lock when you're done.
    readlock.l_type = F_UNLCK;
    int unlockingStatus = fcntl(enroll_fd, F_SETLK, &readlock);
    if (unlockingStatus == -1) 
    {
        perror("Error while releasing read lock on the courses file!\n");
        return false;
    }
    
    
    enroll_fd = open("./records/enroll", O_WRONLY);
    if (enroll_fd == -1)
    {        
        perror("Error while seeking to required enrolled courses record!\n");
        return false;
    }
   
    if(enroll_done==true)
    {
		struct flock readlock;
		readlock.l_type = F_WRLCK; 
		readlock.l_whence = SEEK_SET; 
		readlock.l_start = 0; 
		readlock.l_len = 0; 
		readlock.l_pid = getpid(); 
		int lockingStatus = fcntl(enroll_fd, F_SETLKW, &readlock);
		if (lockingStatus == -1)
		{
		    perror("Error while obtaining write lock on the enrolled courses file!\n");
		    return false;
		}
		writeBytes = write(enroll_fd, &en, sizeof(struct enroll)*num_elements);    
		// Release the lock when you're done.
		readlock.l_type = F_UNLCK;
		int unlockingStatus = fcntl(enroll_fd, F_SETLK, &readlock);
		if (unlockingStatus == -1) 
		{
		    perror("Error while releasing write lock on the courses file!\n");
		    return false;
		}
    }         
    else
    {
    	memset(msg.buff, 0,sizeof(msg.buff));   
		strcpy(msg.buff, "Course not found in your enrolled list...!!\n");     
		msg.response=0;
		write(connFD, &msg, sizeof(msg));
		return false;
	}
	
	update_seats(connFD);
	memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff, "Course is dropped!! Redirecting to main menu....\n");
    msg.response=0;
	write(connFD, &msg, sizeof(msg)); 
    return true;
}



//Updating the available seats for each course by checking the enrollments data
bool update_seats(int connFD)
{
	ssize_t readBytes, writeBytes;  
    char readBuffer[20];   
    char enroll_code[20];         
    char buff[1024];
    struct message msg;
    struct course c[50];
    struct enroll e;
    struct enroll en[100];
    size_t struct_size = sizeof(struct course);
    int cnum_elements = 0, enum_elements = 0;
       
    int course_fd = open("./records/courses", O_RDONLY);
    if (course_fd == -1)
    {        
        perror("Error while seeking to required courses record!\n");
        return false;
    }
    
    struct flock readlock;
    readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = 0; 
	readlock.l_len = 0; 
	readlock.l_pid = getpid(); 
    int lockingStatus = fcntl(course_fd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the courses file!\n");
        return false;
    }
    
    while (read(course_fd, &c[cnum_elements], sizeof(struct course)) != 0)
        cnum_elements++;

    // Release the lock when you're done.
    readlock.l_type = F_UNLCK;
    int unlockingStatus = fcntl(course_fd, F_SETLK, &readlock);
    if (unlockingStatus == -1) 
    {
        perror("Error while releasing read lock on the courses file!\n");
        return false;
    }
		
	if(cnum_elements == 0)
	{
		memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"No courses found..!!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));   
        return false;
	}
	
	
	
	
	int enroll_fd = open("./records/enroll", O_RDONLY);
    if (enroll_fd == -1)
    {        
        perror("Error while seeking to required enrolled courses record!\n");
        return false;
    }
     
    readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = 0; 
	readlock.l_len = 0; 
	readlock.l_pid = getpid(); 
    lockingStatus = fcntl(enroll_fd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the enrolled courses file!\n");
        return false;
    }
    
    while (read(enroll_fd, &en[enum_elements], sizeof(struct enroll)) != 0) 
        enum_elements++;
    
    // Release the lock when you're done.
    readlock.l_type = F_UNLCK;
    unlockingStatus = fcntl(enroll_fd, F_SETLK, &readlock);
    if (unlockingStatus == -1) 
    {
        perror("Error while releasing read lock on the enrolled courses file!\n");
        return false;
    }
	
	
	bool found = false, take=true;	
	struct enroll e_new[100]; int k=0;
	for (size_t i = 0; i < cnum_elements; i++) 
	{
		c[i].avail_seats = c[i].total_seats;
		for (size_t j = 0; j < enum_elements; j++) 
		{
			take=true;
        	if(strcmp(c[i].c_code, en[j].course_code) == 0 && en[j].active_status==true)
        	{
        		c[i].avail_seats = c[i].avail_seats - 1;
        		if(c[i].avail_seats<0)
        			take=false;
        	}
        	if(take==true)
        		e_new[k++]=en[j];
        }
    }
	
	course_fd = open("./records/courses", O_WRONLY);
    if (course_fd == -1)
    {        
        perror("Error while seeking to required courses record!\n");
        return false;
    }
    
    readlock.l_type = F_WRLCK; 
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
    for (size_t i = 0; i < cnum_elements; i++) 
        write(course_fd, &c[i], sizeof(struct course));

    // Release the lock when you're done.
    readlock.l_type = F_UNLCK;
    unlockingStatus = fcntl(course_fd, F_SETLK, &readlock);
    if (unlockingStatus == -1) 
    {
        perror("Error while releasing read lock on the courses file!\n");
        return false;
    }
    
    
    if(take==false)
    {
    	enroll_fd = open("./records/enroll", O_WRONLY);
		if (enroll_fd == -1)
		{        
		    perror("Error while seeking to required enrolled courses record!\n");
		    return false;
		}
		
		readlock.l_type = F_WRLCK; 
		readlock.l_whence = SEEK_SET; 
		readlock.l_start = 0; 
		readlock.l_len = 0; 
		readlock.l_pid = getpid(); 
	   	lockingStatus = fcntl(enroll_fd, F_SETLKW, &readlock);
		if (lockingStatus == -1)
		{
		    perror("Error while obtaining read lock on the enrolled courses file!\n");
		    return false;
		} 
		for (size_t i = 0; i < k; i++) 
		    write(course_fd, &e_new[i], sizeof(struct enroll));

		// Release the lock when you're done.
		readlock.l_type = F_UNLCK;
		unlockingStatus = fcntl(enroll_fd, F_SETLK, &readlock);
		if (unlockingStatus == -1) 
		{
		    perror("Error while releasing read lock on the courses file!\n");
		    return false;
		}
		memset(msg.buff, 0,sizeof(msg.buff));
		strcpy(msg.buff, "No seats available! Last Enrolled Students removed from list if any....\n");
		msg.response=0;
		write(connFD, &msg, sizeof(msg)); 
		return false;
    }
    	
	memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff, "Seat of the courses updated successfully....\n");
    msg.response=0;
	write(connFD, &msg, sizeof(msg)); 
    return true;
}
	
