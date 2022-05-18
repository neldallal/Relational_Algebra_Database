/*
 * main4.c
 *
 *  Created on: Mar 29, 2022
 *      Author 1: Claudia Cortell
 *      Author 2: Nadine Eldallal
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "database.h"
#include "relational-algebra.h"


int main(int argc, char *argv[]) {
	printf("Welcome to Nadine and Claudia's Project 4!\n");

	printf("Press RETURN to continue.");
	getchar();

	printf("\nCreating the data base...\n");
	Database db1 = create_database();
	print_Database(db1);


	printf("Press RETURN to continue.");
	getchar();
	printf("\nPart 1.3: Testing the insert/lookup/delete methods.\n");
	printf("Part 1.3: a) looking up the tuple in CSG with course \"CSC172\" and ID \"98789\":\n");
	CSGTuple t1 = lookup_CSG("CSC172", 98789, "*", db1->cHash);
	if (t1 == NULL){
		printf("No tuple found\n");
	} else {
		printf("Found tuple:");
		print_CSGTuple(t1);
		printf("\n");
	}

	printf("\nPress RETURN to continue.");
	getchar();

	printf("\nPart 1.3: b) looking up the tuple in CP with course \"CSC173\" and prerequisite \"CSC172\"\n");
	CPTuple t2 = lookup_CP("CSC173", "CSC172", db1->pHash);
	if (t2 == NULL){
		printf("No tuple found\n");
	} else {
		printf("Found tuple:");
		print_CPTuple(t2);
		printf("\n");
	}
	printf("\nPress RETURN to continue.");
	getchar();

	printf("\nPart 1.3: c) deleting tuples with course \"DSCC201\" from CDH \n");
	delete_CDH("DSCC201",'*', -1, db1->dHash);
	printf("Updated CDH:\n");
	print_CDH(db1->dHash);
	printf("Press RETURN to continue.");
	getchar();


	printf("\nPart 1.3: d) inserting tuple into CP with course \"CSC280\" and prerequisite \"CSC173\"\n");
	insert_CP("CSC280", "CSC173", db1->pHash);
	printf("Updated CP:\n");
	print_CP(db1->pHash);
	printf("Press RETURN to continue.");
	getchar();

	printf("\nPart 1.3: e) inserting tuple into CP with course \"DSCC202\" and prerequisite \"DSCC201\"\n");
	insert_CP("DSCC202", "DSCC201", db1->pHash);
	printf("Updated CP:\n");
	print_CP(db1->pHash);
	printf("Press RETURN to continue.");
	getchar();


	Database db2 = create_database();
	printf("\n\nPart 2: Answering queries");
	printf("\nPart 2.1: answering query 'What grade did (name) get in (course)?\n");
	char* name = (char*) malloc(127*sizeof(char));
	char* course = (char*) malloc (8 * sizeof(char));
	do {
		printf("Enter an input for name (\"q\" to quit):");
		scanf("%[^\n]s",name);

		if (name[0]!='q' || name[1]!=0){
			printf("Enter an input for course:");
			scanf("%s", course);
			getGradeForNameCourse (name, course, db2);
		}
		getchar();
	} while(name[0] != 'q'||name[1]!=0);
	free(name);
	free(course);

	printf("\nPart 2.2: answering query 'Where is (name) at (hour) on (day)?\n");
	char* name2 = (char*) malloc(127*sizeof(char));
	char day = 0;
	int hour = 0;

	do {
		printf("Enter an input for name (\"q\" to quit):");
		scanf("%[^\n]s",name2);

		if (name2[0]!='q' || name2[1]!=0){
			getchar();
			printf("Enter an input for day (a single capital letter):");
			scanf("%c", &day);
			printf("Enter an input for hour (in military time):");
			scanf("%d", &hour);
			getRoomForNameDayHour (name2, day, hour, db2);
		}
		getchar();
	} while(name2[0] != 'q'||name2[1]!=0);
	free(name2);

	printf("\n\nPart 3: Relational Algebra\n");
	printf("Part 3.1: selecting student id = 67890 from CSG\n");
	CSGNextTuple* selectedIDfromCSG = select_CSG_StudentId(db2->cHash, 67890);
	print_CSG(selectedIDfromCSG);
	printf("Press RETURN to continue.");
	getchar();

	printf("\nPart 3.2: projecting course from the selection of student id = 67890 from CSG\n");
	CSGCourseNextTuple* projectedCourse = project_CSG_Course(selectedIDfromCSG);
	print_CSGCourse(projectedCourse);
	printf("Press RETURN to continue.");
	getchar();

	printf("\nPart 3.3: joining CR and CDH\n");
	CDHRNextTuple* CRjoinCDH = join_CR_CDH(db2->rHash, db2->dHash);
	print_CDHR(CRjoinCDH);
	printf("Press RETURN to continue.");
	getchar();

	printf("\nPart 3.4: projecting day and hour from the selection of room = Wegmans 1400 from joining CR and CDH\n");
	CDHRNextTuple* selectedRoom = select_CDHR_Room(CRjoinCDH,"Wegmans 1400");
	//print_CDHR(selectedRoom);
	CDHRDayHourNextTuple* finalProjection = project_CDHR_DayHour(selectedRoom);
	print_CDHRDayHour(finalProjection);

	free_Database(db1);
	free_Database(db2);

	printf("Done! :)\n");
}
