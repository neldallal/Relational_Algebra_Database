CSC 173

Project 4

Claudia Cortell
ccortell@u.rochester.edu

Nadine Eldallal
neldalla@u.rochester.edu

Build instructions:
1. cd into the folder containing the project files
2. run:
gcc -std=c99 -Wall -Werror -o main4 main4.c database.c relational-algebra.c


Run instructions:
1. run:
On terminal MacOS: ./main4
On command prompt Windows: main4


Explanation/description of each part of the project:
1.1 The database is a struct, which holds 5 hashtables that represent each of the 5 relations.
	Each hashtable is a struct that contains 17 buckets, the buckets will contain the type of
	tuples specified to each relation. The given relations' information is hardcoded in the
	create_SNAP, create_CSG, create_CP, create_CDH, and create_CR methods, using each relation's
	respective insert methods. The database will be printed by printing each of the 5 relations' 
	hashtables. It will print each of the 17 buckets of each hashtable, printing consecutive 
	linked tuples from left to right and printing nothing if there is no tuple in a bucket.
	
1.2	The lookup, delete, and insert methods for each of the 5 hashtables are specific to the
	relation, meaning there are 15 methods in total. They are named, for example, insert_SNAP,
	delete_SNAP, and lookup_SNAP. If the user wishes to leave an attribute blank when calling
	delete or lookup, they should type "*" for strings, '*' for chars, and -1 for ints.
	The key for SNAP is the StudentId, so that attribute cannot be left blank.
	The key for CSG is the Course-StudentId pair, so neither of those atrributes can be left blank.
	The key for CP is the Course-Prerequiste pair, so neither of those attributes can be left blank.
	The key for CDH is the Course-Day pair, but the project description asks us to delete only given
	the Course attribute, so delete_CDH will work (without using the hashing function) when Day is '*'. 
	However, lookup_CDH follows the	definition of the key, so neither Course of Day can be left blank.
	The key for CR is the Course, so that attribute cannot be left blank.
	
2.1 The method getGradeForNameCourse answers the query for part 2.1, while users are prompted for the
	name and course in the REPL in the main.
	
2.2 The method getRoomForNameDayHour answers the query for part 2.2, while users are prompted for the
	name, day, and hour in the REPL in the main.
	
3.1 The method select_CSG_StudentId returns a new relation with the same schema as CSG, but with only
	the tuples that match the user-specified student id.
	
3.2 The method project_CSG_Course returns a new relation with the schema {Course}, projecting only the Course
	attribute from the relation with schema {Course, StudentId, Grade} taken in as an argument.

3.3 The method join_CR_CDH returns a new relation with the schema {Course, Day, Hour, Room}, joining the
	CDH and CR relations taken in as the arguments.
	
3.4 The method project_CDHR_DayHour returns a relation with the schema {Day, Hour}, since it projects the
	Day and Hour attributes from the relation with {Course, Day, Hour, Room} taken in as an argument. This
	relation taken in as an argument to project_CDHR_DayHour has already undergone a selection on room, using
	the method select_CDHR_Room. This select_CDHR_Room returns a relation with the same schema as its argument,
	which is the join of CR and CDH, so {Course, Day, Hour, Room}, but with only the tuples that match the 
	specified room.
	

	