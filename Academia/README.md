# CS-513 System Software – Mini Project

## Design and Development of Course Registration Portal (Academia)

### How to execute?

- Compile server.c and client.c by the given commands respectively:

```
gcc server.c -o server -lpthread
```

```
gcc client.c -o client
```

- Run/Execute the server as shown below:

```
./server 
```

and client as shown below:

```
./client
```

### System Programming Concepts used
Process Management, File Management, File Locking, Inter Process Communication Mechanisms. 

### GitHub Repository Address 
[Academia Mini-Project](https://github.com/bhumika-16/Software_Systems/tree/main/Academia)

## Modules

#### Admin Module
Once the Admin connects to the server, He/She should get a login and password prompt. 
After successful login, He/She should get menu for example:
Do you want to:
- Add Student
- Add Faculty
- Activate/Deactivate Student
- Update Student/Faculty details
- View Student/Faculty details
- Exit

#### Faculty Module
Once the Faculty connects to the server, He/She should get a login and password prompt.
After successful login, He/She should get menu for example:
Do you want to:
- Add new Course
- Update Course details
- Remove offered Course
- View enrollments in Courses
- Password Change
- Exit
(Assumption: Course will have a limited number of seats.)

#### Student Module
Once the Student connects to the server, He/She should get a login and password prompt.
After successful login, He/She should get menu for example:
Do you want to:
- Enroll to new Courses
- Unenroll from already enrolled Courses
- View enrolled Courses
- Password Change
- Exit


## Features
Features of Course Registration Portal are listed as follows:
- Handling multiple connections. i.e., Serving multiple clients simultaneously.
- Socket programming is used to implement client-server model.
- TCP connection for effective and reliable communication.
- Storage/ Database: Unix File System. i.e., data is stored typically in files only.
- Concurrency: File Locking (both mandatory and advisory locking) while operating files for consistency.
Semaphores protection as mutex/ binary locks may be used for Critical Section of the code in future scope.
- Only system calls are used directly, avoiding use of library functions.

## Outputs

- On Running Client and Administrator Login
# ![1](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot1.png)

- Admin adding students details (Login-id & password auto-generated)
# ![2](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot2.png)

- Admin displaying students details (Password not shown, everything else is displayed)
# ![3](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot3.png)

- Admin trying to display invalid students id (Invalid Input Handled)
# ![4](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot4.png)

- Admin adding two faculties and their details (Login-id & password auto-generated)
# ![5](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot5.png)

- Admin viewing faculty details by their id 
# ![6](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot6.png)

- Admin updating the students details
# ![7](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot7.png)

- Admin blocking the specific student and checking its blocked
# ![8](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot8.png)

- Admin activating the activated student and blocked student
# ![9](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot9.png)

- Professor logs in with given details and changes the password
# ![10](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot10.png)

- Faculty adding 2 courses and displaying their details
# ![11](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot11.png)

- Faculty updating his courses and displaying their details
# ![12](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot12.png)

- Student logs in with given details and view all the courses
- He/She then enrolls for a course in the given list
- Available seats for the course decreases as the student enrolls in that course
# ![13](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot13.png)

- Student enrolls for two course of different professors from the given list
- Available seats for the course decreases as the student enrolls in that course
# ![14](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot14.png)

- Student views the courses he/she enrolls in and also change the password
# ![15](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot15.png)

- Student dropping the course and displaying the updated list of enrolled courses.
# ![16](https://raw.githubusercontent.com/bhumika-16/Software_Systems/main/Academia/Output/Screenshot16.png)


<br> 
<i>Report by, </i> <br/>
Bhumika Jindal <br/>
MT2023005 <br/>
MTech CSE <br/>
International Institute of Information Technology Bangalore <br/>
