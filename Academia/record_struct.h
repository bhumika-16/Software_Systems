#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define ADMIN_LOGIN_ID "admin"
#define ADMIN_PASSWORD "admin@123" 

struct message {
	char buff[1024];
	bool response;
};

// Structure for an admin
struct admin {
    char name[50];
    char login_id[20];
    char password[20];
    char email[20];
   	char phone_no[15];
};

// Structure for a faculty member
struct faculty {
    char f_name[50];
    char f_login_id[20];
    char f_password[20];
    int f_age;
    char f_gender;
    char f_email[20];
   	char f_phone_no[15];
   	char f_qual[50];
   	float f_exp;
    bool f_login_status;
    int f_id;
};

// Structure for a course
struct course {
    char c_name[100];
    char c_code[20];
    int c_credit;    
    int total_seats;
    int avail_seats;
    char cfac_id[20];
};

// Structure for a student
struct student {
    char s_name[50];
    char s_login_id[20];
    char s_password[20];
    int s_age;
    char s_gender;
    char s_email[20];
   	char s_phone_no[15];
   	char s_degree[10];
    bool s_login_status;
    bool s_active_status;
    int s_id;
};

struct enroll
{
	char stud_login_id[20];
	char course_code[20];
	bool active_status;
};

struct faculty login_fac;
struct student login_stud;

