/*
 * database.c
 *
 *  Created on: Mar 29, 2022
 *      Author 1: Claudia Cortell
 *      Author 2: Nadine Eldallal
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"


Database create_database (){

	Database database = (Database)malloc(sizeof(struct Database));

	SNAPNextTuple* s = create_SNAP();
    database->sHash = s;

	CSGNextTuple* c = create_CSG();
    database->cHash = c;

	CPNextTuple* p = create_CP();
    database->pHash = p;

	CDHNextTuple* d = create_CDH();
    database->dHash = d;

	CRNextTuple* r = create_CR();
    database->rHash = r;

	return database;

}

Database create_database_from_file() {

    Database database = (Database)malloc(sizeof(struct Database));

    SNAPNextTuple* s = read_SNAP();
    database->sHash = s;

    CSGNextTuple* c = read_CSG();
    database->cHash = c;

    CPNextTuple* p = read_CP();
    database->pHash = p;

    CDHNextTuple* d = read_CDH();
    database->dHash = d;

    CRNextTuple* r = read_CR();
    database->rHash = r;


    return database;
}


void print_Database(Database db){
	printf("Printing Database:\n\n");
	print_SNAP(db->sHash);
	print_CSG(db->cHash);
	print_CP(db->pHash);
	print_CDH(db->dHash);
	print_CR(db->rHash);
	printf("\n");
}

void free_Database (Database d){

	//need to free each of the 5 arrays
	// go into each bucket of the hash array
	for (int i = 0; i < 17; i++){
		if (d->sHash[i] != NULL){
			SNAPTuple currTuple = d->sHash[i];
			SNAPTuple tempTuple = currTuple->next;
			while (currTuple != NULL){
                free(currTuple);
				currTuple = tempTuple;
				if (currTuple != NULL){
					tempTuple = currTuple->next;
				}
			}
		}
	}
	free(d->sHash);

	for (int i = 0; i < 17; i++){
		if (d->cHash[i] != NULL){
			CSGTuple currTuple = d->cHash[i];
			CSGTuple tempTuple = currTuple->next;
			while (currTuple != NULL){
				free(currTuple);
				currTuple = tempTuple;
				if (currTuple != NULL){
					tempTuple = currTuple->next;
				}
			}

		}
	}
	free(d->cHash);

	for (int i = 0; i < 17; i++){
		if (d->pHash[i] != NULL){
			CPTuple currTuple = d->pHash[i];
			CPTuple tempTuple = currTuple->next;
			while (currTuple != NULL){
				free(currTuple);
				currTuple = tempTuple;
				if (currTuple != NULL){
					tempTuple = currTuple->next;
				}
			}

		}
	}
	free(d->pHash);

	for (int i = 0; i < 17; i++){
		if (d->dHash[i] != NULL){
			CDHTuple currTuple = d->dHash[i];
			CDHTuple tempTuple = currTuple->next;
			while (currTuple != NULL){
				free(currTuple);
				currTuple = tempTuple;
				if (currTuple != NULL){
					tempTuple = currTuple->next;
				}
			}

		}
	}
	free(d->dHash);

	for (int i = 0; i < 17; i++){
		if (d->rHash[i] != NULL){
			CRTuple currTuple = d->rHash[i];
			CRTuple tempTuple = currTuple->next;
			while (currTuple != NULL){
				free(currTuple);
				currTuple = tempTuple;
				if (currTuple != NULL){
					tempTuple = currTuple->next;
				}
			}
		}
	}
	free(d->rHash);

	free(d);
}


SNAPNextTuple* create_SNAP (){
	SNAPNextTuple* SNAPHash = (SNAPTuple*)malloc(17*sizeof(SNAPTuple));

	insert_SNAP(11111, "M. Smith", "1 Exchange Blvd", "555-1212", SNAPHash);

	insert_SNAP(12345, "B. Biro", "2700 B-H Townline Rd", "555-1111", SNAPHash);

	insert_SNAP(67890, "L. Rousek", "1 Exchange Blvd", "555-1234", SNAPHash);

	insert_SNAP(12321,"M. Pekar", "80 Lyndon Rd", "555-2222", SNAPHash);

	insert_SNAP(98789, "M. Smith", "123 Ling Rd", "555-3333", SNAPHash);

	return SNAPHash;

}

bool insert_SNAP(int id, char* n, char* a, char* p,  SNAPNextTuple* theHash){
	SNAPTuple tup = (SNAPTuple)malloc(sizeof(struct SNAPTuple));
	tup->StudentId = id;
	strcpy(tup->Name, n);
	strcpy(tup->Address, a);
	strcpy(tup->Phone, p);
	tup->next = NULL;

	//printf("inserting\n");
	int hashKey = tup->StudentId;
	hashKey = hashKey%17;
	//empty bucket, no collision
	if (theHash[hashKey] == NULL){
		theHash[hashKey] = tup;
		return true;

		//if there is already an item in the bucket
	} else{
		SNAPTuple currentBucketItem = theHash[hashKey];
		//make sure the tuple isn't already in the bucket, meaning same key
		if (currentBucketItem->StudentId == tup->StudentId){
			//printf("Tuple already exists\n");
			return false;
		}
		while (currentBucketItem->next != NULL){
			//make sure the tuple isn't already in the bucket, meaning same key
			if (currentBucketItem->StudentId == tup->StudentId){
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

void delete_SNAP(int s, char* n, char* a, char* p, SNAPNextTuple* theHash) {

	int hashKey = s;
	hashKey = hashKey%17;
	if (theHash[hashKey]!= NULL) {
		SNAPTuple currentBucketItem = theHash[hashKey];
		if ((currentBucketItem->StudentId == s)
				&& (strcmp(currentBucketItem->Name, n)==0|| n[0] == '*')
				&& (strcmp(currentBucketItem->Address, a)==0 || a[0] == '*')
				&& (strcmp(currentBucketItem->Phone, p)==0 || p[0] == '*')) {
			//printf("%s\n", "Reached 1");
			if (currentBucketItem->next == NULL) {
				//first option
				//printf("%s\n", "Reached first option");
				theHash[hashKey] = NULL;
				free(currentBucketItem);
			} else {
				theHash[hashKey] = currentBucketItem->next;
			}
		} else if (currentBucketItem->next != NULL) {
			//printf("%s\n", "Reached 2");
			SNAPTuple prevBucketItem = currentBucketItem;
			currentBucketItem = currentBucketItem->next;
			do {
				if ((currentBucketItem->StudentId == s || s == '*')
						&& (strcmp(currentBucketItem->Name, n)==0 || n[0] == '*')
						&& (strcmp(currentBucketItem->Address, a)==0 || a[0] == '*')
						&& (strcmp(currentBucketItem->Phone, p)==0 || p[0] == '*')) {
					if (prevBucketItem != NULL && currentBucketItem->next != NULL) {
						//third option (has next)
						prevBucketItem->next = currentBucketItem->next;
						free(currentBucketItem);
					} else if (prevBucketItem != NULL && currentBucketItem->next == NULL) {
						prevBucketItem->next = NULL;
						free(currentBucketItem);
					}

				}
				prevBucketItem = currentBucketItem;
				currentBucketItem = currentBucketItem->next;
			} while (currentBucketItem != NULL);
			//printf("%s", "No matches found\n");
		} else {
			printf("%s", "No matches found\n" );
		}
	}
	else {
		printf("%s", "No matches found\n");
	}
}

SNAPTuple lookup_SNAP(int s, char*n, char* a, char* p, SNAPNextTuple* theHash) {

	int hashKey = s;
	hashKey = hashKey%17;
	if (theHash[hashKey]!= NULL) {
		SNAPTuple currentBucketItem = theHash[hashKey];
		do {
			if ((currentBucketItem->StudentId == s)
					&& (strcmp(currentBucketItem->Name, n)==0 || n[0] == '*')
					&& (strcmp(currentBucketItem->Address, a)==0 || a[0] == '*')
					&& (strcmp(currentBucketItem->Phone, p)==0 || p[0] == '*')) {
				return currentBucketItem;
			}
			currentBucketItem = currentBucketItem->next;
		} while (currentBucketItem != NULL);
	} else {
		return NULL;
	}
	return NULL;
}

void print_SNAP(SNAPNextTuple* hash){

	printf("printing SNAP relation:\n");
	for (int i = 0; i < 17; i++){
		printf("Bucket %d:\n", i);
		if (hash[i] != NULL){
			SNAPTuple currBucket = hash[i];
			while (currBucket != NULL){
				print_SNAPTuple(currBucket);
				currBucket = currBucket->next;
			}
			printf("\n");
		}

	}
	printf("\n");
}

void print_SNAPTuple(SNAPTuple t){
	printf("   [ID: %d, Name: %s, Addr: %s, Phone: %s]   ", t->StudentId, t->Name, t->Address, t->Phone);
}



CSGNextTuple* create_CSG (){
	CSGNextTuple* CSGHash = (CSGTuple*)malloc(17*sizeof(CSGTuple));


	insert_CSG("CSC171", 12345, "A", CSGHash);

	insert_CSG("CSC171", 67890, "B", CSGHash);

	insert_CSG("MATH150", 12345, "A", CSGHash);

	insert_CSG("DSCC201", 12345, "C", CSGHash);

	insert_CSG("DSCC201", 11111, "B+", CSGHash);

	insert_CSG("CSC172", 98789, "A-", CSGHash);

	insert_CSG("MATH150", 67890, "C+", CSGHash);

	insert_CSG("CSC173", 12321, "B+", CSGHash);

	insert_CSG("CSC173", 98789, "A", CSGHash);


	return CSGHash;
}

bool insert_CSG(char* c, int id, char* g, CSGNextTuple* theHash){

	CSGTuple tup = (CSGTuple)malloc(sizeof(struct CSGTuple));
	strcpy(tup->Course, c);
	tup->StudentId = id;
	strcpy(tup->Grade, g);
	tup->next = NULL;


	int hashKey = tup->StudentId;
	for (int j = 0; j < 8; j++){
		if (tup->Course[j] == 0){
			break;
		}
		hashKey = hashKey + (int)tup->Course[j];
	}

	hashKey = hashKey%17;
	//empty bucket, no collision
	if (theHash[hashKey] == NULL){
		theHash[hashKey] = tup;
		return true;

		//if there is already an item in the bucket
	} else{
		CSGTuple currentBucketItem = theHash[hashKey];
		//make sure the tuple isn't already in the bucket, meaning same key
		if ((currentBucketItem->StudentId == tup->StudentId) && (strcmp(currentBucketItem->Course, tup->Course) == 0)){
			//printf("Tuple already exists\n");
			return false;
		}
		while (currentBucketItem->next != NULL){
			//make sure the tuple isn't already in the bucket, meaning same key
			if ((currentBucketItem->StudentId == tup->StudentId) && (strcmp(currentBucketItem->Course, tup->Course) == 0)){
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

void delete_CSG(char* c, int s, char* g, CSGNextTuple* theHash){

	int hashKey = s;
	for (int j = 0; j < 8; j++){
		if (c[j] == 0){
			break;
		}
		hashKey = hashKey + c[j];
	}

	hashKey = hashKey%17;

	if (theHash[hashKey]!= NULL) {
		CSGTuple currentBucketItem = theHash[hashKey];
		if ((currentBucketItem->StudentId == s)
				&& (strcmp(currentBucketItem->Course, c)==0)
				&& (strcmp(currentBucketItem->Grade, g)==0 || g[0] == '*')) {
			//printf("%s\n", "Reached 1");
			if (currentBucketItem->next == NULL) {
				//first option
				//printf("%s\n", "Reached first option");
				theHash[hashKey] = NULL;
				free(currentBucketItem);
			} else {
				theHash[hashKey] = currentBucketItem->next;
			}
		} else if (currentBucketItem->next != NULL) {
			//printf("%s\n", "Reached 2");
			CSGTuple prevBucketItem = currentBucketItem;
			currentBucketItem = currentBucketItem->next;
			do {
				if ((currentBucketItem->StudentId == s)
						&& (strcmp(currentBucketItem->Course, c)==0)
						&& (strcmp(currentBucketItem->Grade, g)==0 || g[0] == '*')) {
					if (prevBucketItem != NULL && currentBucketItem->next != NULL) {
						//third option (has next)
						prevBucketItem->next = currentBucketItem->next;
						free(currentBucketItem);
					} else if (prevBucketItem != NULL && currentBucketItem->next == NULL) {
						prevBucketItem->next = NULL;
						free(currentBucketItem);
					}

				}
				prevBucketItem = currentBucketItem;
				currentBucketItem = currentBucketItem->next;
			} while (currentBucketItem != NULL);
			//printf("%s", "No matches found\n");
		} else {
			printf("%s", "No matches found\n" );
		}
	}
	else {
		printf("%s", "No matches found\n");
	}
}

CSGTuple lookup_CSG(char* c, int s, char* g, CSGNextTuple* theHash){
	int hashKey = s;
	for (int j = 0; j < 8; j++){
		if (c[j] == 0){
			break;
		}
		hashKey = hashKey + c[j];
	}

	hashKey = hashKey%17;

	if (theHash[hashKey]!= NULL) {
		CSGTuple currentBucketItem = theHash[hashKey];
		do {
			if ((currentBucketItem->StudentId == s)
					&& (strcmp(currentBucketItem->Course, c)==0)
					&& (strcmp(currentBucketItem->Grade, g)==0 || g[0] == '*')) {
				return currentBucketItem;
			}
			currentBucketItem = currentBucketItem->next;
		} while (currentBucketItem != NULL);
	} else {
		return NULL;
	}
	return NULL;
}

void print_CSG(CSGNextTuple* hash){
	printf("printing CSG relation:\n");
	for (int i = 0; i < 17; i++){
		printf("Bucket %d:\n", i);
		if (hash[i] != NULL){
			CSGTuple currBucket = hash[i];
			while (currBucket != NULL){
				print_CSGTuple(currBucket);
				currBucket = currBucket->next;
			}
			printf("\n");
		}
	}
	printf("\n");
}

void print_CSGTuple(CSGTuple t){
	printf("   [Course: %s, ID: %d, Grade: %s]   ", t->Course, t->StudentId, t->Grade);
}



CPNextTuple* create_CP (){

	CPNextTuple* CPHash = (CPTuple*) malloc(17*sizeof(CPNextTuple));

	insert_CP("CSC172", "CSC171", CPHash);

	insert_CP("CSC172", "MATH150", CPHash);

	insert_CP("CSC173", "CSC172", CPHash);

	insert_CP("CSC252", "CSC172", CPHash);

	insert_CP("CSC254", "CSC252", CPHash);

	insert_CP("DSCC201", "CSC171", CPHash);

	insert_CP("DSCC202", "DSCC201", CPHash);

	insert_CP("DSCC265", "CSC262", CPHash);

	insert_CP("DSCC265", "CSC171", CPHash);

	return CPHash;

}

bool insert_CP(char* c, char* p, CPNextTuple* theHash){

	CPTuple tup = (CPTuple)malloc(sizeof(struct CPTuple));
	strcpy(tup->Course, c);
	strcpy(tup->PreReq, p);
	tup->next = NULL;

	int hashKey = 0;
	for (int i=0; i<8; i++) {
		if (tup->Course[i] == 0){
			break;
		}
		hashKey = hashKey + (int)tup->Course[i];
	}

	for (int j = 0; j < 8; j++){
		if (tup->Course[j] == 0){
			break;
		}
		hashKey = hashKey + (int)tup->PreReq[j];
	}

	hashKey = hashKey%17;
	if (theHash[hashKey]== NULL){
		theHash[hashKey] = tup;
		return true;

		//if there is already an item in the bucket
	} else{
		CPTuple currentBucketItem = theHash[hashKey];
		//make sure the tuple isn't already in the bucket, meaning same key
		if ((strcmp(currentBucketItem->Course, tup->Course)==0) &&
				(strcmp(currentBucketItem->PreReq, tup->PreReq)==0)){
			printf("Tuple already exists\n");
			return false;
		}
		while (currentBucketItem->next != NULL){
			//make sure the tuple isn't already in the bucket, meaning same key
			if (strcmp(currentBucketItem->Course, tup->Course)==0 &&
					strcmp(currentBucketItem->PreReq, tup->PreReq)==0){
				printf("Tuple already exists\n");
				return false;
			}
			currentBucketItem = currentBucketItem->next;
		}
		currentBucketItem->next = tup;
		return true;
	}
	return false;
}

void delete_CP(char* c, char* p, CPNextTuple* theHash){
	int hashKey = 0;
	for (int i=0; i<8; i++) {
		if (c[i]==0) {
			break;
		}
		hashKey = hashKey + c[i];
	}
	for (int j = 0; j<8; j++){
		if (p[j]==0) {
			break;
		}
		hashKey = hashKey + p[j];
	}
	hashKey = hashKey%17;
	//printf("Hash key is %d\n", hashKey);

	if (theHash[hashKey]!= NULL) {
		CPTuple currentBucketItem = theHash[hashKey];
		if ((strcmp(currentBucketItem->Course, c)==0)
				&& (strcmp(currentBucketItem->PreReq, p)==0)) {
			//printf("%s\n", "Reached 1");
			if (currentBucketItem->next == NULL) {
				//first option
				//printf("%s\n", "Reached first option");
				theHash[hashKey] = NULL;
				free(currentBucketItem);
			} else {
				theHash[hashKey] = currentBucketItem->next;
			}
		} else if (currentBucketItem->next != NULL) {
			//printf("%s\n", "Reached 2");
			CPTuple prevBucketItem = currentBucketItem;
			currentBucketItem = currentBucketItem->next;
			do {
				if ((strcmp(currentBucketItem->Course, c)==0)
						&& (strcmp(currentBucketItem->PreReq, p)==0)) {
					if (prevBucketItem != NULL && currentBucketItem->next != NULL) {
						//third option (in the middle)
						prevBucketItem->next = currentBucketItem->next;
						free(currentBucketItem);
					} else if (prevBucketItem != NULL && currentBucketItem->next == NULL) {
						//second option (last)
						prevBucketItem->next = NULL;
						free(currentBucketItem);
					}
				}
				prevBucketItem = currentBucketItem;
				currentBucketItem = currentBucketItem->next;
			} while (currentBucketItem != NULL);
			//printf("%s", "No matches found 3\n");
		} else {
			printf("%s", "No matches found \n" );
		}
	} else {
		printf("%s", "No matches found \n");
	}

}

CPTuple lookup_CP(char* c, char* p, CPNextTuple* theHash){
	int hashKey = 0;
	for (int i=0; i<8; i++) {
		if (c[i]==0) {
			break;
		}
		hashKey = hashKey + c[i];
	}
	for (int j = 0; j<8; j++){
		if (p[j]==0) {
			break;
		}
		hashKey = hashKey + p[j];
	}
	hashKey = hashKey%17;

	if (theHash[hashKey]!= NULL) {
		CPTuple currentBucketItem = theHash[hashKey];
		do {
			if ((strcmp(currentBucketItem->Course, c)==0)
					&& (strcmp(currentBucketItem->PreReq, p)==0)) {
				return currentBucketItem;
			}
			currentBucketItem = currentBucketItem->next;
		} while (currentBucketItem != NULL);
	} else {
		return NULL;
	}
	return NULL;
}

void print_CP(CPNextTuple* hash){
	printf("printing CP relation:\n");
	for (int i = 0; i < 17; i++){
		printf("Bucket %d:\n", i);
		if (hash[i] != NULL){
			CPTuple currBucket = hash[i];
			while (currBucket != NULL){
				print_CPTuple(currBucket);
				currBucket = currBucket->next;
			}
			printf("\n");
		}
	}
	printf("\n");
}

void print_CPTuple(CPTuple t){
	printf("   [Course: %s, PreReq: %s]   ", t->Course, t->PreReq);
}



CDHNextTuple* create_CDH (){

	CDHNextTuple* CDHHash = (CDHTuple*) malloc(17*sizeof(CDHNextTuple));

	insert_CDH("CSC171", 'T', 1400, CDHHash);

	insert_CDH("CSC171", 'R', 1400, CDHHash);

	insert_CDH("CSC172", 'T', 1525, CDHHash);

	insert_CDH("CSC172", 'R', 1640, CDHHash);

	insert_CDH("CSC173", 'T', 1400, CDHHash);

	insert_CDH( "CSC173", 'R', 1400, CDHHash);

	insert_CDH("CSC252", 'T', 1230, CDHHash);

	insert_CDH("CSC252", 'R', 1230, CDHHash);

	insert_CDH("DSCC201", 'M', 900, CDHHash);

	insert_CDH("DSCC201", 'W', 900, CDHHash);

	insert_CDH("DSCC202", 'M', 1650, CDHHash);

	insert_CDH("DSCC202", 'W', 1650, CDHHash);

	insert_CDH("DSCC265", 'M', 1400, CDHHash);

	insert_CDH( "DSCC265", 'W', 1400, CDHHash);

	return CDHHash;

}

bool insert_CDH(char* c, char d, int h, CDHNextTuple* theHash){

	CDHTuple tup = (CDHTuple)malloc(sizeof(struct CDHTuple));
	strcpy(tup->Course, c);
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

	if (theHash[hashKey]== NULL){
		theHash[hashKey] = tup;
		return true;

		//if there is already an item in the bucket
	} else{
		CDHTuple currentBucketItem = theHash[hashKey];
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

void delete_CDH(char* c, char d, int h, CDHNextTuple* theHash){
	if (d == '*'){
		for (int i = 0; i < 17; i++){
			if (theHash[i] != NULL){
				CDHTuple currentBucketItem = theHash[i];
				if ((strcmp(currentBucketItem->Course, c) == 0)
						&& (currentBucketItem->Hour == h|| h == -1)){
					//printf("%s\n", "Reached 1");
					if (currentBucketItem->next == NULL) {
						//first option
						theHash[i] = NULL;
						free(currentBucketItem);
					} else {
						theHash[i] = currentBucketItem->next;
					}
				}  else if (currentBucketItem->next != NULL) {
					CDHTuple prevBucketItem = currentBucketItem;
					currentBucketItem = currentBucketItem->next;
					do {
						if ((strcmp(currentBucketItem->Course, c)==0)
								&& (currentBucketItem->Hour == h || h == -1)) {
							if (prevBucketItem != NULL && currentBucketItem->next != NULL) {
								//third option (has next)
								prevBucketItem->next = currentBucketItem->next;
								free(currentBucketItem);

							} else if (prevBucketItem != NULL && currentBucketItem->next == NULL) {
								prevBucketItem->next = NULL;
								free(currentBucketItem);
							}

						}
						prevBucketItem = currentBucketItem;
						currentBucketItem = currentBucketItem->next;
					} while (currentBucketItem != NULL);
				} else{

				}
			}
		}

	} else{

		int hashKey = 0;
		for (int i=0; i<8; i++) {
			if (c[i] == 0){
				break;
			}
			hashKey = hashKey + (int)c[i];
		}
		hashKey = hashKey + d;
		hashKey = hashKey%17;

		if (theHash[hashKey]!= NULL) {
			CDHTuple currentBucketItem = theHash[hashKey];
			if ((currentBucketItem->Day == d)
					&& (strcmp(currentBucketItem->Course, c)==0)
					&& (currentBucketItem->Hour == h|| h == -1)) {
				//printf("%s\n", "Reached 1");
				if (currentBucketItem->next == NULL) {
					//first option
					//printf("%s\n", "Reached first option");
					theHash[hashKey] = NULL;
					free(currentBucketItem);
				} else {
					theHash[hashKey] = currentBucketItem->next;
				}
			} else if (currentBucketItem->next != NULL) {
				//printf("%s\n", "Reached 2");
				CDHTuple prevBucketItem = currentBucketItem;
				currentBucketItem = currentBucketItem->next;
				do {
					if (((currentBucketItem->Day == d))
							&& (strcmp(currentBucketItem->Course, c)==0)
							&& (currentBucketItem->Hour == h || h == -1)) {
						if (prevBucketItem != NULL && currentBucketItem->next != NULL) {
							//third option (has next)
							prevBucketItem->next = currentBucketItem->next;
							free(currentBucketItem);
						} else if (prevBucketItem != NULL && currentBucketItem->next == NULL) {
							prevBucketItem->next = NULL;
							free(currentBucketItem);
						}

					}
					prevBucketItem = currentBucketItem;
					currentBucketItem = currentBucketItem->next;
				} while (currentBucketItem != NULL);
				//printf("%s", "No matches found\n");
			} else {
				printf("%s", "No matches found\n" );
			}
		}
		else {
			printf("%s", "No matches found\n");
		}
	}
}

CDHTuple lookup_CDH(char* c, char d, int h, CDHNextTuple* theHash){
	int hashKey = 0;
	for (int i=0; i<8; i++) {
		if (c[i] == 0){
			break;
		}
		hashKey = hashKey + (int)c[i];
	}
	hashKey = hashKey + d;
	hashKey = hashKey%17;

	if (theHash[hashKey]!= NULL) {
		CDHTuple currentBucketItem = theHash[hashKey];
		do {
			if ((currentBucketItem->Day == d)
					&& (strcmp(currentBucketItem->Course, c)==0)
					&& (currentBucketItem->Hour == h|| h == -1)){
				return currentBucketItem;
			}
			currentBucketItem = currentBucketItem->next;
		} while (currentBucketItem != NULL);
	} else {
		return NULL;
	}
	return NULL;
}

void print_CDH(CDHNextTuple* hash){
	printf("printing CDH relation:\n");
	for (int i = 0; i < 17; i++){
		printf("Bucket %d:\n", i);
		if (hash[i] != NULL){
			CDHTuple currBucket = hash[i];
			while (currBucket != NULL){
				print_CDHTuple(currBucket);
				currBucket = currBucket->next;
			}
			printf("\n");
		}
	}
	printf("\n");
}

void print_CDHTuple(CDHTuple t){
	printf("   [Course: %s, Day: %c, Hour: %d]   ", t->Course, t->Day, t->Hour);
}



CRNextTuple* create_CR (){
	CRNextTuple* CRHash = (CRTuple*)malloc(17*sizeof(CRTuple));

	insert_CR("CSC171", "Hutchison Hall 141", CRHash);

	insert_CR("CSC172", "Hutchison Hall 141", CRHash);

	insert_CR("CSC173", "Wegmans 1400", CRHash);

	insert_CR("CSC252", "Wegmans 1400", CRHash);

	insert_CR("CSC254", "Wegmans 1400", CRHash);

	insert_CR("DSCC201", "Bausch & Lomb 109", CRHash);

	insert_CR("DSCC202", "Dewey 2162", CRHash);

	insert_CR("DSCC265", "Wegmans 1400", CRHash);

	insert_CR("MATH150", "Harkness 115", CRHash);

	return CRHash;

}

bool insert_CR(char* c, char* r, CRNextTuple* theHash){

	CRTuple tup = (CRTuple)malloc(sizeof(struct CRTuple));
	strcpy(tup->Course, c);
	strcpy(tup->Room, r);
	tup->next = NULL;

	int hashKey = 0;
	for (int j = 0; j < 8; j++){
		if (tup->Course[j] == 0){
			break;
		}
		hashKey += tup->Course[j];

	}
	hashKey = hashKey%17;

	//empty bucket, no collision
	if (theHash[hashKey]== NULL){
		theHash[hashKey] = tup;
		return true;

		//if there is already an item in the bucket
	} else{
		CRTuple currentBucketItem = theHash[hashKey];
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

void delete_CR(char* c, char* r, CRNextTuple* theHash){
	int hashKey = 0;
	for (int j = 0; j < 8; j++){
		if (c[j]==0) {
			break;
		}
		hashKey += c[j];
	}
	hashKey = hashKey%17;

	if (theHash[hashKey]!= NULL) {
		CRTuple currentBucketItem = theHash[hashKey];
		if ((strcmp(currentBucketItem->Course, c)==0)
				&& (strcmp(currentBucketItem->Room, r)==0 || r[0] == '*')) {
			//printf("%s\n", "Reached 1");
			if (currentBucketItem->next == NULL) {
				//first option
				//printf("%s\n", "Reached first option");
				theHash[hashKey] = NULL;
				free(currentBucketItem);
			} else {
				theHash[hashKey] = currentBucketItem->next;
			}
		} else if (currentBucketItem->next != NULL) {
			//printf("%s\n", "Reached 2");
			CRTuple prevBucketItem = currentBucketItem;
			currentBucketItem = currentBucketItem->next;
			do {
				if ((strcmp(currentBucketItem->Course, c)==0)
						&& (strcmp(currentBucketItem->Room, r)==0 || r[0] == '*')) {
					if (prevBucketItem != NULL && currentBucketItem->next != NULL) {
						//third option (in the middle)
						prevBucketItem->next = currentBucketItem->next;
						free(currentBucketItem);
					} else if (prevBucketItem != NULL && currentBucketItem->next == NULL) {
						//second option (last)
						prevBucketItem->next = NULL;
						free(currentBucketItem);
					}
				}
				prevBucketItem = currentBucketItem;
				currentBucketItem = currentBucketItem->next;
			} while (currentBucketItem != NULL);
			//printf("%s", "No matches found\n");
		} else {
			printf("%s", "No matches found\n" );
		}
	} else {
		printf("%s", "No matches found\n");
	}
}

CRTuple lookup_CR(char* c, char* r, CRNextTuple* theHash){
	int hashKey = 0;
	for (int j = 0; j < 8; j++){
		if (c[j]==0) {
			break;
		}
		hashKey += c[j];
	}
	hashKey = hashKey%17;

	if (theHash[hashKey]!= NULL) {
		CRTuple currentBucketItem = theHash[hashKey];
		do {
			if ((strcmp(currentBucketItem->Course, c)==0)
					&& (strcmp(currentBucketItem->Room, r)==0 || r[0] == '*')) {
				return currentBucketItem;
			}
			currentBucketItem = currentBucketItem->next;
		} while (currentBucketItem != NULL);
	} else {
		return NULL;
	}
	return NULL;
}

void print_CR(CRNextTuple* hash){
	printf("printing CR relation:\n");
	for (int i = 0; i < 17; i++){
		printf("Bucket %d:\n", i);
		if (hash[i] != NULL){
			CRTuple currBucket = hash[i];
			while (currBucket != NULL){
				print_CRTuple(currBucket);
				currBucket = currBucket->next;
			}
			printf("\n");
		}
	}
	printf("\n");
}

void print_CRTuple(CRTuple t){
	printf("   [Course: %s, Room: %s]   ", t->Course, t->Room);
}



void getGradeForNameCourse (char* n, char* c, Database db){
	/*
	 * (1) for each tuple t in StudentId-Name-Address-Phone do
		(2) if t has “C. Brown” in its Name component then begin
		(3) let i be the StudentId component of tuple t;
		(4) for each tuple s in Course-StudentId-Grade do
		(5) if s has Course component “CS101” and StudentId component i then
		(6) print the Grade component of tuple s;
		end
	 */

	bool isFound = false;
	//(1) for each tuple t in StudentId-Name-Address-Phone do
	for (int i = 0; i < 17; i ++){
		SNAPTuple currTuple = db->sHash[i];
		if (currTuple != NULL){
			do{
				//printf("%d \n", currTuple->StudentId);
				//(2) if t has “C. Brown” in its Name component then begin
				if (strcmp(currTuple->Name, n)==0){
					//(3) let i be the StudentId component of tuple t;
					int id = currTuple->StudentId;
					//(4) for each tuple s in Course-StudentId-Grade do
					//(5) if s has Course component “CS101” and StudentId component i then
					CSGTuple foundTuple = lookup_CSG(c, id, "*", db->cHash);
					//(6) print the Grade component of tuple s;
					if (foundTuple != NULL){
						isFound = true;
						printf("%s's grade in %s is %s\n", n, foundTuple->Course, foundTuple->Grade);
					}

				}
				currTuple = currTuple->next;
			} while (currTuple != NULL);
		}

	}
	if (!isFound){
		printf("Invalid input for name and course, no grade exists\n");
	}

}

void getRoomForNameDayHour (char* n, char d, int h, Database db){
	/*1. Find the student ID for C. Brown, using the StudentId-Name-Address-Phone
	 * 		 relation for C. Brown. Let this ID number be i.
	 * 2. Look up in the Course-StudentId-Grade relation all tuples with StudentId
	 * 		component i. Let {c1, . . . , ck} be the set of Course values in these tuples.
	 * 3. In the Course-Day-Hour relation, look for tuples with Course component ci, that is,
	 * 		one of the courses found in step (2). There should be at most one that has both
	 * 		“M” in the Day component and “9AM” in the Hour component.
	 * 4. If a course c is found in step (3), then look up in the Course-Room relation
	 * 		the room in which course c meets. That is where C. Brown will be found on
	 * 		Mondays at 9AM, assuming that he hasn’t decided to take a long weekend.*/

	bool isFound = false;
	//(1)
	for (int i = 0; i < 17; i ++){
		SNAPTuple currTuple = db->sHash[i];
		if (currTuple != NULL){
			do{
				//printf("%d \n", currTuple->StudentId);
				if (strcmp(currTuple->Name, n)==0){
					int id = currTuple->StudentId;
					//(2)
					for (int j = 0; j < 17; j++){
						CSGTuple cTuple = db->cHash[j];
						if (cTuple != NULL){
							do{
								if (cTuple->StudentId == id){
									char* course = cTuple->Course;
									//(3)
									CDHTuple tempTuple = lookup_CDH(course, d, h, db->dHash);
									if (tempTuple != NULL){
										//(4)
										CRTuple roomTuple = lookup_CR(tempTuple->Course, "*", db->rHash);
										if (roomTuple != NULL){
											isFound = true;
											printf("%s will be found at %s at %d on %c\n", n, roomTuple->Room, h, d);
										}
									}
								}

								cTuple = cTuple->next;
							}while (cTuple != NULL);
						}

					}
				}
				currTuple = currTuple->next;
			} while (currTuple != NULL);
		}

	}
	if (!isFound){
		printf("Invalid input for name and day and hour, no room exists\n");

	}
}
