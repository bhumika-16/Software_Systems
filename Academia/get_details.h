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
Contact No.: %s\n\tDegree Enrolled: %s\n\tLoginID : %s\n\tAccount Status : %s\n\tRegistered Courses : %d", s.s_id, s.s_name, s.s_gender, s.s_age, s.s_email, s.s_phone_no,\
s.s_degree, s.s_login_id, status, s.num_reg_courses);
    strcat(msg.buff, "\n\nRedirecting to main menu....\n");
    msg.response=0;
	write(connFD, &msg, sizeof(msg)); 
    return true;
}



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
Contact No.: %s\n\tQualifications: %s\n\tYears of Experience: %.2f\n\tLoginID : %s\n\tAssigned Courses : %d", f.f_id, f.f_name, f.f_gender, f.f_age, \
f.f_email, f.f_phone_no, f.f_qual, f.f_exp, f.f_login_id, f.num_assigned_courses);
    strcat(msg.buff, "\n\nRedirecting to main menu....\n");
    msg.response=0;
	write(connFD, &msg, sizeof(msg)); 
    return true;
}
