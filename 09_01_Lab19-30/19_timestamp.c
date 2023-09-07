//Hands on 1: Assignment No.19 (OPTIONAL) - Program to find out time taken to execute getpid system call using time stamp counter.
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
//header specific to x86 architectures, provides intrinsics for using assembly instructions like rdtsc (Read Time Stamp Counter).
#include <x86intrin.h>

//Function to read the Time Stamp Counter (TSC)
//Inline function - the code will be inserted directly into the calling code to minimize overhead.
//Returns a 64-bit unsigned integer (uint64_t) representing the value of the TSC.
static inline uint64_t rdtsc() 
{
	//Store the low and high parts of the TSC value.
    unsigned int lo, hi; 
    //inline assembly block which contains the assembly instruction rdtsc.
    //This assembly instruction reads the TSC and stores the low part in lo and the high part in hi.
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
        
    //This combines the low and high parts to form a 64-bit TSC value.
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    uint64_t start, end;
    pid_t pid;
    start = rdtsc(); // Get the initial timestamp
    pid = getpid(); // Execute getpid system call
    end = rdtsc(); // Get the final timestamp

    printf("Process ID: %d\n", pid);
    printf("Time taken (TSC cycles): %lu\n", end - start);
    return 0;
}
