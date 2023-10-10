#include <stdbool.h> // Include this header for boolean support

// Structure for a course
struct course {
    char course_name[100];
    char course_code[20];
    int course_credit;
};

// Structure for an admin
struct admin {
    char name[50];
    char login_id[20];
    char password[20];
    // You can add more admin-specific fields here if needed
};

// Structure for a student
struct student {
    char s_name[50];
    char s_login_id[20];
    char s_password[20];
    int s_age;
    char s_gender;
    bool s_login_status;
    // Additional fields for student, e.g., student ID
    char student_id[20];
    // Information about the courses a student is registered for
    struct course registered_courses[10]; // Assuming a student can register for up to 10 courses
    int num_registered_courses; // Number of courses registered
};

// Structure for a faculty member
struct faculty {
    char f_name[50];
    char f_login_id[20];
    char f_password[20];
    int f_age;
    char f_gender;
    bool f_login_status;
    // Additional fields for faculty, e.g., faculty ID
    char faculty_id[20];
    // Information about the courses a faculty member is responsible for
    struct course assigned_courses[10]; // Assuming a faculty member can be assigned up to 10 courses
    int num_assigned_courses; // Number of courses assigned
};
