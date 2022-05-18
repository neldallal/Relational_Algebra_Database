/*
 * database.h
 *
 *  Created on: Mar 29, 2022
 *      Author 1: Claudia Cortell
 *      Author 2: Nadine Eldallal
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdbool.h>

typedef struct SNAPTuple* SNAPNextTuple;
typedef struct SNAPTuple* SNAPTuple;
struct SNAPTuple {
	int StudentId;
	char Name[30];
	char Address[50];
	char Phone[9];
	SNAPNextTuple next;
};



typedef struct CSGTuple* CSGNextTuple;
typedef struct CSGTuple* CSGTuple;
struct CSGTuple {
	char Course[8];
	int StudentId;
	char Grade[3];
	CSGNextTuple next;
};


typedef struct CPTuple* CPNextTuple;
typedef struct CPTuple* CPTuple;
struct CPTuple {
	char Course[8];
	char PreReq[8];
	CPNextTuple next;
};


typedef struct CDHTuple* CDHNextTuple;
typedef struct CDHTuple* CDHTuple;
struct CDHTuple {
	char Course[8];
	char Day;
	int Hour;
	CDHNextTuple next;
};

typedef struct CRTuple* CRNextTuple;
typedef struct CRTuple* CRTuple;
struct CRTuple {
	char Course[8];
	char Room[50];
	CRNextTuple next;
};


typedef struct Database* Database;
struct Database {
	SNAPNextTuple* sHash;
	CSGNextTuple* cHash;
	CPNextTuple* pHash;
	CDHNextTuple* dHash;
	CRNextTuple* rHash;
};


extern Database create_database ();

extern Database create_database_from_file();

extern void print_Database(Database db);

extern void free_Database (Database d);



extern SNAPNextTuple* create_SNAP ();

extern bool insert_SNAP(int id, char* n, char* a, char* p, SNAPNextTuple* theHash);

extern void delete_SNAP(int s, char* n, char* a, char* p, SNAPNextTuple* theHash);

extern SNAPTuple lookup_SNAP(int s, char* n, char* a, char* p, SNAPNextTuple* theHash);

extern void print_SNAP(SNAPNextTuple* hash);

extern void print_SNAPTuple(SNAPTuple t);



extern CSGNextTuple* create_CSG ();

extern bool insert_CSG(char* c, int s, char* g, CSGNextTuple* theHash);

extern void  delete_CSG(char* c, int s, char* g, CSGNextTuple* theHash);

extern CSGTuple lookup_CSG(char* c, int s, char* g, CSGNextTuple* theHash);

extern void print_CSG(CSGNextTuple* hash);

extern void print_CSGTuple(CSGTuple t);



extern CPNextTuple* create_CP ();

extern bool insert_CP(char* c, char* p, CPNextTuple* theHash);

extern void  delete_CP(char* c, char* p, CPNextTuple* theHash);

extern CPTuple lookup_CP(char* c, char* p, CPNextTuple* theHash);

extern void print_CP(CPNextTuple* hash);

extern void print_CPTuple(CPTuple t);



extern CDHNextTuple* create_CDH ();

extern bool insert_CDH(char* c, char d, int h, CDHNextTuple* theHash);

extern void  delete_CDH(char* c, char d, int h, CDHNextTuple* theHash);

extern CDHTuple lookup_CDH(char* c, char d, int h, CDHNextTuple* theHash);

extern void print_CDH(CDHNextTuple* hash);

extern void print_CDHTuple(CDHTuple t);



extern CRNextTuple* create_CR ();

extern bool insert_CR(char* c, char* r, CRNextTuple* theHash);

extern void  delete_CR(char* c, char* r, CRNextTuple* theHash);

extern CRTuple lookup_CR(char* c, char* r, CRNextTuple* theHash);

extern void print_CR(CRNextTuple* hash);

extern void print_CRTuple(CRTuple t);



extern void getGradeForNameCourse (char* n, char* c, Database db);

extern void getRoomForNameDayHour (char* n, char d, int h, Database db);

#endif /* DATABASE_H_ */
