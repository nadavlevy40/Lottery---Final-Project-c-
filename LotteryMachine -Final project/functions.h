/* Final Project - Lottery */


#define _CRT_SECURE_NO_WARNINGS


/*------------------------- All the libraries we will use in this program: -------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
/*--------------------------------------------------------------------------------------------------------*/




/*------------------------- All the "defines" we will use in this program: -------------------------------*/
#define MEMORY_ALLOCATION_FAIL 1
#define MAX_PLAYER_NAME 100
#define COL_SIZE 6
#define MAX_NUM_IN_COL 15
#define MANUAL 0
#define AUTO 1
#define EXIT_BY_USER 1
#define READ_FILE 2
#define WRITE_FILE 3
/*--------------------------------------------------------------------------------------------------------*/




/*------------------------- All the structs we will use in this program: -------------------------------*/

/*------ A linked list of each participant ------*/
typedef struct list_node {
	int* col;
	int hits;
	struct list_node* next;
	struct list_node* prev;
}ListNode;

typedef struct list {
	ListNode* head;
	ListNode* tail;
}List;
/*-----------------------------------------------*/


typedef struct participant {
	char name[MAX_PLAYER_NAME];
	List colList;
	int numOfCols;
}Participant;


/*------ A linked list of all participants ------*/
typedef struct participant_list_node {
	Participant data;
	struct participant_list_node* next;
	struct participant_list_node* prev;
}ParticipantListNode;

typedef struct participant_list {
	ParticipantListNode* head;
	ParticipantListNode* tail;
}ParticipantList;
/*-----------------------------------------------*/

/*------------------------------------------------------------------------------------------------------*/







/*------------------------- All the functions we will use in this program: -------------------------------*/
void chooseByUser();
void choiseOne();
ParticipantList getParticipantList(int numOfUsers);
void makeEmptyParticipantList(ParticipantList* res);
void insertDataToEndParticipantList(ParticipantList* list, Participant userInfo);
ParticipantListNode* createNewParticipantListNode(Participant data, ParticipantListNode* next, ParticipantListNode* prev);
void insertNodeToEndParticipantList(ParticipantList* list, ParticipantListNode* tail);
bool isEmptyParticipantList(ParticipantList* list);
List subChooseByUser(int* N);
void fillManual(List* res, int* N);
void fillAuto(List* res, int* N);
void getColList(int numOfCols, List* res, int autoOrManual);
void makeEmptyList(List* res);
void getCol(List* res, int autoOrManual);
bool checkValid(int* column, int num, int autoOrManual);
void insertDataToEndList(List* list, int* col);
ListNode* createNewListNode(int* data, ListNode* next, ListNode* prev);
void insertNodeToEndList(List* list, ListNode* tail);
bool isEmptyList(List* list);
void getWinnerCol(int* winnerCol);
void updateColCountersArr(int* arr, int* countersArr);
void updateHits(ParticipantList* lst, int* winnerColCountersArr);
void updateHitsHelper(List* lst, int* winnerColCountersArr);
void compareCountersArrays(int* winnerColCountersArr, int* colCountersArr, ListNode* curr);
void sortList(List* lst);
void searchIinHits(List* lst, int i, int* counter);
char* getBestAverage(ParticipantList* lst);
void getBestAverageHelper(ParticipantListNode* currParicipant, char** res, float* bestAverage);
void pressToContinue();
void saveToBinFile(ParticipantList* list, int numOfUsers, int* winnerCol);
void saveToBinFileHelper(ParticipantListNode* currParticipant, int numOfUsers, int* winnerCol, FILE* file);
void compressedCol(int* col, FILE* file);
void saveLetters(char* name, int numOfLetters, FILE* file);
void compressedWinnerCol(int* winnerCol, FILE* file);
void choiseTwo();
ParticipantList getParticipantListFromFile(int numOfParticipants, FILE* binFile);
List getListOfCols(FILE* binFile, int numOfCols);
void getColsFromFile(FILE* binFile, List* res);
void getWinnerColFromFile(int* winnerCol, FILE* binFile);
void pressToContinue2();

/*------------ Checking allocations and file opening functions ------------*/
void checkMemoryAllocation(void* ptr);
void checkFileOpen(FILE* fp, int readOrWrite);

/*-------------------------- Printing functions ---------------------------*/
void printMenu();
void printSubMenu();
void printAll(ParticipantList* lst, int* winnerCol);
void printList(List* lst);
void printParticipantList(ParticipantList* lst);
void printWinnerCol(int* winnerCol);
void printColsForEachHit(ParticipantList* lst);

/*------------------------ Free memory functions -------------------------*/
void freeParticipantList(ParticipantList* lst);
void freeList(List* lst);
/*--------------------------------------------------------------------------------------------------------*/