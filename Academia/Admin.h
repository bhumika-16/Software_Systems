#include "record_struct.h"
#include "add.h"
#include "get_details.h"
#include "edit_details.h"
#include "login.h"
#include "password.h"
#include "ad.h"
#include "get.h"

bool admin_operation_handler(int connFD)
{
    if (login_handler(true, false, connFD, NULL, NULL))
    {
        ssize_t writeBytes, readBytes;  
        char buff[1024];        
        struct message msg;        
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Admin login successful...!!\n");      
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        
        while (1)
        {
            memset(msg.buff,0,sizeof(msg.buff));
            strcpy(msg.buff,"\n********************************* Welcome to Administrator Menu *********************************\n1. Add Student\n2. Get Student Details\n\
3. Add Faculty\n4. View Faculty Details\n5. Activate Student\n6. Block Student\n7. Modify Student Details\n8. Modify Faculty Details\n9. Logout & Exit\n\
Enter your choice: \n");          
            msg.response=1;
            write(connFD, &msg, sizeof(msg));         
            
            memset(msg.buff, 0,sizeof(msg.buff));
            read(connFD, buff, sizeof(buff));
            int choice = atoi(buff);
            switch (choice)
            {
            case 1:
                add_student(connFD);
                break;
            case 2:
                get_student_details(connFD,-1);
                break;       
            case 3:
                add_faculty(connFD);
                break;
            case 4:
                get_faculty_details(connFD,-1);
                break;
            case 5:
                activate_student(connFD,1);
                break;
            case 6:
                activate_student(connFD,0);
                break;
            case 7:
                modify_student_details(connFD);
                break;                
            case 8:
                modify_faculty_details(connFD);
                break;
            default:               
                memset(msg.buff,0,sizeof(msg.buff));
                strcpy(msg.buff,"Signing out... Reopen application...\n" );
                msg.response=0;
                write(connFD, &msg, sizeof(msg));
                return false;
            }
        }
    }
    else
    {    
        //ADMIN LOGIN FAILED       
        return false;
    }
    return true;
}





bool faculty_operation_handler(int connFD)
{
    if (login_handler(false, true, connFD, &login_fac, NULL))
    {
        ssize_t writeBytes, readBytes;  
        char buff[1024];        
        struct message msg;        
        memset(msg.buff, 0,sizeof(msg.buff));          
        strcpy(msg.buff, "Faculty login successful... Hello ");  
        strcat(msg.buff, login_fac.f_name);
        strcat(msg.buff, " !!\n");    
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        
        while (1)
        {
            memset(msg.buff,0,sizeof(msg.buff));
            strcpy(msg.buff,"\n********************************* Welcome to Faculty Menu *********************************\n1. View Offering Courses\n2. Add new Course\n\
3. Remove Course from Catalog\n4. Update Course Details\n5. Change Password\n6. Logout & Exit\nEnter your choice: \n");          
            msg.response=1;
            write(connFD, &msg, sizeof(msg));         
            
            memset(msg.buff, 0,sizeof(msg.buff));
            read(connFD, buff, sizeof(buff));
            int choice = atoi(buff);
            switch (choice)
            {
            case 1:
                get_course_details(connFD);
                break;
            case 2:
                add_course(connFD);
                break;
            /*       
            case 3:
                add_faculty(connFD);
                break;
            case 4:
                get_faculty_details(connFD,-1);
                break;*/
            case 5:
                change_faculty_password(connFD);
                break;
            default:               
                memset(msg.buff,0,sizeof(msg.buff));
                strcpy(msg.buff,"Signing out... Reopen application...\n" );
                msg.response=0;
                write(connFD, &msg, sizeof(msg));
                return false;
            }
        }
    }
    else
    {    
        //Faculty Login Failed      
        return false;
    }
    return true;
}






bool student_operation_handler(int connFD)
{
    if (login_handler(false, false, connFD, NULL, &login_stud))
    {
        ssize_t writeBytes, readBytes;  
        char buff[1024];        
        struct message msg;        
        memset(msg.buff, 0,sizeof(msg.buff));
        strcpy(msg.buff, "Student login successful... Hello ");  
        strcat(msg.buff, login_stud.s_name);
        strcat(msg.buff, " !!\n");  
        msg.response=0;
        write(connFD, &msg, sizeof(msg));
        
        while (1)
        {
            memset(msg.buff,0,sizeof(msg.buff));
            strcpy(msg.buff,"\n********************************* Welcome to Student Menu *********************************\n1. View all Courses\n\
2. Enroll (pick) New Course\n3. Drop Course\n4. View Enrolled Course Details\n5. Change Password\n6. Logout & Exit\nEnter your choice: \n");          
            msg.response=1;
            write(connFD, &msg, sizeof(msg));         
            
            memset(msg.buff, 0,sizeof(msg.buff));
            read(connFD, buff, sizeof(buff));
            int choice = atoi(buff);
            switch (choice)
            {
            /*
            case 1:
                add_student(connFD);
                break;
            case 2:
                get_student_details(connFD,-1);
                break;       
            case 3:
                add_faculty(connFD);
                break;
            case 4:
                get_faculty_details(connFD,-1);
                break;*/
            case 5:
                change_student_password(connFD);
                break;
            default:               
                memset(msg.buff,0,sizeof(msg.buff));
                strcpy(msg.buff,"Signing out... Reopen application...\n" );
                msg.response=0;
                write(connFD, &msg, sizeof(msg));
                return false;
            }
        }
    }
    else
    {    
        //Faculty Login Failed      
        return false;
    }
    return true;
}
