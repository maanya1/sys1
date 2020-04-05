
#ifndef RECURSIVE_H
#define RECURSIVE_H

void listFilesRecursive(char *basePath, void (*some_function)(char*, void*), void* data);

#endif