//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdbool.h>
//#include <ctype.h>

///**
// * Auto-generated code below aims at helping you parse
// * the standard input according to the problem statement.
// **/

//int main()
//{
//    char s[503];
//    scanf("%[^\n]", s);
//    int k = 0;
//	char c;
//    for (int i = 0; i < strlen(s); i++)
//    {
//        c = tolower(s[i]);
//        if (k % 2 == 1 && isspace(s[i]) != 0)
//        {
//            c = toupper(s[i]);
//            printf ("%c", c);
//            k++;
//        }
//        else if (isspace(s[i]) != 0)
//        {
//            printf ("%c", c);
//            k++;
//        }
//       // else 
//           // printf ("%c", c);
//    }
//    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
//    // To debug: fprintf(stderr, "Debug messages...\n");

//   // printf("sarcasm\n");

//    return 0;
//}
//#include <stdio.h>
//#include <pthread.h>

//#define NUM_THREADS 5

//void* task(void* arg) {
//    int id = *(int*)arg;
//    //printf("Thread %d is running\n", id);
//    return NULL;
//}

//int main() {
//    pthread_t threads[NUM_THREADS];
//    int thread_ids[NUM_THREADS];

//    for (int i = 0; i < NUM_THREADS; i++) {
//        thread_ids[i] = i;
//        printf("%p\n", &thread_ids[i]);
//        if (pthread_create(&threads[i], NULL, task, &i) != 0) {
//            perror("pthread_create failed");
//        }
//    }

//    for (int i = 0; i < NUM_THREADS; i++) {
//        pthread_join(threads[i], NULL);
//    }

//    return 0;
//}
