#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <sys/stat.h>
#include <time.h>

BOOL deleteDirectory(const char* path) {
    return RemoveDirectoryA(path);
}

BOOL isFileEncrypted(const char* path) {
    DWORD attributes = GetFileAttributesA(path);
    return (attributes != INVALID_FILE_ATTRIBUTES) && (attributes & FILE_ATTRIBUTE_ENCRYPTED);
}

char* getLastModifiedTime(const char* path) {
    struct stat result;
    if (stat(path, &result) == 0) {
        time_t mod_time = result.st_mtime;
        struct tm* timeinfo = localtime(&mod_time);
        static char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
        return buffer;
    }
    return NULL;
}

int main() {
    const char* fileName = "C:\\3 course 2 sem\\SPZ\\L4\\file-to-change.txt";
    const char* directoryPath = "C:\\3 course 2 sem\\SPZ\\L4\\directory-to-remove";
    int choice;
    char* lastModified = NULL;

    while (1) {
        printf("\n1. Delete Directory\n");
        printf("2. Check if File is Encrypted\n");
        printf("3. Get Last Modified Time of File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (deleteDirectory(directoryPath)) {
                printf("Directory deleted successfully.\n");
            }
            else {
                printf("Failed to delete directory.\n");
            }
            break;
        case 2:
            if (isFileEncrypted(fileName)) {
                printf("The file is encrypted.\n");
            }
            else {
                printf("The file is not encrypted.\n");
            }
            break;
        case 3:
            lastModified = getLastModifiedTime(fileName); 
            if (lastModified != NULL) {
                printf("Last modified time: %s\n", lastModified);
            }
            else {
                printf("Failed to get last modified time.\n");
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
