#include "record_struct.h"
#include "add.h"
#include "get_details.h"
#include "edit_details.h"

bool admin_operation_handler(int connFD)
{

    //if (login_handler(true, connFD, NULL))
    //{
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
            strcpy(msg.buff,"\n------------------------------ Welcome to Administrator Menu ----------------------------\n\
1. Add Student\n2. Get Student Details\n3. Add Faculty\n4. View Faculty Details\n5. Activate Student\n6. Block Student\n\
7. Modify Student Details\n8. Modify Faculty Details\n9. Logout and Exit\nEnter your choice: \n");          
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
            /*
            case 5:
                activate_student(connFD);
                break;
            case 6:
                block_student(connFD);
                break;*/
            case 7:
                modify_student_details(connFD);
                break;                
            case 8:
                modify_faculty_details(connFD);
                break;
            default:               
                memset(msg.buff,0,sizeof(msg.buff));
                strcpy(msg.buff,"Signing out... Reopen application...\n\n" );
                msg.response=0;
                write(connFD, &msg, sizeof(msg));
                return false;
            }
        }
    //}
    //else
    //{    
        // ADMIN LOGIN FAILED       
        //return false;
    //}
    return true;
}
