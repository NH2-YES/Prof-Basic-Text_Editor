#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1000
#define LINES 2000

void Create_New_File();
void Open_File();
void Edit_File();
void Save_File();
void Display_File_Content();
void Delete_File();
void Append_File();
void Search_Word();
void Replace_Word();
void Count_Words();
void Exit_Editor();

int main() {
    int choice;
    char name[50];

    printf("Enter your name, please: ");
    scanf("%s", name);

    while (1) {
        printf("\nAsalamoualeykum, %s! Please choose an option:\n", name);
        printf("1. Create New File\n");
        printf("2. Open File\n");
        printf("3. Edit File\n");
        printf("4. Save File\n");
        printf("5. Display File Content\n");
        printf("6. Delete File\n");
        printf("7. Append to File\n");
        printf("8. Search Word in File\n");
        printf("9. Replace Word in File\n");
        printf("10. Count Words in File\n");
        printf("11. Exit Editor\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                Create_New_File();
                break;
            case 2:
                Open_File();
                break;
            case 3:
                Edit_File();
                break;
            case 4:
                Save_File();
                break;
            case 5:
                Display_File_Content();
                break;
            case 6:
                Delete_File();
                break;
            case 7:
                Append_File();
                break;
            case 8:
                Search_Word();
                break;
            case 9:
                Replace_Word();
                break;
            case 10:
                Count_Words();
                break;
            case 11:
                Exit_Editor();
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void Create_New_File() {
    char filename[100];
    FILE *fp;

    printf("Enter the name of the new file: ");
    scanf("%s", filename);

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error creating file.\n");
        return;
    }

    printf("File created successfully.\n");
    fclose(fp);
}

void Open_File() {
    char filename[100];
    FILE *fp;
    char ch;

    printf("Enter the name of the file to open: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("File opened successfully.\n");
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
}

void Edit_File() {
    char filename[100];
    FILE *fp;
    char content[LENGTH];

    printf("Enter the name of the file to edit: ");
    scanf("%s", filename);

    fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter the content to append (end with a single dot on a new line):\n");
    while (1) {
        fgets(content, LENGTH, stdin);
        if (strcmp(content, ".\n") == 0) {
            break;
        }
        fputs(content, fp);
    }

    printf("File edited successfully.\n");
    fclose(fp);
}

void Save_File() {
    char filename[100];
    FILE *fp;
    char content[LENGTH];

    printf("Enter the name of the file to save: ");
    scanf("%s", filename);

    if((fp=fopen(filename, "a"))==NULL){
      printf("Cannot open file %s", filename);
      exit(1);
    }

    printf("Enter the text to be added to the file: ");
    fgets(content, LENGTH, stdin);
    content[strcspn(content, "\n")]='\0';

    fputs(content,fp);
    fclose(fp);
    
}

void Display_File_Content() {
    char filename[100];
    FILE *fp;
    char ch;

    printf("Enter the name of the file to display: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("File content:\n");
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
}

void Delete_File() {
    char filename[100];

    printf("Enter the name of the file to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Error deleting file.\n");
    }
}

void Append_File() {
    char filename[100];
    FILE *fp;
    char content[LENGTH];

    printf("Enter the name of the file to append to: ");
    scanf("%s", filename);

    fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter the content to append (end with a single dot on a new line):\n");
    while (1) {
        fgets(content, LENGTH, stdin);
        if (strcmp(content, ".\n") == 0) {
            break;
        }
        fputs(content, fp);
    }

    printf("Content appended successfully.\n");
    fclose(fp);
}

void Search_Word() {
    char filename[100];
    FILE *fp;
    char word[50];
    char line[LENGTH];
    int line_number = 0;
    int found = 0;

    printf("Enter the name of the file to search in: ");
    scanf("%s", filename);

    printf("Enter the word to search for: ");
    scanf("%s", word);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, LENGTH, fp) != NULL) {
        line_number++;
        if (strstr(line, word) != NULL) {
            printf("Word found at line %d: %s", line_number, line);
            found = 1;
        }
    }

    if (!found) {
        printf("Word not found in the file.\n");
    }

    fclose(fp);
}

void Replace_Word() {
    char filename[100];
    FILE *fp, *temp_fp;
    char word[50], replacement[50];
    char line[LENGTH];
    int line_number = 0;
    int found = 0;

    printf("Enter the name of the file to search in: ");
    scanf("%s", filename);

    printf("Enter the word to replace: ");
    scanf("%s", word);

    printf("Enter the replacement word: ");
    scanf("%s", replacement);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    while (fgets(line, LENGTH, fp) != NULL) {
        line_number++;
        if (strstr(line, word) != NULL) {
            found = 1;
            char *pos = strstr(line, word);
            while (pos != NULL) {
                int len = pos - line;
                line[len] = '\0';
                strcat(line, replacement);
                strcat(line, pos + strlen(word));
                pos = strstr(line, word);
            }
        }
        fputs(line, temp_fp);
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(filename);
        rename("temp.txt", filename);
        printf("Word replaced successfully.\n");
    } else {
        remove("temp.txt");
        printf("Word not found in the file.\n");
    }
}

void Count_Words() {
    char filename[100];
    FILE *fp;
    char word[50];
    int count = 0;

    printf("Enter the name of the file to count words in: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    while (fscanf(fp, "%s", word) != EOF) {
        count++;
    }

    printf("Total words in the file: %d\n", count);
    fclose(fp);
}

void Exit_Editor() {
    printf("Exiting the editor. Goodbye!\n");
    exit(1);
}