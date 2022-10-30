struct entry
{
	int itemID;
	char itemName[50];  //the name of the identifier
	char itemKind[8];  //is it a function or a variable?
	char itemType[8];  // Is it int, char, etc.?
	int arrayLength;
	char scope[50];     // global, or the name of the function
	char value[50];
    int Nparams;
    
    // Only allow the user to store 5 parameters

    struct entry *next;

};

//linked list of tables

// Store an array of parameters

int tabIndex = 1;

struct entry * head;

void insert(char *itemName, char *itemKind, char *itemType, char *scope) {
    struct entry * list = (struct entry*) malloc(sizeof(struct entry));

    list->itemID = tabIndex;
    strcpy(list->itemName, itemName);
    strcpy(list->itemKind, itemKind);
    strcpy(list->itemType, itemType);
    strcpy(list->scope, scope);

    list->next = head;
    head = list;

    tabIndex++;
}

void updateVal(char itemName[50], char scope[50], char value[50]) {
    struct entry * list = head;

    while(list->next != NULL) {
        if(strcmp(list->itemName, itemName) == 0 && strcmp(list->scope, scope) == 0) {
            strcpy(list->value, value);
        } 
        list = list->next;
    }
}

char *getVal(char itemName[50], char scope[50]) {
    struct entry *list = head;

    while(list != NULL) {
        int str1 = strcmp(list->itemName, itemName);
        int str2 = strcmp(list->scope, scope);

        if(str1 == 0 && str2 == 0) {
            return list->value;
        } 
        list = list->next;

       
    }

    return NULL; 
}

//Finds the function in the Symbol Table
int find(char itemName[50], char scope[50]) {
    struct entry *list = head;

    while(list != NULL) {
        int str1 = strcmp(list->itemName, itemName);
        int str2 = strcmp(list->scope, scope);

        if(str1 == 0 && str2 == 0) {
            return 1;
        } else {
            list = list->next; 
        }
    }

    return 0; 
}

// Finds the index of The ID
int itemIndex(char itemName[50], char scope[50]) {
    struct entry *list = head;
    while(list != NULL) {
        int str1 = strcmp(list->itemName, itemName);
        int str2 = strcmp(list->scope, scope);

        if(str1 == 0 && str2 == 0) {
            return list->itemID;
        } else {
            list = list->next; 
        }

    }
}


// Gets what the variable type is
char *getVarType(char itemName[50], char scope[50]) {
    struct entry *list = head;

    while(list != NULL) {
        int str1 = strcmp(list->itemName, itemName);
        int str2 = strcmp(list->scope, scope);

        if(str1 == 0 && str2 == 0) {
            return list->itemType;
        }
    }

    return NULL;
}


void printList() {
    struct entry * ptr = head;

    	printf("ItemId  ItemName   itemKind    itemType   itemScope  Value\n");
	printf("-----------------------------------------------------------------------\n");
    while(ptr != NULL) {
//shows the symbol table

		printf("%5d %7s  %7s  %7s %15s %10s \n",ptr->itemID, ptr->itemName, ptr->itemKind, ptr->itemType, ptr->scope, ptr->value);

        ptr = ptr->next;
	}
	printf("-----------------------------------------------------------------------\n");
}


