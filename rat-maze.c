#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

int top=-1;
int stack[300][3]={}; //record the path
int isEmpty();   //to check if stack is empty
void pop();      //delete the latest element in the stack
void push(int,int,int);  //add the element in the stack
int move(int);  //show the next step the rat goes
int i,j,g,h,m,p,d=1;  /*(i,j) showed the start position, (g,h) showed the next position, and(m,p) showed the final position.
                         d showed the direction.*/
int main() {
    FILE *file;
    printf("Enter filename: ");  //input the maze file.
    char filename[50];
    gets(filename);    //read the file name.
    file=fopen(filename,"r");  //open the file.
    if(file==NULL){
        return -1;  //if the file isn't exist, return -1.
    }
    int num;
    int maze[17][17]={};  /*Because the maze is 17*17 matrix, building a 17*17 array. However, is the size of maze changed,
                            the size of array need to be modified.*/

    for(int i=0;i<17;i++){        // i represent the row of array.
        for(int j=0;j<17;j++){    // j represent the column of array.
            fscanf(file,"%1d",&num);
            maze[i][j]=num;         // put every number into maze array.
            printf("%1d",num);   //print the maze.
            if(j==16){
                printf("\n");
            }
        }
    }
    fclose(file);   //close the file.
    int a=0;
    do{
        int mark[17][17]={};   // mark array record the road which has been stepped.
        int time=0;   // time record the number of steps.
        bool escape=false;  //escape show whether the rat could escape or not.
        d=1;   //initialize the direction is 1.
        memset(stack,0,sizeof(stack));  // clean up the data of last time we used.
        top=-1;
        printf("enter start position:\n");
        scanf("%d%d",&i,&j);   //read the start position.
        if(i==-1&&j==-1){            //if the start position is(-1,-1), end the code.
            printf("end the code.");
            break;
        }
        else{
            mark[i][j]=1;
            push(i,j,d);    //add the first position in the stack.
        }
        printf("enter end position:\n");
        scanf("%d%d",&m,&p);   //read the end position.
        while(!isEmpty()&& !escape){    //if the stack is empty or the rat has escaped, can break the loop.
            i=stack[top][0];j=stack[top][1];d=stack[top][2];   /* if there isn't any road to go, the rat have to back to the previous step.
                                                           Also, it means that that step is wrong, so we delete it from the stack. */
            pop();
            printf("%d:%d,%d\n",time,i,j);   //Although the rat go back to last step, we need to print the whole process.
            time++;
            while(d<5){  //Because there are only four direction, the d can't be larger than 4.
                move(d);   //show the new step.
                if(g==m&&h==p){  // if the new step equal to the end position, it means that the rat is successful.
                    escape=true;
                    printf("%d:%d,%d\n",time,g,h);  //print the end step.
                    break;
                }
                else if((!maze[g][h])&&(!mark[g][h])){   /*if the road is open(equal to 1) and the rat hasn't gone to,
                                                          * we can add the position to stack and record that the rat has gone to.
                                                          * However, we need to plus the direction so the next time if the rat come back,
                                                          * we can check up from the new direction.
                                                          */
                    mark[g][h]=1;
                    printf("%d:%d,%d\n",time,g,h);
                    time++;
                    push(i,j,d+1);
                    i=g;j=h;d=1;
                }
                else d++; // if the road is close, we can check other direction.
            }
        }
        if(escape){
            printf("Successfully escape.\n"); // the condition of success.
        }
        else printf("Failed to escape.\n");   //the condition of fail.
    }
    while(a>-1);
    return 0;
}
int isEmpty(){         //the top os initialize to -1 so if the top equal to -1, which means that the stack is empty.
    if(top==-1){
        return 1;
    }
    else{
        return 0;
    }
}
void push(int x,int y, int dir){    //add the possible position and direction to stack.
    top++;
    stack[top][0]=x;
    stack[top][1]=y;
    stack[top][2]=dir;
}
void pop(){    //minus the top to delete the latest element.
    top--;
}
int move(int dir){
    switch(dir){
        case 1:     // direction 1 means east, so we need to plus the number of column.
            g=i;h=j+1;
            break;
        case 2:     // direction 2 means south, so we need to plus the number of row.
            g=i+1;h=j;
            break;
        case 3:    // direction 3 means north, so we need to minus the number of row.
            g=i-1;h=j;
            break;
        case 4:   // direction 4 means west, so we need to minus the number of column.
            g=i;h=j-1;
            break;
    }
}

