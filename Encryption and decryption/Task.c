#include"Task.h"

/***********************************************************************************/
char msg[101]; // Increase size by 1 for null terminator
char key;
int operation;

/***********************************************************************************/
void encryption_English_letters(char *msg, char key) {
    char ch;
    for(int i = 0; msg[i] != '\0'; ++i){
        ch = msg[i];
        if(isalpha(ch)){ // Check if it's an English letter
            if(islower(ch)){ // Check if it's a lowercase letter
                ch = 'a' + (ch - 'a' + key) % 26;
            }
            else if(isupper(ch)){ // Check if it's an uppercase letter
                ch = 'A' + (ch - 'A' + key) % 26;
            }
            msg[i] = ch;
        }
    }
}
/***********************************************************************************/
void decryption_English_letters(char *msg, char key) {
    encryption_English_letters(msg, 26 - (key % 26));
}
/***********************************************************************************/
 void Remove_lines(char *msg){
    size_t len = strlen(msg);
    if (len > 0 && msg[len - 1] == '\n') {
        msg[len - 1] = '\0';
    }
}
/***********************************************************************************/
void Main_Task(){
      printf("1- Encryption 2-Decryption, Please choose the operation: ");
    scanf("%d", &operation);
    getchar();

    if (operation == 1) {
        printf("Enter the key: ");
        scanf("%d", &key);
        getchar();

        printf("Enter a message to encrypt: ");
        scanf("%[^\n]", msg);
        getchar();

        encryption_English_letters(msg, key);
        printf("Encrypted message: %s\n", msg);

    } else if (operation == 2) {
        printf("Enter the key: ");
        scanf("%d", &key);
        getchar();

        printf("Enter a message to decrypt: ");
        scanf("%[^\n]", msg);
        getchar();

        decryption_English_letters(msg, key);
        printf("Decrypted message: %s\n", msg);
    } else {
        printf("Invalid choice.\n");
    }
}
