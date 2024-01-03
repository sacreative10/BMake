#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int getNumOfCFiles(char *path) {
  FILE *fp;
  char num[100];
  char cmd[200];
  snprintf(cmd, 200, "ls %s -1 | grep .c | wc -l", path);
  fp = popen(cmd, "r");

  if (fp == NULL) {
    printf("Failed to run command\n");
    exit(1);
  }

  fgets(num, 100, fp);
  pclose(fp);

  return atoi(num);
}

void createObjFolder(char *path) {
  DIR *dir = opendir(path);
  if (dir) {
    closedir(dir);
  } else if (ENOENT == errno) {
    mkdir(path, 0777);
  } else {
    printf("Failed to create obj folder\n");
    exit(1);
  }
}

void getSourceFileNames(char *path, char fileNames[][200]) {
  FILE *fp;
  char cmd[200];
  snprintf(cmd, 200, "ls %s -1 | grep .c", path);
  fp = popen(cmd, "r");

  if (fp == NULL) {
    printf("Failed to run command\n");
    exit(1);
  }

  int i = 0;
  char fileName[1024];
  while (fgets(fileName, 1024, fp) != NULL) {
    // add to array
    strcpy(fileNames[i], fileName);
    i++;
  }
  pclose(fp);
}

int main(int argc, char *argv[]) {
  char *pathToProject = "./exampleProject";
  char *pathToObjs = "./exampleObjs";

  int numOfSourceFiles = getNumOfCFiles(pathToProject);
  createObjFolder(pathToObjs);

  printf("Number of source files: %d\n", numOfSourceFiles);

  char sourceFileNames[numOfSourceFiles][200];

  getSourceFileNames(pathToProject, sourceFileNames);

  for (int i = 0; i <= numOfSourceFiles - 1; i++) {
    sourceFileNames[i][strlen(sourceFileNames[i]) - 1] = 0;
    char cmd[200];
    snprintf(cmd, 200, "g++ -c %s/%s -o %s/%s.o\n", pathToProject,
             sourceFileNames[i], pathToObjs, sourceFileNames[i]);
    printf("%s", cmd);
    popen(cmd, "r");
    if (errno != 0) {
      printf("Failed to compile %s\n", sourceFileNames[i]);
      exit(1);
    }
  }

  // link the file
  char cmd[200];
  snprintf(cmd, 200, "g++ %s/*.o -o %s/main\n", pathToObjs, pathToObjs);
  printf("%s", cmd);
  if (popen(cmd, "r") == NULL) {
    printf("Failed to link\n");
    exit(1);
  }

  return 0;
}
