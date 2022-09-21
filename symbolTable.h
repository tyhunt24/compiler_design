// todo Attributes: ID, Add Item, Kind (function or variable), Type (int, char, etc)
struct Entry {
    int itemID;
    char itemName[50];
    char itemKind[8];
    int arrayLength;
    char scope[50];
}

struct entry tableItems[100];
int tableIndex = 0;

// todo Function to add Items to a list
void addItem(char itemName[50], char itemKind[8], int arrayLength, char scope[50]) {}

// todo - Function to and see if the item is found
void found(char itemName[50], char scope[50]) {}

// todo - Print out our symbol table to the screen
void print() {}

// ? What is the scope? is it (Global or Local)
// ? How much of your program can I borrow? 
// ? Should we implement this using a linked list instead? How do you want us to go about this?
