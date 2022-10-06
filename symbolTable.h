//Symbol table header
#include <string.h>

// This is a very simplistic implementation of a symbol table
// You will use this as reference and build a much more robust one

struct Entry
{
	int itemID;
	char itemName[50];  //the name of the identifier
	char itemKind[8];  //is it a function or a variable?
	char itemType[8];  // Is it int, char, etc.?
	int arrayLength;
	char scope[50];     // global, or the name of the function
	char value[50];
};

struct Entry symTabItems[100];
int symTabIndex = 1;

void symTabAccess(void){
	printf("::::> Symbol table accessed.\n");
}

void addItem(char itemName[50], char itemKind[8], char itemType[8], int arrayLength, char scope[50]){
	// what about scope? should you add scope to this function?
		symTabItems[symTabIndex].itemID = symTabIndex;
		strcpy(symTabItems[symTabIndex].itemName, itemName);
		strcpy(symTabItems[symTabIndex].itemKind, itemKind);
		strcpy(symTabItems[symTabIndex].itemType, itemType);
		symTabItems[symTabIndex].arrayLength = arrayLength;
		strcpy(symTabItems[symTabIndex].scope, scope);
		symTabIndex++;
	
}

void showSymTable(){
	printf("itemID    itemName    itemKind    itemType     Value    itemSCope\n");
	printf("-----------------------------------------------------------------------\n");
	for (int i=1; i<symTabIndex; i++){
		printf("%5d %15s  %7s  %7s %6s %15s \n",symTabItems[i].itemID, symTabItems[i].itemName, symTabItems[i].itemKind, symTabItems[i].itemType, symTabItems[i].value, symTabItems[i].scope);
	}
	

	printf("-----------------------------------------------------------------------\n");
}

int found(char itemName[50], char scope[50]){
	// Lookup an identifier in the symbol table
	// what about scope?
	// return TRUE or FALSE
	// Later on, you may want to return additional information
	for(int i=1; i<100; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);
		if( str1 == 0 && str2 == 0){
			return i; // found the ID in the table
		}
	}
	return 0;
}

//compare two different types to make sure they are right. 
int compareTypes(int itemIndex1, int itemIndex2) {
	int check = strcmp(symTabItems[itemIndex1].itemType, symTabItems[itemIndex2].itemType);

	if (check == 0) {
		return 1;
	}

	return 0;
}

//update the value to the symbol table
void updateValue(char itemName[50], char scope[50], char value[50]) {
	for(int i = 1; i<symTabIndex; i++) {
		if (strcmp(symTabItems[i].itemName, itemName) && strcmp(symTabItems[i].scope, scope) == 0) {
			strcpy(symTabItems[i].value, value);
		}
	}
}

//returns the value that we put into the symbol table
char *getValue(char itemName[50], char scope[50]) {
	for (int i = 1; i<symTabIndex; i++) {
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);

		if(str1 && str2 == 0) {
			return symTabItems[i].value;
		}
	}

	return NULL;
}

//returns what the type of the variable is
char *getVariableType(char itemName[50], char scope[50]) {
		for (int i = 1; i<symTabIndex; i++) {
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);

		if(str1 && str2 == 0) {
			return symTabItems[i].itemType;
		}
	}

	return NULL;
} 