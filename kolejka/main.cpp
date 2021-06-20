#define _CRT_SECURE_NO_WARNIGS
#include <iostream>
#include <string>
#include "queue.hpp"

using namespace std;

int main() {
    Queue que;
    char comm[15];
    int x,n=0;
    string temp;
    while(scanf("%s",comm)>0)
    {
        string command=comm;
        x=0;
        if(command.compare("ACTUAL")==0) x=1;
        else if(command.compare("NEXT")==0) x=2;
        else if(command.compare("PREV")==0) x=3;
        else if(command.compare("ADD_BEG")==0) x=4;
        else if(command.compare("ADD_END")==0) x=5;
        else if(command.compare("ADD_ACT")==0) x=6;
        else if(command.compare("DEL_BEG")==0) x=7;
        else if(command.compare("DEL_END")==0) x=8;
        else if(command.compare("DEL_VAL")==0) x=9;
        else if(command.compare("DEL_ACT")==0) x=10;
        else if(command.compare("PRINT_FORWARD")==0) x=11;
        else if(command.compare("PRINT_BACKWARD")==0) x=12;
        else if(command.compare("PUSH")==0) x=13;
        else if(command.compare("POP")==0) x=14;
        else if(command.compare("PRINT_QUEUE")==0) x=15;
        else if(command.compare("SIZE")==0) x=16;
        else if(command.compare("COUNT")==0) x=17;
        else if(command.compare("GARBAGE_SOFT")==0) x=18;
        else if(command.compare("GARBAGE_HARD")==0) x=19;

        switch(x) {
            case 1:
                que.getAct();
                break;
            case 2:
                que.getNext();
                break;
            case 3:
                que.getPrev();
                break;
            case 4:
                scanf("%d",&n);
                que.addNodeBeg(n);
                break;
            case 5:
                scanf("%d",&n);
                que.addNodeEnd(n);
                break;
            case 6:
                scanf("%d",&n);
                que.addNodeAct(n);
                break;
            case 7:
                que.deleteNodeBeg();
                break;
            case 8:
                que.deleteNodeEnd();
                break;
            case 9:
                scanf("%d",&n);
                que.deleteNode(n);
                break;
            case 10:
                que.deleteNodeAct();
                break;
            case 11:
                que.printListF();
                break;
            case 12:
                que.printListB();
                break;
            case 13:
                scanf("%d",&n);
                que.push(n);
                break;
            case 14:
                que.pop();
                break;
            case 15:
                que.printQueue();
                break;
            case 16:
                que.size();
                break;
            case 17:
                que.countP();
                break;
            case 18:
                que.gSoft();
                break;
            case 19:
                que.gHard();
                break;
            default:
                return 0;
       }
    }
    return 0;
}

