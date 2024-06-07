#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

int deleteDirectory(const char* path) {
    return rmdir(path);
}

int isFileHidden(const char* path) {
    struct stat sb;
    if (lstat(path, &sb) == -1) {
        return -1;
    }
    return (S_ISVTX & sb.st_mode) ? 1 : 0;
}

char* getCreationTime(const char* path) {
    struct stat sb;
    if (stat(path, &sb) == -1) {
        return NULL;
    }
    time_t creation_time = sb.st_ctime;
    return ctime(&creation_time);
}

int main() {
    const char* fileName = "/home/user/.hiddenfile";
    const char* directoryToDeletePath = "/home/user/directory-to-delete";
    const char* homeDirectory = "/home";
    int choice;
    char* creationTime = NULL;

    while (1) {
        printf("\n1. Delete Directory\n");
        printf("2. Check if File is Hidden\n");
        printf("3. Get Creation Time of Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (deleteDirectory(directoryToDeletePath) == 0) {
                printf("Directory deleted successfully.\n");
            }
            else {
                printf("Failed to delete directory.\n");
            }
            break;
        case 2:
            if (isFileHidden(fileName) == 1) {
                printf("The file is hidden.\n");
            }
            else if (isFileHidden(fileName) == 0) {
                printf("The file is not hidden.\n");
            }
            else {
                printf("Failed to check file hidden status.\n");
            }
            break;
        case 3:
            creationTime = getCreationTime(homeDirectory); 
            if (creationTime != NULL) {
                printf("Creation time: %s", creationTime);
            }
            else {
                printf("Failed to get creation time.\n");
            }
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
    return 0;
}
