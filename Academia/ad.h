int add_course(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1024]; 
    struct message msg;    
    struct course newCourse, prevCourse;
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff, "\n---------Enter the details of your new course--------\n");
	strcat(msg.buff, "Enter course's name: ");
    msg.response=1;
    write(connFD, &msg, sizeof(msg));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(newCourse.c_name, readBuffer);    
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter course's code: ");
    msg.response=1;
    write(connFD, &msg, sizeof(msg));
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
   	strcpy(newCourse.c_code, readBuffer); 

    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter course's credit: ");
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
        return -1;
    }
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter course's total seats: ");
  	msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    int tot_seats;
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
    
    newCourse.c_credit = cred;
    newCourse.total_seats = tot_seats;
    newCourse.avail_seats = tot_seats;
    strcpy(newCourse.cfac_id,login_fac.f_login_id);
    
    int course_fd = open("./records/courses", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
    if (course_fd == -1)
    {
        perror("Error while creating / opening faculty file!");
        return -1;
    }
    writeBytes = write(course_fd, &newCourse, sizeof(newCourse));  
    close(course_fd);
  
    memset(msg.buff, 0,sizeof(msg.buff));    
    strcpy(msg.buff, "Course added successfully...!!\n");     
    msg.response=0;
    write(connFD, &msg, sizeof(msg));
    return 0;
}
