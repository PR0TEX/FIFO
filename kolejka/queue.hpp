#ifndef queue_hpp
#define queue_hpp
class Queue{
protected:
    
    typedef struct node{
        int data;
        node* xptr;
        
    }*nodePtr;
    int count=0;
    int s=0;
    bool isEmpty=true;
    nodePtr head;
    nodePtr curr;
    nodePtr end;
    nodePtr front;
    nodePtr back;
public:
    bool const check(struct node* object);
    nodePtr XOR(struct node* a, struct node* b);
    void const getAct();
    void const getNext();
    void const getPrev();
    Queue();
    void addNodeBeg(int addData);
    void addNodeAct(int addData);
    void addNodeEnd(int addData);
    void deleteNodeBeg();
    void deleteNodeEnd();
    void deleteNode(int delData);
    void deleteNodeAct();
    void const printListB();
    void push(int addData);
    void pop();
    void const printQueue();
    void const countP();
    void const printListF();
    void const size();
    void gSoft();
    void gHard();
    nodePtr* find(struct node* side,struct node* start,struct node* temp);
};
#endif
