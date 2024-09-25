#include <stdio.h>
#include <stdlib.h>


char* next1(char *npm1){
    int i=0;

    npm1 = malloc(11);
    if(!npm1)
      return (NULL);

    while(i != 10){
      npm1[i] = 'a' + i;
      i++;
    }
    npm1[i] = '\0';

    printf("npm1 : %s\n", npm1);
    printf("npm1 address : %p\n\n", (void *)npm1);

    return(npm1);
}

char* next2(char *npm2){
    int i=0;

    while(i != 10){
      npm2[i] = 'A' + i;
      i++;
    }
    npm2[i] = '\0';

    printf("npm2 : %s\n", npm2);
    printf("npm2 address : %p\n\n", (void *)npm2);

    return(npm2);
}

int main(void)
{
    int num;
    char text;
    int *pnum;
    char *ptext;
    char *pm1;
    int i;


    num = 1;
    text = 'a';

    pnum = &num;
    ptext = &text;

    *pnum = 2;
    *ptext = 'b';

    printf("num: %d\n", num);
    printf("num address: %p\n\n", (void *)&num);

    printf("text: %c\n", text);
    printf("text address: %p\n\n", (void *)&text);

    printf("pnum : %d\n", *pnum);
    printf("pnum address : %p\n\n", (void *)pnum);

    printf("ptext : %c\n", *ptext);
    printf("ptext address : %p\n\n", (void *)ptext);

    i=0;
    pm1 = malloc(11 * sizeof(char));
    if (!pm1)
		return (NULL);

    while(i != 10){
      pm1[i] = '0' + i;
      i++;
    }
    pm1[i] = '\0';

    printf("pm1 : %s\n", pm1);
    printf("pm1 address : %p\n\n", (void *)pm1);

    ptext = pm1;

    printf("ptext <- pm1 : %s\n", ptext);
    printf("ptext <- pm1 address : %p\n\n", (void *)ptext);

    free(pm1);

    char *npm1 = next1(NULL);

    printf("next1 returned : %s\n", npm1);
    printf("next1 returned address : %p\n\n", (void *)npm1);
    free(npm1);

    char *npm2;

    npm2 = malloc(11);
    if(!npm2){
      free(npm2);
      return(NULL);
    }
    next2(npm2);
    printf("next2 returned : %s\n", npm2);
    printf("next2 returned address : %p\n\n", (void *)npm2);
    free(npm2);


    return (0);
}

// *ptext, *pm1, 