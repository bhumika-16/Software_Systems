bool get_student_details(int connFD, int studentID);
bool get_faculty_details(int connFD, int facultyID);
bool get_course_details(int connFD);
bool view_all_courses(int connFD);

//Admin viewing student details
bool get_student_details(int connFD, int studentID)
{
    ssize_t readBytes, writeBytes;             
    char buff[1024];
    struct message msg;
    struct student s;
    if (studentID == -1)//should it be Null 
    {
      	memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Enter Student ID:\n" );
        msg.response=1;
        write(connFD, &msg, sizeof(msg));
        memset(buff, 0,sizeof(buff));
        readBytes = read(connFD, buff, sizeof(buff));
		studentID = atoi(buff);
    }

    int stfd = open("./records/student", O_RDONLY);
    if (stfd == -1 || studentID==0)
    {        
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Invalid Student Id!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));       
        return false;
    }
    
    //check offset 
    off_t end=lseek(stfd,0,SEEK_END);
    off_t offset = lseek(stfd, (studentID-1) * sizeof(struct student), SEEK_SET);
    printf("%ld",offset);
    if (errno == EINVAL || end<=offset)
    {      
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Invalid Student Id!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));   
        return false;
    }
    else if (offset == -1)
    {
        perror("Error while seeking to required student record!");
        return false;
    }  
    
    struct flock readlock;
    readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = offset; 
	readlock.l_len = sizeof(struct student); 
	readlock.l_pid = getpid(); 
    int lockingStatus = fcntl(stfd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the Student file!");
        return false;
    }
    memset(buff, 0,sizeof(buff));
    readBytes = read(stfd, &s, sizeof(struct student));
    readlock.l_type = F_UNLCK;
    fcntl(stfd, F_SETLK, &readlock);
    memset(msg.buff, 0,sizeof(msg.buff));
    char *status = (s.s_active_status)? "Active":"Blocked";
    sprintf(msg.buff, "\n----------------- Student Details -------------------- \n\tID: %d\n\tName: %s\n\tGender : %c\n\tAge: %d\n\tEmail : %s\n\t\
Contact No.: %s\n\tDegree Enrolled: %s\n\tLoginID : %s\n\tAccount Status : %s", s.s_id, s.s_name, s.s_gender, s.s_age, s.s_email, s.s_phone_no,\
s.s_degree, s.s_login_id, status);
    strcat(msg.buff, "\n\nRedirecting to main menu....\n");
    msg.response=0;
	write(connFD, &msg, sizeof(msg)); 
    return true;
}




//Admin viewing faculty details
bool get_faculty_details(int connFD, int facultyID)
{
    ssize_t readBytes, writeBytes;             
    char buff[1024];
    struct message msg;
    struct faculty f;
    if (facultyID == -1)//should it be Null 
    {
      	memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Enter Faculty ID:\n" );
        msg.response=1;
        write(connFD, &msg, sizeof(msg));
        memset(buff, 0,sizeof(buff));
        readBytes = read(connFD, buff, sizeof(buff));
		facultyID = atoi(buff);
    }

    int stfd = open("./records/faculty", O_RDONLY);
    if (stfd == -1 || facultyID==0)
    {        
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Invalid Faculty Id!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));       
        return false;
    }
    
    //check offset 
    off_t end=lseek(stfd,0,SEEK_END);
    off_t offset = lseek(stfd, (facultyID-1) * sizeof(struct faculty), SEEK_SET);
    printf("%ld",offset);
    if (errno == EINVAL || end<=offset)
    {      
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Invalid Faculty Id!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));   
        return false;
    }
    else if (offset == -1)
    {
        perror("Error while seeking to required faculty record!");
        return false;
    }  
    
    struct flock readlock;
    readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = offset; 
	readlock.l_len = sizeof(struct faculty); 
	readlock.l_pid = getpid(); 
    int lockingStatus = fcntl(stfd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the Faculty file!");
        return false;
    }
    memset(buff, 0,sizeof(buff));
    readBytes = read(stfd, &f, sizeof(struct faculty));
    readlock.l_type = F_UNLCK;
    fcntl(stfd, F_SETLK, &readlock);
    memset(msg.buff, 0,sizeof(msg.buff));
    sprintf(msg.buff, "\n----------------- Faculty Details -------------------- \n\tID: %d\n\tName: %s\n\tGender : %c\n\tAge: %d\n\tEmail : %s\n\t\
Contact No.: %s\n\tQualifications: %s\n\tYears of Experience: %.2f\n\tLoginID : %s", f.f_id, f.f_name, f.f_gender, f.f_age, \
f.f_email, f.f_phone_no, f.f_qual, f.f_exp, f.f_login_id);
    strcat(msg.buff, "\n\nRedirecting to main menu....\n");
    msg.response=0;
	write(connFD, &msg, sizeof(msg)); 
    return true;
}





//Professor viewing his/her course details
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





bool view_all_courses(int connFD)
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
	
	memset(msg.buff, 0,sizeof(msg.buff));
	strcpy(msg.buff,"\n------------------------------ Details of all Courses offered ---------------------------- \n");
	strcat(msg.buff,"Course Name\t\tCourse Code\t\tCredit\t\tTotal Seats\t\tAvailable seats\n");
	for (size_t i = 0; i < num_elements; i++) 
        sprintf(msg.buff + strlen(msg.buff), "%s\t\t%s\t\t\t%d\t\t%d\t\t\t%d\n",c[i].c_name, c[i].c_code, c[i].c_credit, c[i].total_seats, c[i].avail_seats);
    strcat(msg.buff, "\n\nRedirecting to main menu....\n");
    msg.response=0;
	write(connFD, &msg, sizeof(msg)); 
    return true;
}
