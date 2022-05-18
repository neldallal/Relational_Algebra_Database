//
// Created on 4/3/2022.
// Author 1: Claudia Cortell
// Author 2: Nadine Eldallal
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "relational-algebra.h"
#include "database.h"

CSGNextTuple* select_CSG_StudentId(CSGNextTuple* r, int id) {

    CSGNextTuple* result = (CSGTuple*)malloc(17*sizeof(CSGTuple));

    for (int i=0; i<17; i++) {
        CSGTuple currTuple = r[i];
        if (currTuple != NULL) {
            do {
                if (currTuple->StudentId == id) {
                    insert_CSG(currTuple->Course, id, currTuple->Grade, result);
                }
                currTuple = currTuple->next;
            } while(currTuple !=NULL);
        }
    }
    return result;
}


CSGCourseNextTuple* project_CSG_Course(CSGNextTuple* r) {

    CSGCourseNextTuple* result = (CSGCourseTuple*)malloc(17*sizeof(CSGCourseTuple));

    for (int i=0; i<17; i++) {
        CSGTuple currTuple = r[i];
        if (currTuple != NULL) {
            do {
                insert_CSGCourse(currTuple->Course, result);
                currTuple = currTuple->next;
            } while(currTuple !=NULL);
        }
    }
    return result;

}

extern bool insert_CSGCourse(char* c, CSGCourseNextTuple* theHash) {

    CSGCourseTuple tup = (CSGCourseTuple)malloc(sizeof(struct CSGCourseTuple));
    strcpy(tup->Course, c);
    tup->next = NULL;

    int hashKey = 0;
    for (int j = 0; j < 8; j++){
        if (tup->Course[j]==0)
            break;
        hashKey += tup->Course[j];
    }
    hashKey = hashKey%17;

    //empty bucket, no collision
    if (theHash[hashKey]== NULL){
        theHash[hashKey] = tup;
        return true;

        //if there is already an item in the bucket
    } else{
        CSGCourseTuple currentBucketItem = theHash[hashKey];
        //make sure the tuple isn't already in the bucket, meaning same key
        if (strcmp(currentBucketItem->Course, tup->Course)==0){
            //printf("Tuple already exists\n");
            return false;
        }
        while (currentBucketItem->next != NULL){
            //make sure the tuple isn't already in the bucket, meaning same key
            if (strcmp(currentBucketItem->Course, tup->Course)==0){
                //printf("Tuple already exists\n");
                return false;
            }
            currentBucketItem = currentBucketItem->next;
        }
        currentBucketItem->next = tup;
        return true;
    }
    return false;

}

void print_CSGCourse(CSGCourseNextTuple* hash){
    printf("printing CSGCourse relation:\n");
    for (int i = 0; i < 17; i++){
        printf("Bucket %d:\n", i);
        if (hash[i] != NULL){
            CSGCourseTuple currBucket = hash[i];
            while (currBucket != NULL){
                print_CSGCourseTuple(currBucket);
                currBucket = currBucket->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

void print_CSGCourseTuple(CSGCourseTuple t){
    printf("   [Course: %s]   ", t->Course);
}


CDHRNextTuple* join_CR_CDH(CRNextTuple* r1, CDHNextTuple* r2) {

    CDHRNextTuple* result = (CDHRTuple*)malloc(17*sizeof(CDHRTuple));

    for (int i=0; i<17; i++) {
        CDHTuple currTuple = r2[i];
        if (currTuple != NULL) {
            do {
                char* course = currTuple->Course;
                CRTuple temp = lookup_CR(course, "*", r1);
                if (temp != NULL) {
                    insert_CDHR(course, currTuple->Day, currTuple->Hour, temp->Room, result);
                }
                currTuple = currTuple->next;
            } while(currTuple !=NULL);
        }
    }
    return result;

}

bool insert_CDHR(char*c, char d, int h, char* r, CDHRNextTuple* t) {
    CDHRTuple tup = (CDHRTuple)malloc(sizeof(struct CDHRTuple));
    strcpy(tup->Course, c);
    strcpy(tup->Room, r);
    tup->Day = d;
    tup->Hour = h;
    tup->next = NULL;

    int hashKey = 0;
    for (int i=0; i<8; i++) {
        if (tup->Course[i] == 0){
            break;
        }
        hashKey = hashKey + (int)tup->Course[i];
    }
    hashKey = hashKey + (int)tup->Day;
    hashKey = hashKey%17;

    if (t[hashKey]== NULL){
        t[hashKey] = tup;
        return true;

        //if there is already an item in the bucket
    } else{
        CDHRTuple currentBucketItem = t[hashKey];
        //make sure the tuple isn't already in the bucket, meaning same key
        if (strcmp(currentBucketItem->Course, tup->Course)==0 &&
            currentBucketItem->Day == tup->Day){
            //printf("Tuple already exists\n");
            return false;
        }
        while (currentBucketItem->next != NULL){
            //make sure the tuple isn't already in the bucket, meaning same key
            if (strcmp(currentBucketItem->Course, tup->Course)==0 &&
                currentBucketItem->Day == tup->Day){
                //printf("Tuple already exists\n");
                return false;
            }
            currentBucketItem = currentBucketItem->next;
        }
        currentBucketItem->next = tup;
        return true;
    }
    return false;
}

void print_CDHR(CDHRNextTuple* hash){
    printf("printing CDHR relation:\n");
    for (int i = 0; i < 17; i++){
        printf("Bucket %d:\n", i);
        if (hash[i] != NULL){
            CDHRTuple currBucket = hash[i];
            while (currBucket != NULL){
                print_CDHRTuple(currBucket);
                currBucket = currBucket->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

void print_CDHRTuple(CDHRTuple t){
    printf("   [Course: %s, Day: %c, Hour: %d, Room: %s]   ", t->Course, t->Day, t->Hour, t->Room);
}


CDHRDayHourNextTuple* project_CDHR_DayHour(CDHRNextTuple* r) {

    CDHRDayHourNextTuple* result = (CDHRDayHourTuple*)malloc(17*sizeof(CDHRDayHourTuple));

    for (int i=0; i<17; i++) {
        CDHRTuple currTuple = r[i];
        if (currTuple != NULL) {
            do {
                insert_CDHRDayHour(currTuple->Day, currTuple->Hour, result);
                currTuple = currTuple->next;
            } while(currTuple !=NULL);
        }
    }
    return result;

}

bool insert_CDHRDayHour(char d, int h, CDHRDayHourNextTuple* t) {
    CDHRDayHourTuple tup = (CDHRDayHourTuple)malloc(sizeof(struct CDHRDayHourTuple));
    tup->Day = d;
    tup->Hour = h;

    int hashKey = h;
    hashKey = hashKey + (int)tup->Day;
    hashKey = hashKey%17;

    if (t[hashKey]== NULL){
        t[hashKey] = tup;
        return true;

        //if there is already an item in the bucket
    } else{
        CDHRDayHourTuple currentBucketItem = t[hashKey];
        //make sure the tuple isn't already in the bucket, meaning same key
        if (currentBucketItem->Hour == tup->Hour &&
            currentBucketItem->Day == tup->Day){
            //printf("Tuple already exists\n");
            return false;
        }
        while (currentBucketItem->next != NULL){
            //make sure the tuple isn't already in the bucket, meaning same key
            if (currentBucketItem->Hour == tup->Hour &&
                currentBucketItem->Day == tup->Day){
                //printf("Tuple already exists\n");
                return false;
            }
            currentBucketItem = currentBucketItem->next;
        }
        currentBucketItem->next = tup;
        return true;
    }
    return false;

}
void print_CDHRDayHour(CDHRDayHourNextTuple* hash) {

    printf("printing CDHRDayHour relation:\n");
    for (int i = 0; i < 17; i++){
        printf("Bucket %d:\n", i);
        if (hash[i] != NULL){
            CDHRDayHourTuple currBucket = hash[i];
            while (currBucket != NULL){
                print_CDHRDayHourTuple(currBucket);
                currBucket = currBucket->next;
            }
            printf("\n");
        }
    }
    printf("\n");

}
void print_CDHRDayHourTuple(CDHRDayHourTuple t) {
    printf("   [Day: %c, Hour: %d]   ", t->Day, t->Hour);

}

CDHRNextTuple* select_CDHR_Room(CDHRNextTuple* t, char* r) {

    CDHRNextTuple* result = (CDHRTuple*)malloc(17*sizeof(CDHRTuple));

    for (int i=0; i<17; i++) {
        CDHRTuple currTuple = t[i];
        if (currTuple != NULL) {
            do {
                if (strcmp(currTuple->Room, r)==0) {
                    insert_CDHR(currTuple->Course, currTuple->Day, currTuple->Hour, currTuple->Room, result);
                }
                currTuple = currTuple->next;
            } while(currTuple !=NULL);
        }
    }
    return result;
}
