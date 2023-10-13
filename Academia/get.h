bool get_course_details(int connFD)
{
    ssize_t readBytes, writeBytes;             
    char buff[1024];
    struct message msg;
    struct course c[50];
    size_t struct_size = sizeof(struct course);
    int num_elements = 0;
    
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
	strcpy(msg.buff,"\n----------------- Your Courses Details -------------------- \n");
	for (size_t i = 0; i < num_elements; i++) 
	{
        if(strcmp(c[i].cfac_id, login_fac.f_login_id) == 0)
        {
        	found = true;
        	sprintf(msg.buff + strlen(msg.buff), "\tCourse Name: %s\n\tCourse Code: %s\n\tCourse Credit : %d\n\tTotal Seats: %d\n\tAvailable seats : %d\n\n",\
c[i].c_name, c[i].c_code, c[i].c_credit, c[i].total_seats, c[i].avail_seats);
        }
    }
    if(found==false)
	{
		memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"No courses found that you are teaching..!!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));   
        return false;
	}
	    
    strcat(msg.buff, "\n\nRedirecting to main menu....\n");
    msg.response=0;
	write(connFD, &msg, sizeof(msg)); 
    return true;
}
