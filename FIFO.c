#include <stdio.h>

int main()
{
    int incomingStream[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2, 0};
    int pageFaults = 0;
    int framesCount = 3;
    int m, n, s, pagesCount;

    // * pagesCount = total count of pages {4, 1, 2, 4, 5} = 5 pages.
    pagesCount = sizeof(incomingStream)/sizeof(incomingStream[0]);

    printf("Incoming \t Frame 1 \t Frame 2 \t Frame 3");
    // * temp is the array of framesCount that holds the pages
    int frames[framesCount];

    // * INITIALIZING frames with -1
    for(m = 0; m < framesCount; m++)
    {
        frames[m] = -1;
    }

    for(int pageOffset = 0; pageOffset < pagesCount; pageOffset++)
    {
        s = 0;

        // * CHECK IF PAGES IS ALREADY PRESENT
        for(n = 0; n < framesCount; n++)
        {
            if(incomingStream[pageOffset] == frames[n])
            {
                s++;
                pageFaults--;
            }
        }
        pageFaults++;
        
        // * BASICALLY IF THERE IS EMPTY SPACE IN THE FRAMES THEN SIMPLE POPULATE THOSE FRAMES UNTIL FULL
        // * ONCE FULL GO IN THE ELSE PART!
        if((pageFaults <= framesCount) && (s == 0))
        {
            frames[pageOffset] = incomingStream[pageOffset];
        }
        else if(s == 0)
        {
            frames[(pageFaults - 1) % framesCount] = incomingStream[pageOffset];
        }
      
        printf("\n");
        printf("%d\t\t\t",incomingStream[pageOffset]);

        for(n = 0; n < framesCount; n++)
        {
            if(frames[n] != -1)
                printf(" %d\t\t\t", frames[n]);
            else
                printf(" - \t\t\t");
        }
    }

    printf("\nTotal Page Faults:\t%d\n", pageFaults);
    return 0;
}