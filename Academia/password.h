bool change_faculty_password(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1024];
    struct message msg;
    char newPassword[20];

     /*
    struct sembuf semOp; 
    semOp.sem_num = 0;
    semOp.sem_flg = SEM_UNDO;  
    semOp.sem_op = -1;
    semop(semid, &semOp, 1);*/
    
   	memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff, "Enter current password: ");
    msg.response=1;
    write(connFD, &msg, sizeof(msg));   
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));    

    if (strcmp(readBuffer, login_fac.f_password) == 0)
    {       
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Enter new password: " );
        msg.response=1;
        write(connFD, &msg, sizeof(msg));        
        memset(readBuffer, 0,sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));     
        strcpy(newPassword,readBuffer);
		strcpy(login_fac.f_password, newPassword);

        int facfd = open("./records/faculty", O_WRONLY);
        if (facfd == -1)
        {
            perror("Error opening faculty file!");               
			//semOp.sem_op = 1;
            //semop(semid, &semOp, 1);  
            return false;
        }
        //offset check
        off_t end=lseek(facfd,0,SEEK_END);
        off_t offset = lseek(facfd, (login_fac.f_id-1) * sizeof(struct faculty), SEEK_SET);
        if (offset == -1 || end<=offset)
        {
        	perror("Error seeking to the faculty record!");
            //semOp.sem_op = 1;
            //semop(semid, &semOp, 1);  
            return false;
        }

		struct flock writelock; 
		writelock.l_type = F_WRLCK; 
		writelock.l_whence = SEEK_SET; 
		writelock.l_start = offset; 
		writelock.l_len = sizeof(struct faculty); 
		writelock.l_pid = getpid(); 
	
        int lockingStatus = fcntl(facfd, F_SETLKW, &writelock);
        if (lockingStatus == -1)
        {
        	perror("Error obtaining write lock on faculty record!");
            //semOp.sem_op = 1;
            //semop(semid, &semOp, 1);  
            return false;
         }
		writeBytes = write(facfd, &login_fac, sizeof(struct faculty));
        writelock.l_type = F_UNLCK;
        fcntl(facfd, F_SETLK, &writelock);
		close(facfd);

        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Password changed successfully...!!\n" );
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        //semOp.sem_op = 1;
        //semop(semid, &semOp, 1);
        return true;       
    }
    else
    {
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Incorrect password...!!\n" );
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
       
    } 
    //semOp.sem_op = 1;
    //semop(semid, &semOp, 1);
    return false;
}









bool change_student_password(int connFD)
{
    ssize_t readBytes, writeBytes;
    char readBuffer[1024];
    struct message msg;
    char newPassword[20];

     /*
    struct sembuf semOp; 
    semOp.sem_num = 0;
    semOp.sem_flg = SEM_UNDO;  
    semOp.sem_op = -1;
    semop(semid, &semOp, 1);*/
    
   	memset(msg.buff, 0,sizeof(msg.buff));
    strcpy(msg.buff, "Enter current password: ");
    msg.response=1;
    write(connFD, &msg, sizeof(msg));   
    memset(readBuffer, 0,sizeof(readBuffer));
    readBytes = read(connFD, readBuffer, sizeof(readBuffer));    

    if (strcmp(readBuffer, login_stud.s_password) == 0)
    {       
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Enter new password: " );
        msg.response=1;
        write(connFD, &msg, sizeof(msg));        
        memset(readBuffer, 0,sizeof(readBuffer));
        readBytes = read(connFD, readBuffer, sizeof(readBuffer));     
        strcpy(newPassword,readBuffer);
		strcpy(login_stud.s_password, newPassword);

        int studfd = open("./records/student", O_WRONLY);
        if (studfd == -1)
        {
            perror("Error opening student file!");               
			//semOp.sem_op = 1;
            //semop(semid, &semOp, 1);  
            return false;
        }
        //offset check
        off_t end=lseek(studfd,0,SEEK_END);
        off_t offset = lseek(studfd, (login_stud.s_id-1) * sizeof(struct student), SEEK_SET);
        if (offset == -1 || end<=offset)
        {
        	perror("Error seeking to the student record!");
            //semOp.sem_op = 1;
            //semop(semid, &semOp, 1);  
            return false;
        }

		struct flock writelock; 
		writelock.l_type = F_WRLCK; 
		writelock.l_whence = SEEK_SET; 
		writelock.l_start = offset; 
		writelock.l_len = sizeof(struct student); 
		writelock.l_pid = getpid(); 
	
        int lockingStatus = fcntl(studfd, F_SETLKW, &writelock);
        if (lockingStatus == -1)
        {
        	perror("Error obtaining write lock on student record!");
            //semOp.sem_op = 1;
            //semop(semid, &semOp, 1);  
            return false;
         }
		writeBytes = write(studfd, &login_stud, sizeof(struct student));
        writelock.l_type = F_UNLCK;
        fcntl(studfd, F_SETLK, &writelock);
		close(studfd);

        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Password changed successfully...!!\n" );
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        //semOp.sem_op = 1;
        //semop(semid, &semOp, 1);
        return true;       
    }
    else
    {
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff,"Incorrect password...!!\n" );
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
       
    } 
    //semOp.sem_op = 1;
    //semop(semid, &semOp, 1);
    return false;
}
