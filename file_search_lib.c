#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int file_found = 0;
void search_file(const char* root_dir, const char* filename) {
    DIR* dir;
    struct dirent* entry;
    struct stat statbuf;
    char path[1024];

    dir = opendir(root_dir);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    // Traverse through the directories and subdirectories
    while ((entry = readdir(dir)) != NULL) {
        if (file_found) {
            break; 
        }
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", root_dir, entry->d_name);

        // Get file status to check if the entry is a directory
        if (stat(path, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        // Check if the entry is a directory
        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(entry->d_name, "/") == 0 || strcmp(entry->d_name, "C:") == 0) {
                continue;
            }

            search_file(path, filename);
        } else {
            if (strcmp(entry->d_name, filename) == 0) {
                printf("Found file: %s/%s\n", root_dir, entry->d_name);
                file_found = 1;
                break;
            }
        }
    }

    closedir(dir);
}

