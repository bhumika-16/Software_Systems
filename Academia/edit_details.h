bool modify_student_details(int connFD);
bool modify_faculty_details(int connFD);
bool activate_student(int connFD,int status);

//Admin modifies student details
bool modify_student_details(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1024];
    struct message msg;
    struct student s;
    int sID, lockingStatus;
    off_t offset;

    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter Student Id:\n" );
    msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    sID = atoi(readBuffer);

    int studfd = open("./records/student", O_RDONLY);
    if (studfd == -1 || sID==0)
    {
        // Student File doesn't exist       
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"No record exists...\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        return false;
    }
    off_t end=lseek(studfd,0,SEEK_END);
    offset = lseek(studfd, (sID-1) * sizeof(struct student), SEEK_SET);
    if (errno == EINVAL ||  end<=offset)
    {
        // Student record doesn't exist       
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Given student id doesn't exists!\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        return false;
    }   
    else if (offset == -1)
    {
        perror("Error while seeking to required student record!\n");
        return false;
    }
	struct flock readlock;
	readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = offset; 
	readlock.l_len = sizeof(struct student); 
	readlock.l_pid = getpid();   
    lockingStatus = fcntl(studfd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Couldn't obtain lock on student record!\n");
        return false;
    }
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(studfd, &s, sizeof(struct student));   
    // Unlock the record
    readlock.l_type = F_UNLCK;
    fcntl(studfd, F_SETLK, &readlock);
    close(studfd);
    
    memset(msg.buff, 0,sizeof(msg.buff));    
    strcpy(msg.buff,"Select the information you wish to modify:\n1. Name \n2. Age\n3. Gender\n4. Email\n5. Contact No.\nEnter your choice: " );
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
        strcpy(msg.buff,"Enter student's new Name: ");
        msg.response=1;
        write(connFD, &msg, sizeof(msg));
        readBytes = read(connFD, &readBuffer, sizeof(readBuffer));      
        strcpy(s.s_name, readBuffer);
        break;        
    case 2:
        memset(msg.buff, 0,sizeof(msg.buff));      
        strcpy(msg.buff,"Enter student's new Age: ");        
        msg.response=1;
		write(connFD, &msg, sizeof(msg));    
		memset(readBuffer, 0,sizeof(readBuffer));
		readBytes = read(connFD, readBuffer, sizeof(readBuffer));
		int sAge;
		if (is_numeric(readBuffer))
			sAge = atoi(readBuffer); // Now, sAge contains the integer value
		else
			sAge=-1;     
		if (sAge <= 18 || sAge>150)
		{
		    // Either client has sent age as 0 (which is invalid) or has entered a non-numeric string 
		    memset(msg.buff, 0,sizeof(msg.buff));
		    strcpy(msg.buff, "Invalid Age!! Redirecting to the main menu...!\n");      
		    msg.response=0;
		    write(connFD, &msg, sizeof(msg));       
		    return false;
		}
       	s.s_age = sAge;
        break;    
    case 3:
        memset(msg.buff, 0,sizeof(msg.buff));
    	strcpy(msg.buff,"Student's new gender:\nEnter M for male, F for female and O for others: ");
		msg.response=1;
		write(connFD, &msg, sizeof(msg));
		memset(readBuffer, 0,sizeof(readBuffer));
		readBytes = read(connFD, readBuffer, sizeof(readBuffer));
   
		if (readBuffer[0] == 'M' || readBuffer[0] == 'F' || readBuffer[0] == 'O')
		    s.s_gender = readBuffer[0];
		else{      
		    memset(msg.buff, 0,sizeof(msg.buff));
		    strcpy(msg.buff, "Invalid Gender!! Redirecting to the main menu...!\n");
		    msg.response=0;
		    write(connFD, &msg, sizeof(msg));      
		    return false;
		}
		break;
	case 4:
		memset(msg.buff, 0,sizeof(msg.buff));
		strcpy(msg.buff,"Enter student's new email: ");
	  	msg.response=1;
		write(connFD, &msg, sizeof(msg));    
		memset(readBuffer, 0,sizeof(readBuffer));
		readBytes = read(connFD, readBuffer, sizeof(readBuffer));
		if (is_valid_email(readBuffer))
			strcpy(s.s_email, readBuffer);  
		else{      
		    memset(msg.buff, 0,sizeof(msg.buff));
		    strcpy(msg.buff, "Invalid Email!! Redirecting to the main menu...!\n");
		    msg.response=0;
		    write(connFD, &msg, sizeof(msg));      
		    return false;
		}
    	break;
    case 5:
    	memset(msg.buff, 0,sizeof(msg.buff));
		strcpy(msg.buff,"Enter student's new Contact No.: ");
	  	msg.response=1;
		write(connFD, &msg, sizeof(msg));    
		memset(readBuffer, 0,sizeof(readBuffer));
		readBytes = read(connFD, readBuffer, sizeof(readBuffer));
		if (is_valid_phone_number(readBuffer))
			strcpy(s.s_phone_no, readBuffer);  
		else{      
		    memset(msg.buff, 0,sizeof(msg.buff));
		    strcpy(msg.buff, "Invalid Contact No!! Redirecting to the main menu...!\n");
		    msg.response=0;
		    write(connFD, &msg, sizeof(msg));      
		    return -1;
		}
		break;
    default:        
        memset(msg.buff, 0,sizeof(msg.buff));
		strcpy(msg.buff, "Invalid Choice!! Redirecting to the main menu...!\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        return false;
    }

    studfd = open("./records/student", O_WRONLY);
    if (studfd == -1)
    {
        perror("Error while opening student file!\n");
        return false;
    }
    offset = lseek(studfd, (sID-1) * sizeof(struct student), SEEK_SET);
    if (offset == -1)
    {
        perror("Error while seeking to required student record!");
        return false;
    }

    readlock.l_type = F_WRLCK;
    readlock.l_start = offset;
    lockingStatus = fcntl(studfd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining write lock on student record!");
        return false;
    }
    writeBytes = write(studfd, &s, sizeof(struct student));
    readlock.l_type = F_UNLCK;
    fcntl(studfd, F_SETLK, &readlock);
    close(studfd);
    
	memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Student details modified successfully!! Redirecting to the main menu...!\n");
    msg.response=0;
    write(connFD, &msg, sizeof(msg));
    return true;
}




//Admin modifying faculty details
bool modify_faculty_details(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1024];
    struct message msg;
    struct faculty f;
    int fID, lockingStatus;
    off_t offset;

    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter Faculty Id:\n" );
    msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    fID = atoi(readBuffer);

    int facfd = open("./records/faculty", O_RDONLY);
    if (facfd == -1 || fID==0)
    {
        // Faculty File doesn't exist       
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"No record exists...\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        return false;
    }
    off_t end=lseek(facfd,0,SEEK_END);
    offset = lseek(facfd, (fID-1) * sizeof(struct faculty), SEEK_SET);
    if (errno == EINVAL ||  end<=offset)
    {
        // Faculty record doesn't exist       
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Given faculty id doesn't exists!\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        return false;
    }   
    else if (offset == -1)
    {
        perror("Error while seeking to required faculty record!\n");
        return false;
    }
	struct flock readlock;
	readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = offset; 
	readlock.l_len = sizeof(struct faculty); 
	readlock.l_pid = getpid();   
    lockingStatus = fcntl(facfd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Couldn't obtain lock on faculty record!\n");
        return false;
    }
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(facfd, &f, sizeof(struct faculty));   
    // Unlock the record
    readlock.l_type = F_UNLCK;
    fcntl(facfd, F_SETLK, &readlock);
    close(facfd);
    
    memset(msg.buff, 0,sizeof(msg.buff));    
    strcpy(msg.buff,"Select the information you wish to modify:\n1. Name \n2. Age\n3. Gender\n4. Email\n5. Contact No.\n6. Qualification\n7. Experience\nEnter your choice: " );
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
        strcpy(msg.buff,"Enter faculty's new Name: ");
        msg.response=1;
        write(connFD, &msg, sizeof(msg));
        readBytes = read(connFD, &readBuffer, sizeof(readBuffer));      
        strcpy(f.f_name, readBuffer);
        break;        
    case 2:
        memset(msg.buff, 0,sizeof(msg.buff));      
        strcpy(msg.buff,"Enter faculty's new Age: ");        
        msg.response=1;
		write(connFD, &msg, sizeof(msg));    
		memset(readBuffer, 0,sizeof(readBuffer));
		readBytes = read(connFD, readBuffer, sizeof(readBuffer));
		int fAge;
		if (is_numeric(readBuffer))
			fAge = atoi(readBuffer); // Now, fAge contains the integer value
		else
			fAge=-1;     
		if (fAge <= 25 || fAge>150)
		{
		    // Either client has sent age as 0 (which is invalid) or has entered a non-numeric string 
		    memset(msg.buff, 0,sizeof(msg.buff));
		    strcpy(msg.buff, "Invalid Age!! Redirecting to the main menu...!\n");      
		    msg.response=0;
		    write(connFD, &msg, sizeof(msg));       
		    return false;
		}
		f.f_age = fAge;
        break;    
    case 3:
        memset(msg.buff, 0,sizeof(msg.buff));
    	strcpy(msg.buff,"Faculty's new gender:\nEnter M for male, F for female and O for others: ");
		msg.response=1;
		write(connFD, &msg, sizeof(msg));
		memset(readBuffer, 0,sizeof(readBuffer));
		readBytes = read(connFD, readBuffer, sizeof(readBuffer));
   
		if (readBuffer[0] == 'M' || readBuffer[0] == 'F' || readBuffer[0] == 'O')
		    f.f_gender = readBuffer[0];
		else{      
		    memset(msg.buff, 0,sizeof(msg.buff));
		    strcpy(msg.buff, "Invalid Gender!! Redirecting to the main menu...!\n");
		    msg.response=0;
		    write(connFD, &msg, sizeof(msg));      
		    return false;
		}
		break;
	case 4:
		memset(msg.buff, 0,sizeof(msg.buff));
		strcpy(msg.buff,"Enter faculty's new email: ");
	  	msg.response=1;
		write(connFD, &msg, sizeof(msg));    
		memset(readBuffer, 0,sizeof(readBuffer));
		readBytes = read(connFD, readBuffer, sizeof(readBuffer));
		if (is_valid_email(readBuffer))
			strcpy(f.f_email, readBuffer);  
		else{      
		    memset(msg.buff, 0,sizeof(msg.buff));
		    strcpy(msg.buff, "Invalid Email!! Redirecting to the main menu...!\n");
		    msg.response=0;
		    write(connFD, &msg, sizeof(msg));      
		    return false;
		}
    	break;
    case 5:
    	memset(msg.buff, 0,sizeof(msg.buff));
		strcpy(msg.buff,"Enter faculty's new Contact No.: ");
	  	msg.response=1;
		write(connFD, &msg, sizeof(msg));    
		memset(readBuffer, 0,sizeof(readBuffer));
		readBytes = read(connFD, readBuffer, sizeof(readBuffer));
		if (is_valid_phone_number(readBuffer))
			strcpy(f.f_phone_no, readBuffer);  
		else{      
		    memset(msg.buff, 0,sizeof(msg.buff));
		    strcpy(msg.buff, "Invalid Contact No!! Redirecting to the main menu...!\n");
		    msg.response=0;
		    write(connFD, &msg, sizeof(msg));      
		    return -1;
		}
		break;
	case 6:
		memset(msg.buff, 0,sizeof(msg.buff));
		strcpy(msg.buff,"Enter faculty's new Qualifications: ");
	  	msg.response=1;
		write(connFD, &msg, sizeof(msg));    
		memset(readBuffer, 0,sizeof(readBuffer));
		readBytes = read(connFD, readBuffer, sizeof(readBuffer));
		strcpy(f.f_qual, readBuffer);  
		break;
	case 7:
		memset(msg.buff, 0,sizeof(msg.buff));
		strcpy(msg.buff,"Enter updated Years of experience: ");
	  	msg.response=1;
		write(connFD, &msg, sizeof(msg));    
		memset(readBuffer, 0,sizeof(readBuffer));
		readBytes = read(connFD, readBuffer, sizeof(readBuffer));
		
		char *endptr; // A pointer to the character that stopped the conversion
		float fExp = strtof(readBuffer, &endptr);
		if (*endptr != '\0') 
		{
		    // Either client has sent age as 0 (which is invalid) or has entered a non-numeric string 
		    memset(msg.buff, 0,sizeof(msg.buff));
		    strcpy(msg.buff, "Invalid Experience!! Redirecting to the main menu...!\n");      
		    msg.response=0;
		    write(connFD, &msg, sizeof(msg));       
		    return -1;
		}
		f.f_exp = fExp;
		break;
    default:        
        memset(msg.buff, 0,sizeof(msg.buff));
		strcpy(msg.buff, "Invalid Choice!! Redirecting to the main menu...!\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        return false;
    }

    facfd = open("./records/faculty", O_WRONLY);
    if (facfd == -1)
    {
        perror("Error while opening faculty file!\n");
        return false;
    }
    offset = lseek(facfd, (fID-1) * sizeof(struct faculty), SEEK_SET);
    if (offset == -1)
    {
        perror("Error while seeking to required faculty record!");
        return false;
    }

    readlock.l_type = F_WRLCK;
    readlock.l_start = offset;
    lockingStatus = fcntl(facfd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining write lock on faculty record!");
        return false;
    }
    writeBytes = write(facfd, &f, sizeof(struct faculty));
    readlock.l_type = F_UNLCK;
    fcntl(facfd, F_SETLK, &readlock);
    close(facfd);
    
	memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Faculty details modified successfully!! Redirecting to the main menu...!\n");
    msg.response=0;
    write(connFD, &msg, sizeof(msg));
    return true;
}

//Activate or block a student
bool activate_student(int connFD,int status)
{
	ssize_t readBytes, writeBytes;
    char readBuffer[1024];
    struct message msg;
    struct student s;
    int sID, lockingStatus;
    off_t offset;

    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter Student Id:\n" );
    msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    sID = atoi(readBuffer);

	bool correct = false;
    int studfd = open("./records/student", O_RDWR);
    if (studfd == -1 || sID==0)
    {
        // Student File doesn't exist       
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"No record exists...\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        return false;
    }
    off_t end=lseek(studfd,0,SEEK_END);
    offset = lseek(studfd, (sID-1) * sizeof(struct student), SEEK_SET);
    if (errno == EINVAL ||  end<=offset)
    {
        // Student record doesn't exist       
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Given student id doesn't exists!\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        return false;
    }   
    else if (offset == -1)
    {
        perror("Error while seeking to required student record!\n");
        return false;
    }
	struct flock readlock;
	readlock.l_type = F_RDLCK; 
	readlock.l_whence = SEEK_SET; 
	readlock.l_start = offset; 
	readlock.l_len = sizeof(struct student); 
	readlock.l_pid = getpid();   
    lockingStatus = fcntl(studfd, F_SETLKW, &readlock);
    if (lockingStatus == -1)
    {
        perror("Couldn't obtain lock on student record!\n");
        return false;
    }
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(studfd, &s, sizeof(struct student));  
    if(s.s_active_status == status)
    	correct = true;
    // Unlock the record
    readlock.l_type = F_UNLCK;
    fcntl(studfd, F_SETLK, &readlock);
    close(studfd);
    
    if(correct==false)
    {
    	s.s_active_status = status;
    	studfd = open("./records/student", O_WRONLY);
		if (studfd == -1)
		{
		    perror("Error while opening student file!\n");
		    return false;
		}
		offset = lseek(studfd, (sID-1) * sizeof(struct student), SEEK_SET);
		if (offset == -1)
		{
		    perror("Error while seeking to required student record!");
		    return false;
		}

		readlock.l_type = F_WRLCK;
		readlock.l_start = offset;
		lockingStatus = fcntl(studfd, F_SETLKW, &readlock);
		if (lockingStatus == -1)
		{
		    perror("Error while obtaining write lock on student record!");
		    return false;
		}
		writeBytes = write(studfd, &s, sizeof(struct student));
		readlock.l_type = F_UNLCK;
		fcntl(studfd, F_SETLK, &readlock);
		close(studfd);
		
		memset(msg.buff, 0,sizeof(msg.buff));
		if(status==1)
			strcpy(msg.buff,"Student Account Activated!! Redirecting to the main menu...!\n");
		else
			strcpy(msg.buff,"Student Account Blocked!! Redirecting to the main menu...!\n");
		msg.response=0;
		write(connFD, &msg, sizeof(msg));
		return true;
    }    
    else
    {
		memset(msg.buff, 0,sizeof(msg.buff));
		if(status==1)
			strcpy(msg.buff,"Student Account is already activated!! Redirecting to the main menu...!\n");
		else
			strcpy(msg.buff,"Student Account is already blocked!! Redirecting to the main menu...!\n");
		msg.response=0;
		write(connFD, &msg, sizeof(msg));
	}
	return true;
}
