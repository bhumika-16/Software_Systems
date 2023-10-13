int is_numeric(const char *str) 
{
    // Function to check if a string contains only numeric digits
    while (*str) {
        if (!isdigit(*str)) {
            return 0; // Non-numeric character found
        }
        str++;
    }
    return 1; // All characters are numeric
}

bool is_valid_email(const char *email) {
    int atCount = 0;
    int dotCount = 0;
    bool atFound = false;

    // Iterate through each character in the email
    for (int i = 0; i < strlen(email); i++) {
        if (email[i] == '@') {
            atCount++;
            atFound = true;
        } else if (email[i] == '.') {
            dotCount++;
        }
    }

    // Check if there is exactly one '@' and at least one '.'
    if (atCount == 1 && dotCount >= 1 && atFound) {
        return true; // Valid email
    } else {
        return false; // Invalid email
    }
}


bool is_valid_phone_number(const char *phoneNumber) {
    // Check if the phone number contains only digits
    for (int i = 0; i < strlen(phoneNumber); i++) {
        if (!isdigit(phoneNumber[i])) {
            return false;
        }
    }

    // Check if the phone number has the correct length for your region
    // You can adjust the length requirement based on your needs
    if (strlen(phoneNumber) != 10) {
        return false; // For example, a 10-digit number
    }
    return true; // If it passes all checks
}



int add_student(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1024]; 
    struct message msg;
    struct student newStudent, prevStudent;
    int studfd = open("./records/student", O_RDONLY);
    if (studfd == -1 && errno == ENOENT)
        newStudent.s_id = 1;
    else if (studfd == -1)
    {
        perror("Error while opening student file");
        return -1;
    }
    else
    {
        int offset = lseek(studfd, -sizeof(struct student), SEEK_END);
        if (offset == -1)
        {
            perror("Error seeking to last student record!");
            return -1;
        }
		struct flock readlock; 	
		readlock.l_type = F_RDLCK; 
		readlock.l_whence = SEEK_SET; 
		readlock.l_start = offset; 
		readlock.l_len = sizeof(struct student); 
		readlock.l_pid = getpid(); 
		
		fcntl(studfd, F_SETLKW, &readlock);       
		readBytes = read(studfd, &prevStudent, sizeof(struct student));
		readlock.l_type = F_UNLCK;
		fcntl(studfd, F_SETLK, &readlock);
		close(studfd);
		newStudent.s_id = prevStudent.s_id + 1;
    }

    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff, "\n---------Enter the details of the new student--------\n");
	strcat(msg.buff, "Enter student's name: ");
    msg.response=1;
    write(connFD, &msg, sizeof(msg));
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(newStudent.s_name, readBuffer);    
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Student's gender:\nEnter M for male, F for female and O for others: ");
    msg.response=1;
    write(connFD, &msg, sizeof(msg));
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
   
    if (readBuffer[0] == 'M' || readBuffer[0] == 'F' || readBuffer[0] == 'O')
        newStudent.s_gender = readBuffer[0];
    else{      
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Invalid Gender!! Redirecting to the main menu...!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));      
        return -1;
    }

    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter student's age: ");
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
        return -1;
    }
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter student's email: ");
  	msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (is_valid_email(readBuffer))
    	strcpy(newStudent.s_email, readBuffer);  
    else{      
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Invalid Email!! Redirecting to the main menu...!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));      
        return -1;
    }
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter student's Contact No.: ");
  	msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (is_valid_phone_number(readBuffer))
    	strcpy(newStudent.s_phone_no, readBuffer);  
    else{      
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Invalid Contact No!! Redirecting to the main menu...!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));      
        return -1;
    }
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Degree Applied (IMT,MT,MS,PHD): ");
  	msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (strcmp(readBuffer, "IMT") == 0 || strcmp(readBuffer, "MT") == 0 || strcmp(readBuffer, "MS") == 0 || strcmp(readBuffer, "PHD") == 0) 
    	strcpy(newStudent.s_degree, readBuffer);  
    else{      
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Invalid Degree Entered!! Redirecting to the main menu...!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));      
        return -1;
    }
    
    newStudent.s_age = sAge;
    newStudent.s_login_status = 0;
	newStudent.s_active_status = 1;	
    strcpy(newStudent.s_login_id, newStudent.s_degree);
    strcat(newStudent.s_login_id, "2023_");
    memset(msg.buff, 0,sizeof(msg.buff));
    sprintf(msg.buff, "%03d", newStudent.s_id);
    strcat(newStudent.s_login_id, msg.buff);    
    strcpy(newStudent.s_password, "pass_");
    strcat(newStudent.s_password, newStudent.s_login_id);
    newStudent.num_reg_courses = 0;
    
    studfd = open("./records/student", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
    if (studfd == -1)
    {
        perror("Error while creating / opening student file!");
        return -1;
    }
    writeBytes = write(studfd, &newStudent, sizeof(newStudent));  
    close(studfd);
  
    memset(msg.buff, 0,sizeof(msg.buff));    
    char temp_buffer[1024];  // Adjust the buffer size as needed
	strcpy(temp_buffer, "---------------------------------------------------------\nStudent Login ID: ");
	strcat(temp_buffer, newStudent.s_login_id);
	strcat(temp_buffer, "\nAuto-generated Password: ");
	strcat(temp_buffer, newStudent.s_password);
	strcat(temp_buffer, "\nKindly change your password at first login..!!\n");
	strcpy(msg.buff, temp_buffer);
    msg.response=0;
    write(connFD, &msg, sizeof(msg));
    return newStudent.s_id;
}


int add_faculty(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1024]; 
    struct message msg;
    struct faculty newFaculty, prevFaculty;
    int facfd = open("./records/faculty", O_RDONLY);
    if (facfd == -1 && errno == ENOENT)
        newFaculty.f_id = 1;
    else if (facfd == -1)
    {
        perror("Error while opening faculty file");
        return -1;
    }
    else
    {
        int offset = lseek(facfd, -sizeof(struct faculty), SEEK_END);
        if (offset == -1)
        {
            perror("Error seeking to last faculty record!");
            return -1;
        }
		struct flock readlock; 	
		readlock.l_type = F_RDLCK; 
		readlock.l_whence = SEEK_SET; 
		readlock.l_start = offset; 
		readlock.l_len = sizeof(struct faculty); 
		readlock.l_pid = getpid(); 
		
		fcntl(facfd, F_SETLKW, &readlock);       
		readBytes = read(facfd, &prevFaculty, sizeof(struct faculty));
		readlock.l_type = F_UNLCK;
		fcntl(facfd, F_SETLK, &readlock);
		close(facfd);
		newFaculty.f_id = prevFaculty.f_id + 1;
    }

    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff, "\n---------Enter the details of the new faculty--------\n");
	strcat(msg.buff, "Enter faculty's name: ");
    msg.response=1;
    write(connFD, &msg, sizeof(msg));
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(newFaculty.f_name, readBuffer);    
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Faculty's gender:\nEnter M for male, F for female and O for others: ");
    msg.response=1;
    write(connFD, &msg, sizeof(msg));
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
   
    if (readBuffer[0] == 'M' || readBuffer[0] == 'F' || readBuffer[0] == 'O')
        newFaculty.f_gender = readBuffer[0];
    else{      
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Invalid Gender!! Redirecting to the main menu...!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));      
        return -1;
    }

    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter faculty's age: ");
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
        return -1;
    }
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter faculty's email: ");
  	msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (is_valid_email(readBuffer))
    	strcpy(newFaculty.f_email, readBuffer);  
    else{      
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Invalid Email!! Redirecting to the main menu...!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));      
        return -1;
    }
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter faculty's Contact No.: ");
  	msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    if (is_valid_phone_number(readBuffer))
    	strcpy(newFaculty.f_phone_no, readBuffer);  
    else{      
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Invalid Contact No!! Redirecting to the main menu...!\n");
        msg.response=0;
        write(connFD, &msg, sizeof(msg));      
        return -1;
    }
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter faculty's Qualifications: ");
  	msg.response=1;
    write(connFD, &msg, sizeof(msg));    
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));
    strcpy(newFaculty.f_qual, readBuffer);  
    
    memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff,"Enter Years of experience: ");
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
    
    newFaculty.f_age = fAge;
    newFaculty.f_exp = fExp;
    newFaculty.f_login_status = 0;
	
    strcpy(newFaculty.f_login_id, "FAC");
    strcat(newFaculty.f_login_id, "2023_");
    memset(msg.buff, 0,sizeof(msg.buff));
    sprintf(msg.buff, "%03d", newFaculty.f_id);
    
    strcat(newFaculty.f_login_id, msg.buff);    
    strcpy(newFaculty.f_password, "pass_");
    strcat(newFaculty.f_password, newFaculty.f_login_id);
    newFaculty.num_assigned_courses = 0;
    
    facfd = open("./records/faculty", O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
    if (facfd == -1)
    {
        perror("Error while creating / opening faculty file!");
        return -1;
    }
    writeBytes = write(facfd, &newFaculty, sizeof(newFaculty));  
    close(facfd);
  
    memset(msg.buff, 0,sizeof(msg.buff));    
    char temp_buffer[1024];  // Adjust the buffer size as needed
	strcpy(temp_buffer, "---------------------------------------------------------\nFaculty Login ID: ");
	strcat(temp_buffer, newFaculty.f_login_id);
	strcat(temp_buffer, "\nAuto-generated Password: ");
	strcat(temp_buffer, newFaculty.f_password);
	strcat(temp_buffer, "\nKindly change your password at first login..!!\n");
	strcpy(msg.buff, temp_buffer);
    msg.response=0;
    write(connFD, &msg, sizeof(msg));
    return newFaculty.f_id;
}
