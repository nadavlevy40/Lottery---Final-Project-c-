/* Final Project - Lottery */


#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"


void gamePlay()
{
	/* This function runs the lottery as long as the user did not choose 'EXIT' from the main menu. */

	while (true)
		chooseByUser();
}


void chooseByUser()
{
	/* A function that captures the user's selection from the menu displayed on the screen. */

	int choose;

	printMenu();

	printf("Your choise:  ");
	scanf("%d", &choose);
	getchar();

	while (choose < 1 || choose > 3)
	{ /* As long as the user selection is invalid, the game menu will be displayed again and again. */
		system("cls");
		printf("\nPlease enter a valid number from the menu!\n");
		printMenu();
		printf("Your choise:  ");
		scanf("%d", &choose);
		getchar();
	}

	switch (choose)
	{
	case 1:
		system("cls");
		choiseOne();
		break;

	case 2:
		system("cls");
		choiseTwo();
		break;

	case 3:
		exit(EXIT_BY_USER);
		break;
	}
}


void choiseOne()
{
	/*  A function which is called if the user selected option 1 from the menu */

	int numOfUsers, i;
	ParticipantList list;
	int* winnerCol, * winnerColCountersArr;

	winnerCol = (int*)calloc(COL_SIZE, sizeof(int));
	checkMemoryAllocation(winnerCol);
	winnerColCountersArr = (int*)calloc(MAX_NUM_IN_COL, sizeof(int));
	checkMemoryAllocation(winnerColCountersArr);

	printf("\nPlease enter the number of participants in the lottery:  ");
	scanf("%d", &numOfUsers);

	while (numOfUsers < 1)
	{/* As long as the user selection is invalid, the game menu will be displayed again and again. */
		system("cls");
		printf("\nPlease enter a valid number of participants (must be greater than 0):   ");
		scanf("%d", &numOfUsers);
	}

	list = getParticipantList(numOfUsers);

	getWinnerCol(winnerCol);
	updateColCountersArr(winnerCol, winnerColCountersArr);
	updateHits(&list, winnerColCountersArr);

	printf("-----------------------------------------------------------\n");
	printf("THE RESULTS OF THE  LOTTERY:");
	printf("\n-----------------------------------------------------------\n\n");
	printAll(&list, winnerCol);

	pressToContinue();
	saveToBinFile(&list, numOfUsers, winnerCol);
	free(winnerCol);
	free(winnerColCountersArr);
	freeParticipantList(&list);
}


ParticipantList getParticipantList(int numOfUsers)
{
	/* This function makes a list of participants,
	It captures the names of the participants from the user. */

	int i, N;
	ParticipantList res;
	Participant userInfo;

	makeEmptyParticipantList(&res);

	for (i = 0; i < numOfUsers; i++)
	{
		printf("\n\nPlease insert player's name:  ");
		scanf("%s", userInfo.name);

		userInfo.colList = subChooseByUser(&N);
		userInfo.numOfCols = N;

		insertDataToEndParticipantList(&res, userInfo);

		Sleep(2000);
		system("cls");
	}

	return res;
}


void makeEmptyParticipantList(ParticipantList* res)
{
	/* This function make empty participant list */

	res->head = res->tail = NULL;
}


void insertDataToEndParticipantList(ParticipantList* list, Participant userInfo)
{
	/*  This function adds a new value to the end of the linked list.
	It uses the auxiliary functions "createNewParticipantListNode" and "insertNodeToEndParticipantList". */

	ParticipantListNode* newTail;
	newTail = createNewParticipantListNode(userInfo, NULL, NULL);
	insertNodeToEndParticipantList(list, newTail);
}


ParticipantListNode* createNewParticipantListNode(Participant data, ParticipantListNode* next, ParticipantListNode* prev)
{
	/* This function creates a new participantList node. */

	ParticipantListNode* res;
	res = (ParticipantListNode*)malloc(sizeof(ParticipantListNode));
	checkMemoryAllocation(res);

	res->data = data;
	res->next = next;
	res->prev = prev;

	return res;
}


void insertNodeToEndParticipantList(ParticipantList* list, ParticipantListNode* tail)
{
	/*  This function inserts the new node with the new data to the end of the list. */

	if (isEmptyParticipantList(list) == true)
	{
		tail->next = tail->prev = NULL;
		list->head = list->tail = tail;
	}
	else
	{
		tail->prev = list->tail;
		tail->next = NULL;
		list->tail->next = tail;
		list->tail = tail;
	}
}


bool isEmptyParticipantList(ParticipantList* list)
{
	/* A Boolean function that checks if the list is empty. */

	if (list->head == NULL)
		return true;

	return false;
}


List subChooseByUser(int* N)
{
	/* A function that captures the user's selection from the sub menu displayed on the screen.
	In addition, the function returns a linked list of columns for each participant. */

	List res;
	int choose;

	printSubMenu();

	printf("Your choise:  ");
	scanf("%d", &choose);
	getchar();

	makeEmptyList(&res);

	while (choose < 1 || choose > 2)
	{ /* As long as the user selection is invalid, the game menu will be displayed again and again. */
		system("cls");
		printf("\nPlease enter a valid number from the sub menu!\n");
		printSubMenu();
		printf("Your choise:  ");
		scanf("%d", &choose);
		getchar();
	}

	switch (choose)
	{
	case 1:
		fillManual(&res, N);
		break;
	case 2:
		fillAuto(&res, N);
		break;
	}

	return res;
}


void fillManual(List* res, int* N)
{ /* This function handles in case the user selects a manual selection of columns. */

	printf("\nPlease enter the number of columns: ");
	scanf("%d", N);
	printf("\n\n");
	getColList(*N, res, MANUAL);
	printf("The columns were filled in successfully\n");
}


void fillAuto(List* res, int* N)
{
	/* This function handles in case the user selects an automatic selection of columns. */

	printf("\nPlease enter the number of columns: ");
	scanf("%d", N);
	printf("\n");
	printf("Please wait, the system is randoming columns...\n\n");
	getColList(*N, res, AUTO);
	printf("The columns were filled in successfully\n");
}


void getColList(int numOfCols, List* res, int autoOrManual)
{
	/* This function makes a list of columns for each participant,
	The function differentiates between the instances of aotomatic or manual columns selection. */

	int i;

	makeEmptyList(res);


	for (i = 0; i < numOfCols; i++)
	{
		if (autoOrManual == MANUAL)
		{
			printf("Enter column number %d:  \n", i + 1);
			getCol(res, MANUAL);
		}
		else
			getCol(res, AUTO);
	}
}


void makeEmptyList(List* res)
{
	/* This function make empty columns list. */

	res->head = res->tail = NULL;
}


void getCol(List* res, int autoOrManual)
{
	/* This function gets a columns.
	The function differentiates between the instances of aotomatic or manual columns selection. */

	int i, num;

	int* column = (int*)calloc(COL_SIZE, sizeof(int));
	checkMemoryAllocation(column);


	for (i = 0; i < COL_SIZE; i++)
	{
		if (autoOrManual == MANUAL)
		{
			printf("Please enter a number between 1-15: ");
			scanf("%d", &num);

			while (!checkValid(column, num, MANUAL))
				scanf("%d", &num);
		}

		else
		{
			num = getRandomNum();
			while (!checkValid(column, num, AUTO))
				num = getRandomNum();
		}


		column[i] = num;
	}

	if (autoOrManual == MANUAL)
		printf("\n\n");

	insertDataToEndList(res, column);

}


bool checkValid(int* column, int num, int autoOrManual)
{
	/* A boolean function that checks if the number entered is valid:
	- It must be between 1-15.
	- Each number can appear only once in a column.
	The function differentiates between the instances of aotomatic or manual columns selection. */

	int i;

	if (autoOrManual == MANUAL)
		if (num < 1 || num > 15)
		{
			printf("The number must be between 1 - 15! Please enter a valid number: ");
			return false;
		}

	for (i = 0; i < COL_SIZE; i++)
	{
		if (num == column[i])
		{
			if (autoOrManual == MANUAL)
				printf("The number entered already appears in the column! Please enter another number: ");
			return false;
		}
	}

	return true;
}


int getRandomNum()
{
	/* A function that randomize a number between 1 and 15 and returns it. */

	srand(time(NULL));

	return (1 + rand() % MAX_NUM_IN_COL);
}


void insertDataToEndList(List* list, int* col)
{
	/*  This function adds a new value to the end of the linked list.
	It uses the auxiliary functions "createNewListNode" and "insertNodeToEndList". */

	ListNode* newTail;
	newTail = createNewListNode(col, NULL, NULL);
	insertNodeToEndList(list, newTail);
}


ListNode* createNewListNode(int* data, ListNode* next, ListNode* prev)
{
	/* This function creates a new list node. */

	ListNode* res;
	res = (ListNode*)malloc(sizeof(ListNode));
	checkMemoryAllocation(res);

	res->col = data;
	res->hits = 0;
	res->next = next;
	res->prev = prev;

	return res;
}


void insertNodeToEndList(List* list, ListNode* tail)
{
	/*  This function inserts the new node with the new data to the end of the list. */

	if (isEmptyList(list) == true)
	{
		tail->next = tail->prev = NULL;
		list->head = list->tail = tail;
	}
	else
	{
		tail->prev = list->tail;
		tail->next = NULL;
		list->tail->next = tail;
		list->tail = tail;
	}
}


bool isEmptyList(List* list)
{
	/* A Boolean function that checks if the list is empty. */

	if (list->head == NULL)
		return true;

	return false;
}


void getWinnerCol(int* winnerCol)
{
	/* This function randomize the winner column of the current lottery.
	It uses the auxiliary functions "getRandomNum" and "checkValid". */

	int i, num;

	printf("Please wait, the system is randoming the WINNER column...\n\n");

	for (i = 0; i < COL_SIZE; i++)
	{
		num = getRandomNum();
		while (!checkValid(winnerCol, num, AUTO))
			num = getRandomNum();
		winnerCol[i] = num;
	}

	system("cls");
}


void updateColCountersArr(int* arr, int* countersArr)
{
	/* This function updates the counters array of each column.
	Each array of counters is a physical size of 15.
	For each number that appears in the column (arr),
	the index [number-1] in the counters array (countersArr) will increase. */

	int i;

	for (i = 0; i < COL_SIZE; i++)
		countersArr[arr[i] - 1]++;
}


void updateHits(ParticipantList* lst, int* winnerColCountersArr)
{
	/* A function that goes through the list of participants,
	and updates the number of hits of each column for each particpant.
	It uses the auxiliary function "updateHitsHelper". */

	ParticipantListNode* curr = lst->head;
	int i;


	while (curr != NULL)
	{
		updateHitsHelper(&curr->data.colList, winnerColCountersArr);
		curr = curr->next;
		printf("\n");
	}
}


void updateHitsHelper(List* lst, int* winnerColCountersArr)
{
	/* A function that goes through the list of columns of each participant,
	and updates the number of hits of each column.
	This function creates a counters array for each column,
	And then compares the counters array of each column with the counters array of the winning column,
	and thus updates the hits of each column.
	It uses the auxiliary functions "updateColCountersArr" and "compareCountersArrays". */

	ListNode* curr = lst->head;
	int i;
	int* colCountersArr;


	while (curr != NULL)
	{
		colCountersArr = (int*)calloc(MAX_NUM_IN_COL, sizeof(int));
		checkMemoryAllocation(winnerColCountersArr);

		updateColCountersArr(curr->col, colCountersArr);

		compareCountersArrays(winnerColCountersArr, colCountersArr, curr);

		curr = curr->next;
		free(colCountersArr);
	}


}


void compareCountersArrays(int* winnerColCountersArr, int* colCountersArr, ListNode* curr)
{
	/* This function compares the counters array of each column with the counters array of the winning columns.
	If  winnerColCountersArr[i] equals to colCountersArr[i] and both of them equals to 1,
	the 'hits' of the current column is increased. */

	int i;

	for (i = 0; i < MAX_NUM_IN_COL; i++)
		if (winnerColCountersArr[i] == colCountersArr[i] && colCountersArr[i] == 1)
			curr->hits++;
}


char* getBestAverage(ParticipantList* lst)
{
	/* This function finds which of the participants has the highest average of 'hits' and returns his name.
	It uses the auxiliary function "getBestAverageHelper". */

	char* res;
	float bestAverage = 0.0;
	ParticipantListNode* curr = lst->head;
	getBestAverageHelper(curr, &res, &bestAverage);

	return res;
}


void getBestAverageHelper(ParticipantListNode* currParicipant, char** res, float* bestAverage)
{
	/* A recursive auxiliary function that goes through the lists,
	calculates the average 'hits' of each of the participants,
	and updates the input-output variables 'res' and 'bestAverage' according to the highest average. */

	float counter = 0, sum = 0, currAverage;
	List* lst = &currParicipant->data.colList;
	ListNode* currCol;

	if (currParicipant == NULL)
		return;

	currCol = lst->head;

	while (currCol != NULL)
	{
		sum += currCol->hits;
		counter++;
		currCol = currCol->next;
	}

	currAverage = sum / counter;

	if (currAverage > (*bestAverage))
	{
		*bestAverage = currAverage;
		*res = currParicipant->data.name;
	}

	return getBestAverageHelper(currParicipant->next, res, bestAverage);
}


void searchIinHits(List* lst, int i, int* counter)
{
	/* The shovel function looks for 'i' in the number of 'hits' of each column.
	If 'i' is equals to the current column's 'hits' we increase the input-output variable. */

	ListNode* curr = lst->head;
	int j;

	while (curr != NULL)
	{
		if (i == curr->hits)
			(*counter)++;
		curr = curr->next;
	}
}


void sortList(List* lst)
{
	/* This function sorts the column list of each participant in 'bubble sort'.
	The column with the highest number of hits will be first,
	and the column with the lowest number of hits will be last on the list. */

	ListNode* p1 = lst->head;
	ListNode* p2;
	int* colSaver, hitsSaver;

	if ((!p1) || !(p1->next))
		return;

	while (p1 != NULL)
	{
		p2 = p1->next;
		while (p2 != NULL)
		{
			if (p1->hits < p2->hits)
			{
				colSaver = p1->col;
				hitsSaver = p1->hits;
				p1->col = p2->col;
				p1->hits = p2->hits;
				p2->col = colSaver;
				p2->hits = hitsSaver;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}


void pressToContinue()
{
	/* This function asks the user to press 'ENTER' in order to continue. */

	char ch;

	printf("\nPress 'ENTER' to continue...");
	ch = getchar();
	getchar();
	ch = '\n';
	system("cls");
}


void saveToBinFile(ParticipantList* list, int numOfUsers, int* winnerCol)
{
	/* This function handle the binary file :
	it opens the file , then  writes into it by calling Helper function ,
	and then close the file. */

	char* fileName;
	FILE* file;
	ParticipantListNode* currParticipant = list->head;
	fileName = "lastLotteryData.bin";

	file = fopen(fileName, "wb");
	checkFileOpen(file, WRITE_FILE);

	saveToBinFileHelper(currParticipant, numOfUsers, winnerCol, file);

	fclose(file);

}


void saveToBinFileHelper(ParticipantListNode* currParticipant, int numOfUsers, int* winnerCol, FILE* file)
{
	/* This function write and save all the information of the participants in the lottery:
	 - The amount of users and their names.
	 - The columns of each user and the number.
	 - The winner column. */

	int numOfLetters;
	ListNode* currCol;

	fwrite(&numOfUsers, sizeof(int), 1, file);

	while (currParticipant != NULL)
	{
		currCol = currParticipant->data.colList.head;
		numOfLetters = strlen(currParticipant->data.name);
		fwrite(&numOfLetters, sizeof(int), 1, file);
		saveLetters(&currParticipant->data.name, numOfLetters, file);
		fwrite(&(currParticipant->data.numOfCols), sizeof(int), 1, file);

		while (currCol != NULL)
		{
			compressedCol(currCol->col, file);
			currCol = currCol->next;
		}
		currParticipant = currParticipant->next;
	}

	compressedWinnerCol(winnerCol, file);
}


void saveLetters(char* name, int numOfLetters, FILE* file)
{
	/* This function write the letters of a given user's name to the binary file. */

	int i;
	for (i = 0; i < numOfLetters; i++)
		fwrite(name + i, sizeof(char), 1, file);

}


void compressedCol(int* col, FILE* file)
{
	/* This function compress the winner column and write it to the binary file,
	by writing the values inside every two following indexs of the winner column
	to single byte  using mask. */

	BYTE mask;
	int  i;

	for (i = 0; i < COL_SIZE; i += 2)
	{
		mask = 0x00;
		mask = mask | col[i];
		mask = mask << 4;
		mask = mask | col[i + 1];
		fwrite(&mask, sizeof(char), 1, file);
	}
}


void compressedWinnerCol(int* winnerCol, FILE* file)
{
	/* This function compress the winner column and write it to the binary file ,
	by writing the values inside every two following indexs of the winner column
	to single byte  using mask. */

	BYTE mask;
	int  i;

	for (i = 0; i < COL_SIZE; i += 2)
	{
		mask = 0x00;
		mask = mask | winnerCol[i];
		mask = mask << 4;
		mask = mask | winnerCol[i + 1];
		fwrite(&mask, sizeof(char), 1, file);
	}

}


void choiseTwo()
{
	/* This function handles in a case the user choose the second option ,
	means that the function displays the results and the information  from the last lottery ,
	using binary file that holds all the information . */

	ParticipantList list;
	int* winnerCol, * winnerColCountersArr, numOfParticipants;
	char* binFileName = "lastLotteryData.bin";
	FILE* binFile;

	binFile = fopen(binFileName, "rb");
	checkFileOpen(binFile, READ_FILE);

	winnerCol = (int*)calloc(COL_SIZE, sizeof(int));
	checkMemoryAllocation(winnerCol);

	winnerColCountersArr = (int*)calloc(MAX_NUM_IN_COL, sizeof(int));
	checkMemoryAllocation(winnerColCountersArr);

	fread(&numOfParticipants, sizeof(int), 1, binFile);

	list = getParticipantListFromFile(numOfParticipants, binFile);

	getWinnerColFromFile(winnerCol, binFile);
	updateColCountersArr(winnerCol, winnerColCountersArr);
	updateHits(&list, winnerColCountersArr);

	printf("-----------------------------------------------------------\n");
	printf("THE RESULTS OF THE LAST LOTTERY:");
	printf("\n-----------------------------------------------------------\n\n");
	printAll(&list, winnerCol);

	pressToContinue2();

	fclose(binFile);
	free(winnerCol);
	free(winnerColCountersArr);
	freeParticipantList(&list);
}


ParticipantList getParticipantListFromFile(int numOfParticipants, FILE* binFile)
{
	/*	This function gets the participant list from the binary file. */

	int i, len;
	ParticipantList res;
	Participant userInfo;

	makeEmptyParticipantList(&res);

	for (i = 0; i < numOfParticipants; i++)
	{
		fread(&len, sizeof(int), 1, binFile);
		fread(userInfo.name, sizeof(char), len, binFile);
		userInfo.name[len] = '\0';
		fread(&userInfo.numOfCols, sizeof(int), 1, binFile);
		userInfo.colList = getListOfCols(binFile, userInfo.numOfCols);
		insertDataToEndParticipantList(&res, userInfo);
	}

	return res;
}


List getListOfCols(FILE* binFile, int numOfCols)
{
	/* This function creates a list of columns of a given user. */

	List res;
	int i;

	makeEmptyList(&res);

	for (i = 0; i < numOfCols; i++)
		getColsFromFile(binFile, &res);

	return res;
}


void getColsFromFile(FILE* binFile, List* res)
{
	/* This function gets the columns of each user from the binary file ,
	 using mask  , and two bytes that hold the values of each byte in the binary file. */

	int  i;
	BYTE mask;
	BYTE firstNum, secondNum;

	int* column = (int*)calloc(COL_SIZE, sizeof(int));
	checkMemoryAllocation(column);

	for (i = 0; i < COL_SIZE; i += 2)
	{
		firstNum = 0x00;
		secondNum = 0x0F;

		fread(&mask, sizeof(byte), 1, binFile);
		firstNum = firstNum | (mask >> 4);
		secondNum = secondNum & mask;

		column[i] = firstNum;
		column[i + 1] = secondNum;
	}

	insertDataToEndList(res, column);
}


void getWinnerColFromFile(int* winnerCol, FILE* binFile)
{
	/* This function gets the winner coloumn from the binary file ,
	* using mask  , and two bytes that hold the values of each byte in the binary file. */

	int  i, j;
	BYTE mask;
	BYTE firstNum, secondNum;

	for (i = 0; i < COL_SIZE; i += 2)
	{
		firstNum = 0x00;
		secondNum = 0x0F;

		fread(&mask, sizeof(byte), 1, binFile);
		firstNum = firstNum | (mask >> 4);
		secondNum = secondNum & mask;

		winnerCol[i] = firstNum;
		winnerCol[i + 1] = secondNum;
	}
}


void pressToContinue2()
{
	/* This function asks the user to press 'ENTER' in order to continue. */

	char ch;

	printf("\nPress 'ENTER' to continue...");
	ch = getchar();
	ch = '\n';
	system("cls");
}


/*-------------------- Checking allocations and file opening functions -----------------------*/

void checkMemoryAllocation(void* ptr)
{
	/*This function checks if the memmory allocation Succeeded. */

	if (!ptr)
	{
		printf("Allocation failure ! \n\n");
		exit(MEMORY_ALLOCATION_FAIL);
	}
}


void checkFileOpen(FILE* fp, int readOrWrite)
{
	/* This function checks if the openning of the file Succeeded.
	* if the openning failed , it deferencing between two cases :
	- if the user choose to write to file - means that there was an error opening the file
	- if the user choose to read from file  - means that the file was not created yet. */

	if (!fp)
	{
		if (readOrWrite == WRITE_FILE)
		{
			printf("Error opening file ! \n\n");
			exit(MEMORY_ALLOCATION_FAIL);
		}

		printf("\n\nNo lottery has been drawn yet! \n\n");
		gamePlay();
	}
}


/*----------------------------------- Printing functions -------------------------------------*/

void printMenu()
{
	/* A function that prints the main menu. */

	printf("\n***********************************************************\n\n");
	printf("Please choose one of the following options and enter it's number:\n\n");
	printf("1. Entering the number of participants in the lottery \n2. Viewing the latest lottery results \n3. Exit \n\n");
	printf("*************************************************************\n\n");
}


void printSubMenu()
{
	/* A function that prints the sub-menu. */

	printf("\n***********************************************************\n\n");
	printf("Please choose one of the following options and enter it's number:\n\n");
	printf("1. Manual lottery \n2. Automatic lottery \n\n");
	printf("*************************************************************\n\n");
}


void printAll(ParticipantList* lst, int* winnerCol)
{
	/* This function prints the results of the last lottery according to the format.
	It uses the auxiliary functions:
	"printWinnerCol", "sortList", "printParticipantList", "printColsForEachHit" and "getBestAverage". */

	ParticipantListNode* curr = lst->head;

	printWinnerCol(winnerCol);

	Sleep(1250);

	while (curr != NULL)
	{
		sortList(&curr->data.colList);
		curr = curr->next;
	}

	printParticipantList(lst);

	Sleep(1250);

	printColsForEachHit(lst);

	Sleep(1250);

	printf("\nThe participant with the best average is:  %s\n\n", getBestAverage(lst));
}


void printList(List* lst)
{
	/* This function prints to the screen all the columns of a given user ,
	including its number of hits according the the winner column. */

	ListNode* curr = lst->head;
	int i, colCount = 1;

	while (curr != NULL)
	{
		printf("Column number %d:  ", colCount);
		for (i = 0; i < COL_SIZE; i++)
			printf("%d  ", curr->col[i]);

		printf("Number of hits:  %d", curr->hits);

		printf("\n");

		curr = curr->next;
		colCount++;
	}
}


void printParticipantList(ParticipantList* lst)
{
	/*This function prints to the screen the entire participant list -
	the columns of each participant*/

	ParticipantListNode* curr = lst->head;



	while (curr != NULL)
	{
		printf("The columns of particpant %s are:  \n", curr->data.name);
		printList(&curr->data.colList);
		curr = curr->next;
		printf("\n");
	}

	printf("\n\n");
}


void printWinnerCol(int* winnerCol)
{
	/*This function print to the screen the winner column*/

	int i;

	printf("The winner column is:  ");
	for (i = 0; i < COL_SIZE; i++)
		printf("%d  ", winnerCol[i]);
	printf("\n\n\n");
}


void printColsForEachHit(ParticipantList* lst)
{
	/* This function prints a general summary of the number of columns with 6 'hits',
	the number of columns with 5 'hits' (does not include those with 6'hits'),
	the number of columns with 4 'hits' (not including those with 5,6 vulnerabilities), etc.
	It uses the auxiliary function "searchIinHits". */

	int i, counter;
	ParticipantListNode* curr;

	for (i = COL_SIZE; i >= 0; i--)
	{
		counter = 0;
		curr = lst->head;
		printf("The  number of columns with %d hits is:  ", i);
		while (curr != NULL)
		{
			searchIinHits(&curr->data.colList, i, &counter);
			curr = curr->next;
		}
		printf(" %d\n\n", counter);
	}
}


/*--------------------------------- Free memory functions ------------------------------------*/

void freeParticipantList(ParticipantList* lst)
{
	/*This function free all the allocated memmory of the participant list */

	ParticipantListNode* curr, * saver;
	curr = lst->head;

	while (curr != NULL)
	{
		saver = curr;
		curr = curr->next;
		lst->head = curr;
		freeList(&saver->data.colList);
		free(saver);
	}
}


void freeList(List* lst)
{
	/*This function free all the allocated memmory of the List ,
	and for each node in the list ,
	its free the allocated memmory of its column*/

	ListNode* curr, * saver;
	curr = lst->head;
}