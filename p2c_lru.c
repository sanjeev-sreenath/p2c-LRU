#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int no_of_frames, no_of_pages, pages[100];

int p2clru();
int lru();

int main()
{
    srand(time(0));
    int faults = 0, i, limit_random;
    clock_t start, end;
    double cpu_time_used;

    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);
    //no_of_frames = 5;

    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);
    //no_of_pages = 100;

    printf("Enter limit to random numbers generator for populating page data: ");
    scanf("%d", &limit_random);
    for(i = 0; i < no_of_pages; ++i){
        //scanf("%d", &pages[i]);
        pages[i] = rand()%limit_random;
    }

    printf("---LRU---");
    start = clock();
    faults = lru();
    end = clock();
    cpu_time_used = (((double) (end - start)) / CLOCKS_PER_SEC)*1000;
    printf("\nPage faults = %d  Time taken in ms = %f",faults,cpu_time_used);

    printf("\n\n---Power of 2 choices LRU---");
    start = clock();
    faults = p2clru();
    end = clock();
    cpu_time_used = (((double) (end - start)) / CLOCKS_PER_SEC)*1000;
    printf("\nPage faults = %d  Time taken in ms = %f",faults,cpu_time_used);
    printf("\n");
    return 0;
}

int findLRU(int time[], int n){
    int i, minimum = time[0], pos = 0;
    for(i = 1; i < n; ++i){

        if(time[i] < minimum){
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int lru()
{
  int frames[10], i, j, flag1, flag2, counter = 0, faults = 0, time[100], pos;
  for(i = 0; i < no_of_frames; ++i){
      frames[i] = -1;
  }
  for(i = 0; i < no_of_pages; ++i){
      flag1 = flag2 = 0;

      for(j = 0; j < no_of_frames; ++j){
          if(frames[j] == pages[i]){
              counter++;
              time[j] = counter;
                 flag1 = flag2 = 1;
                 break;
             }
      }

      if(flag1 == 0){
          for(j = 0; j < no_of_frames; ++j){
              if(frames[j] == -1){
                  counter++;
                  faults++;
                  frames[j] = pages[i];
                  time[j] = counter;
                  flag2 = 1;
                  break;
              }
          }
      }

      if(flag2 == 0){
          pos = findLRU(time, no_of_frames);
          counter++;
          faults++;
          frames[pos] = pages[i];
          time[pos] = counter;
      }

      printf("\n");

      for(j = 0; j < no_of_frames; ++j){
          printf("%d\t", frames[j]);
      }
  }
  return faults;
}

int p2clru()
{
  srand(time(0));
  int frames[10], i, j, flag1, flag2, counter = 0, faults = 0, time[100], random_pos1, random_pos2, pos;
  for(i = 0; i < no_of_frames; ++i){
      frames[i] = -1;
  }
  for(i = 0; i < no_of_pages; ++i){
      flag1 = flag2 = 0;

      for(j = 0; j < no_of_frames; ++j){
          if(frames[j] == pages[i]){
              counter++;
              time[j] = counter;
                 flag1 = flag2 = 1;
                 break;
             }
      }

      if(flag1 == 0){
          for(j = 0; j < no_of_frames; ++j){
              if(frames[j] == -1){
                  counter++;
                  faults++;
                  frames[j] = pages[i];
                  time[j] = counter;
                  flag2 = 1;
                  break;
              }
          }
      }

      if(flag2 == 0){
        random_pos1 = rand()%no_of_frames;
        random_pos2 = rand()%no_of_frames;
        pos = time[random_pos1]<time[random_pos2]?random_pos1:random_pos2;
        counter++;
          faults++;
          frames[pos] = pages[i];
          time[pos] = counter;
      }

      printf("\n");

      for(j = 0; j < no_of_frames; ++j){
          printf("%d\t", frames[j]);
      }
  }
  return faults;
}
