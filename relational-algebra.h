//
// Created on 4/3/2022.
// Author 1: Claudia Cortell
// Author 2: Nadine Eldallal
//

#ifndef PROJECT4_RELATIONAL_ALGEBRA_H
#define PROJECT4_RELATIONAL_ALGEBRA_H

#include "database.h"

typedef struct CSGCourseTuple* CSGCourseNextTuple;
typedef struct CSGCourseTuple* CSGCourseTuple;
struct CSGCourseTuple {
    char Course[8];
    CSGCourseNextTuple next;
};

typedef struct CDHRTuple* CDHRNextTuple;
typedef struct CDHRTuple* CDHRTuple;
struct CDHRTuple {
    char Course[8];
    char Day;
    int Hour;
    char Room[50];
    CDHRNextTuple next;
};

typedef struct CDHRDayHourTuple* CDHRDayHourNextTuple;
typedef struct CDHRDayHourTuple* CDHRDayHourTuple;
struct CDHRDayHourTuple {
    char Day;
    int Hour;
    CDHRDayHourNextTuple next;
};


extern CSGNextTuple* select_CSG_StudentId(CSGNextTuple* r, int id);
extern CSGCourseNextTuple* project_CSG_Course(CSGNextTuple* r);
extern CDHRNextTuple* join_CR_CDH(CRNextTuple* r1, CDHNextTuple* r2);
extern CDHRDayHourNextTuple* project_CDHR_DayHour(CDHRNextTuple* r);
extern bool insert_CSGCourse(char* c, CSGCourseNextTuple* theHash);
extern void print_CSGCourse(CSGCourseNextTuple* hash);
extern void print_CSGCourseTuple(CSGCourseTuple t);
extern bool insert_CDHR(char*c, char d, int h, char* r, CDHRNextTuple* t);
extern void print_CDHR(CDHRNextTuple* hash);
extern void print_CDHRTuple(CDHRTuple t);
extern bool insert_CDHRDayHour(char d, int h, CDHRDayHourNextTuple* t);
extern void print_CDHRDayHour(CDHRDayHourNextTuple* hash);
extern void print_CDHRDayHourTuple(CDHRDayHourTuple t);
extern CDHRNextTuple* select_CDHR_Room(CDHRNextTuple* t, char* r);


#endif //PROJECT4_RELATIONAL_ALGEBRA_H
