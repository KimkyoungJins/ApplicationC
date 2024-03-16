// Enter your student ID and Fullname

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct st_class{
	int code;		// class code
	char name[30]; 	// class name
	int unit;		// credites
	int grading;	// grading (1:A+~F, 2:P/F)
};

char kname[2][10] = {"A+~F", "P/F"}; // String for grading

// Functions provided
int loadData(struct st_class* c[]); // Load all class list from data file.
void printAllClasses(struct st_class* c[], int csize); // Print all class list

// Functions for modifying
int addNewClass(struct st_class* c[], int csize); // Add a class into the list
void editClass(struct st_class* c[], int csize); // Modify a class in the list
void findClasses(char* name, struct st_class* c[], int csize); // Search a class by name from the list

// Functions for making
int applyMyClasses(int my[], int msize, struct st_class* c[], int csize); // Apply a class
void printMyClasses(int my[], int msize, struct st_class* c[], int csize); // Print my classes
void saveMyClass(int my[], int msize, struct st_class* c[], int csize); // Save my classes
void saveAllClasses(struct st_class* c[], int csize); // Save all class list


int main(void) {
	int no;	// menu number 
	struct st_class* classes[50]; // Class list (max. 50 classes)

	int myclass[10]; // My classes (max. 10 classes of code)
	int mycount = 0; // Amount of my classes

	srand(time(0));
	int count = loadData(classes);
	printf("> Load %d classes.\n", count);

	while(1){
		printf("\n> Menu 1.List 2.Add 3.Modify 4.Search 5.Apply 6.My classes 7.Save 0.Quit\n");
		printf(">> Menu? > ");
		scanf("%d", &no);

		if(no == 1){ 
			printf("> 1.Class list (%d classes)\n", count);
			printAllClasses(classes, count);
		}
		else if(no == 2){ 
			printf("> 2.Add a Class\n");
			count = addNewClass(classes, count);
		}
		else if(no == 3){ 
			printf("> 3.Modify a Class\n");
			editClass(classes, count);
		}
		else if(no == 4){
			printf("> 4.Search a Class\n");
			printf(">> Enter class name > ");
			char name[30];
			scanf("%s", name);
			findClasses(name, classes, count);
		}
		else if(no == 5){
			printf("> 5.Apply a class\n");
			mycount = applyMyClasses(myclass, mycount, classes, count);
			printf("%d classes has been applied.\n", mycount);
		}
		else if(no == 6){
			printf("> 6.My classes\n");
			printMyClasses(myclass, mycount, classes, count);
		}
		else if(no == 7){
			printf("> 7.Save\n");
			saveMyClass(myclass, mycount, classes, count);
			printf("\n> All my classes ware saved to my_classes.txt.\n");
			saveAllClasses(classes, count);
			printf("\n> All of class list ware saved to classes.txt.\n");
		}
		else break;
	}
	return 0;
}

int loadData(struct st_class* c[]){
	int count=0;
	FILE* file;
	
	file=fopen("classes.txt", "r");
	while(!feof(file)){
		c[count] = (struct st_class*)malloc(sizeof(struct st_class));
		int r = fscanf(file, "%d %s %d %d", &(c[count]->code),c[count]->name, &(c[count]->unit), &(c[count]->grading));
		if(r < 4) break;
		count++;
	}
	fclose(file);
	return count;
}

void printAllClasses(struct st_class* c[], int csize){
	for(int i=0; i<csize; i++){
		printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
	}
}

void saveAllClasses(struct st_class* c[], int csize){
	FILE* file;
	file = fopen("classes.txt", "w");
	for(int i=0; i<csize; i++){
		fprintf(file, "%d %s %d %d\n",c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
	}
	fclose(file);	
}

void findClasses(char* name, struct st_class* c[], int csize){
	int count = 0;

	printf("Searching (keyword : %s)\n", name);
	for(int i=0; i<csize; i++){
		if(strstr(c[i]->name, name)){
			printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
			count++;
		}
	}
	printf("%d classes found.\n", count);
}


// You must complete these functions.
int addNewClass(struct st_class* c[], int csize) {

// Caution : Don't allow the duplicate class code.
// You must complete this function.

  /*
  
  강의 정보를 사용자로부터 입력받는다.
	입력받은 강의 코드가 이미 배열 내에 존재하는지 검사한다.
	만약 없다면, 새로운 struct st_class 인스턴스를 생성하고 입력받은 정보로 초기화한 뒤, c 배열에 추가합니다.
	강의 수 csize를 1 증가시키고 반환한다. 
  
  */

    int code;
    printf(">> code number > ");
    scanf("%d", &code);

    // Check if the code is already used
    for (int i = 0; i < csize; i++) {
        if (c[i]->code == code) {
            printf("This code is already used.\n");
            return csize;
        }
    }

    struct st_class* p = (struct st_class*)malloc(sizeof(struct st_class));
    p->code = code;
    printf(">> class name > ");
    scanf("%s", p->name);
    printf(">> credits > ");
    scanf("%d", &(p->unit));
    printf(">> grading (1: A+~F, 2: P/F) > ");
    scanf("%d", &(p->grading));

    c[csize] = p;
    return csize + 1;
}

void editClass(struct st_class* c[], int csize) {
    /*
수정할 강의의 코드를 사용자로부터 입력받음.
입력받은 코드와 일치하는 강의를 c 배열에서 찾는다.
일치하는 강의를 찾으면, 사용자로부터 새로운 강의 정보를 입력받아 기존 정보 업데이트.
코드와 일치하는 강의를 찾지 못하면, 해당되는 강의가 없다는 메시지를 출력함.
    
    */
    
    int code, found = 0;
    printf(">> Enter a code of class > ");
    scanf("%d", &code);
    
    
	// You must complete this section.
    for (int i = 0; i < csize; i++) {
        if (c[i]->code == code) {
            found = 1;
            printf("> Current: [%d] %s [credits %d - %s]\n", c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading - 1]);
            printf("> Enter new class name > ");
            scanf("%s", c[i]->name);
            printf("> Enter new credits > ");
            scanf("%d", &(c[i]->unit));
            printf("> Enter new grading(1:Grade, 2: P/F) > ");
            scanf("%d", &(c[i]->grading));

            printf("> Modified.\n");
            break;
        }
    }

    if (!found) {
        printf("Class code not found.\n");
    }
}

int applyMyClasses(int my[], int msize, struct st_class* c[], int csize) {
   
   
    /*
    
  사용자로부터 신청할 강의 코드를 입력받는다.
	입력받은 강의 코드가 my 배열 내에 이미 존재하는지 검사한다.
	c 배열에서 해당 강의 코드를 찾아 신청 가능한지 확인한다.
	모든 조건이 충족되면, my 배열에 강의 코드를 추가한다.
	msize를 1 증가시키고, 현재까지 신청한 강의 수를 반환한다.
	
    */
    
    int code, applyMore = 1;
    while (applyMore && msize < 10) {
        printf("Enter class code to apply (0 to finish): ");
        scanf("%d", &code);
        if (code == 0) break;

        // Check if the code is already in my classes
        int alreadyApplied = 0;
        for (int i = 0; i < msize; i++) {
            if (my[i] == code) {
                alreadyApplied = 1;
                printf("You have already applied for this class.\n");
                break;
            }
        }

        if (!alreadyApplied) {
            // Check if the code exists in the class list
            int exists = 0;
            for (int i = 0; i < csize; i++) {
                if (c[i]->code == code) {
                    exists = 1;
                    my[msize++] = code;
                    printf("Applied successfully.\n");
                    break;
                }
            }
            if (!exists) {
                printf("Class code does not exist.\n");
            }
        }

        printf("Apply more? (1: Yes, 0: No): ");
        scanf("%d", &applyMore);
    }
    return msize;
}



void printMyClasses(int my[], int msize, struct st_class* c[], int csize) {
    /*
    
	 msize만큼 반복한다.
	 my 배열에 저장된 각 강의 코드에 해당하는 
	 강의 정보를 c 배열에서 찾아 출력한다.
    
    */
    
    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < csize; j++) {
            if (c[j]->code == my[i]) {
                printf("[%d] %s [credit %d - %s]\n", c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading - 1]);
                break;
            }
        }
    }
}



void saveMyClass(int my[], int msize, struct st_class* c[], int csize) {
   
   /*
   
        (my_classes.txt)을 쓰기 모드로 연다.
		msize만큼 반복하면서, my 배열에 저장된 강의 코드에 해당하는 강의 정보를 파일에 쓴다.
		파일을 닫는다. 
		
		*/
   
    FILE* file = fopen("my_classes.txt", "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < csize; j++) {
            if (c[j]->code == my[i]) {
                fprintf(file, "[%d] %s [credit %d - %s]\n", c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading - 1]);
                break;
            }
        }
    }

    fclose(file);
    printf("My classes have been saved to my_classes.txt\n");
}
