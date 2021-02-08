#include<stdio.h>
#include <unistd.h>
#include<string.h>

void main(){
    char* message = "Hello! What's going on today?";
    int message_length = strlen(message);

    const int width = 20; //number of characters the screen is wide

    const char SPACE = ' ';

    //start scroll on the right of the screen with 1 char
    int display_start = width - 1;
    int display_end = width - 1;

    //tracks text to take from the message string
    int message_start = 0;
    int message_end = 0;
    
    char str[] = "                    "; //20 spaces (probably a better way to do this)

    while(1){
        usleep(100000);

        //fill str with spaces
        for(int i = 0; i < width; i++){
            str[i] = SPACE;
        }

        //fill correct part of message onto the correct part of str
        int i = display_start;
        int c = message_start;

        while(i <= display_end){
            str[i] = message[c];
            i++;
            c++;
        }

        int display_len = display_end - display_start + 1;
        int message_len = message_end - message_start + 1; 

        //putting text onto the screen
        if(message_end < message_length-1){
            message_end++;
            
            if(display_start > 0){
                display_start--;
            }else{
                message_start++;
            }

        }
        
        //all text has been seen, but still needs to be pushed to the left
        else if(display_start != 0){
            display_start--;
            display_end--;
        }

        //rotating last text off the screen
        else{
            display_end--;
            message_start++;
        }

        //reset condition
        if(display_end < 0){
            message_start = 0;
            message_end = 0;

            display_start = width - 1;
            display_end = width - 1;
        }

        //error checking
        if(display_end - display_start != message_end - message_start){
            printf("bounds don't line up!\n");
            printf("display_end=%d, display_start=%d, message_end=%d, message_start=%d\n", display_end, display_start, message_end, message_start);
        }

        printf("%s\n", str);

        fflush(stdout);
    }

}