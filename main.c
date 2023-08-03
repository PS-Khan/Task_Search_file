#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include "file_search_lib.h"

#define MAX_THREADS 8 

typedef struct {
    char* subdir;
} ThreadArgs;

void* search_thread(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;
    char root_path[1024];
    snprintf(root_path, sizeof(root_path), "D:/proj/%s", thread_args->subdir);
    search_file(root_path, "test.txt");
    free(thread_args->subdir); 
    return NULL;
}

int main() {
    DIR* root_dir;
    struct dirent* entry;
    int num_subdirs = 0;
    char** subdirs = NULL;

    // Open the root directory ("\" or "C:\")
    root_dir = opendir("C:/"); 
    if (root_dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Allocate memory to store subdirectory names
    subdirs = (char**)malloc(MAX_THREADS * sizeof(char*));
    if (subdirs == NULL) {
        perror("malloc");
        closedir(root_dir);
        return 1;
    }

    // Read the contents of the root directory
    while ((entry = readdir(root_dir)) != NULL) {
        if (num_subdirs >= MAX_THREADS) {
            break; 
        }

        // Check if the entry is a directory (ignore "." and "..")
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            subdirs[num_subdirs] = strdup(entry->d_name); // Copy the subdirectory name
            if (subdirs[num_subdirs] == NULL) {
                perror("strdup");
                closedir(root_dir);
                return 1;
            }
            num_subdirs++;
        }
    }


    closedir(root_dir);

    // Create a thread for each subdirectory
    pthread_t threads[MAX_THREADS];
    ThreadArgs thread_args[MAX_THREADS]; // Separate thread_args for each thread

    for (int i = 0; i < num_subdirs; i++) {
        thread_args[i].subdir = subdirs[i];
        pthread_create(&threads[i], NULL, search_thread, (void*)&thread_args[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_subdirs; i++) {
        pthread_join(threads[i], NULL);
    }

    free(subdirs);

    system("pause");
    return 0;
}