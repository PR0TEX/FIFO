#include <iostream>
#include "queue.hpp"
using namespace std;
Queue::Queue()
: head(nullptr), curr(nullptr), end(nullptr),front(nullptr),back(nullptr){
}
//operacja xor na dwoch adresach
struct Queue::node* Queue::XOR(struct node* a, struct node* b)
{
    return (struct node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}
//dodawanie elementu do kolejki
void Queue::push(int addData)
{
    nodePtr prev=NULL;
    nodePtr temp=NULL;
    nodePtr buffor=NULL;
    int prevCount=count;
    isEmpty=false;
    if(head==NULL){
        count++;
        Queue::addNodeBeg(addData);
        front=head;
        back=head;
        return;
    }else if(front==NULL){
        end->data=addData;
        front=end;
        back=end;
    }else if(s>count)
    {
        if(back==head) {
            count++;
            end->data=addData;
            back=end;
            return;
        }
        node** pack=find(back,head,head);
        prev=pack[0];
        prev->data=addData;
        back=prev;
    }
    else{
         if((front==end && back==head) || front==back){
            Queue::addNodeBeg(addData);
            back=head;
        }
         else {
             if(end==back){
             buffor=back->xptr;
             addNodeAct(addData);
             back=end->xptr;
             back->xptr=XOR(buffor,end);
             }else{
                 node** pack=find(front,NULL,head);
                 temp=pack[1];
                 if(temp != back){
                   if(!temp) temp=head;
                 temp->data=addData;
                 back=temp;
                 }else {
                     buffor=back->xptr;
                     curr=back;
                     addNodeAct(addData);
                     back=XOR(curr->xptr,XOR(buffor,head));
                 }
             }
         }
    }
    if(prevCount == count) count++;
}
//usuwanie elementu z kolejki
void Queue::pop()
{
    if(front==head)
    {
        if(front==back) {
            isEmpty=true;
            count=0;
        }else count--;
        cout<<front->data<<endl;
        front=end;
        return;
    }
    if(front==end){
        if(isEmpty){
            cout<<"NULL"<<endl;
            return;
        }
        if(front==back) {
            count=0;
            isEmpty=true;
        }else count--;
        cout<<front->data<<endl;
        if(!isEmpty) front=front->xptr;
    }else
    {
        count--;
        node** pack=find(front,head,head);
        nodePtr prev=pack[0];
        cout<<front->data<<endl;
        front=prev;
    }
}
//dodaie i ustawia alement jako pierwszy
void Queue::addNodeBeg(int addData)
{
    s++;
    nodePtr n=new node;
    n->data=addData;
    if(!head)
    {
        n->xptr=NULL;
        curr=n;
        end=n;
    }
    else
    {
        head->xptr=XOR(n,head->xptr);
        n->xptr=head;
    }
    head=n;
    if(check(head)) count++;
}
//dodaje element i ustawia go jako ACTUAL
void Queue::addNodeAct(int addData)
{
    s++;
    if(curr==head) {
        Queue::addNodeBeg(addData);
        return;
    }
    nodePtr n=new node;
    n->data=addData;
    if(!head)
    {
        n->xptr=NULL;
        head=n;
        end=n;
        curr=n;
    }
    else
    {
        nodePtr prev=NULL;
        nodePtr temp=head;
        nodePtr next;
        
        do {
            next = XOR(prev,temp->xptr);
            if(next == curr)
            {
                n->xptr=XOR(temp,next);
                next->xptr=XOR (n, XOR(temp, next->xptr));
                temp->xptr = XOR(prev,n);
            }
            prev=temp;
            temp=next;
            
        }while(next!=curr);
        curr=next;
    }
}
//dodaje element i ustawia jako ostatni
void Queue::addNodeEnd(int addData)
{
    s++;
    nodePtr n=new node;
    n->data=addData;
    if(!head)
    {
        n->xptr=NULL;
        curr=n;
        head=n;
    }
    else{
        end->xptr=XOR(n,end->xptr);
        n->xptr=end;
        
    }
    end=n;
    if(check(end)) count++;
}
//usuwa pierwszy element
void Queue::deleteNodeBeg()
{
    if(head==NULL) return;
    s--;
    if(head==end)
    {
        count=0;
        front=NULL;
        delete head;
        head=NULL;
        return;
    }
    nodePtr temp=head->xptr;
    if(check(head)){
            count--;
            if(head==front) front=end;
            else if(head==back) back=temp;
        }
        temp->xptr=XOR(temp->xptr,head);
        if(curr==head) curr=temp;
        delete head;
        head=temp;
}
//usuwa ostatni element
void Queue::deleteNodeEnd()
{
    if(head==NULL) return;
    s--;
    if(head==end)
    {
        count=0;
        front=NULL;
        delete end;
        head=NULL;
        return;
    }
        nodePtr temp=end->xptr;
    if(check(end)){
           count--;
           if(end==front) front=end->xptr;
           else if(end==back) back=head;
       }
        temp->xptr=XOR(temp->xptr,end);
        if(curr==end) curr=temp;
        delete end;
        end=temp;
}
//usuwa element ktory znajduje sie na miejscu ACTUAL
void Queue::deleteNodeAct()
{
    if(head==NULL) return;
    s--;
    if(head==end)
    {
        delete head;
        head=NULL;
        return;
    }
    if(curr==head)
    {
        Queue::deleteNodeBeg();
        curr=end;
    }
    else if(curr==end)
    {
        Queue::deleteNodeEnd();
    }
    else
    {
        node** pack=find(curr,NULL,curr);
        nodePtr prev=pack[0];
        pack=find(curr,end->xptr,curr);
        nodePtr next=pack[2];
        nodePtr temp=curr;
        curr=prev;
        prev->xptr=XOR(XOR(prev->xptr,temp), next);
        next->xptr=XOR(XOR(next->xptr,temp),prev);
        delete temp;
    }
}
//usuwa wszystkie elementy, ktore przechowuja konkretna wartosc
void Queue::deleteNode(int delData)
{
    s--;
    nodePtr next=NULL;
    nodePtr prev=NULL;
    nodePtr temp=head;
    if(head==end)
    {
        curr=nullptr;
        end=nullptr;
        head=nullptr;
        return;
    }
    while(temp != NULL)
    {
        if(temp==head) next=temp->xptr;
        else next=XOR(prev,temp->xptr);
        
        if(temp->data==delData)
        {
            nodePtr x=temp;
            if(temp==head)
            {
                Queue::deleteNodeBeg();
                temp=NULL;
            }
            else if(temp==end)
            {
                Queue::deleteNodeEnd();
                prev=XOR(prev,x->xptr);
                temp=prev;
                next=NULL;
            }
            else if(temp==curr)
            {
                Queue::deleteNodeAct();
                temp=next;
                prev=XOR(prev->xptr,x);
            }
            else
            {
                prev->xptr=XOR(next,XOR(prev->xptr,temp));
                next=XOR(temp->xptr,prev);
                next->xptr=XOR(XOR(temp,next->xptr),prev);
                if(prev == head)
                {
                    head->xptr=prev->xptr;
                }
                delete temp;
                temp=prev;
            }
        }
        prev=temp;
        temp=next;
    }
}
//wypisywanie kolejki
void const Queue::printQueue()
{
    if(isEmpty){
        cout<<"NULL"<<endl;
        return;
    }
    nodePtr temp=end;
    nodePtr tempPrev=NULL;
    nodePtr next=NULL;
    nodePtr prev=NULL;
    nodePtr buffor=NULL;
    nodePtr buffor2=NULL;
    if(head != end){
        node** pack=find(front,end,end);
        temp=pack[1];
        tempPrev=pack[2];
        prev=pack[0];
    }else prev=NULL;
    temp=front;
    if(!prev && tempPrev==end) {
        buffor=temp->xptr;
        temp->xptr=XOR(buffor,end);
    }
    bool change=false;
    
    buffor2=prev;
    
    while(true)
    {
        if(temp==head)
        {
            next=end;
            prev=NULL;
            change=true;
        }
        else next=XOR(prev,temp->xptr);
        printf("%d ",temp->data);
        if(temp==back) {
            cout<<endl;
            return;
        }
        if(temp==head && buffor2==NULL)
        {
            cout<<endl;
            if(buffor != NULL) front->xptr=buffor;
            return;
        }
        if(!change) prev=temp;
        temp=next;
        change=false;
    }
}
//wypisuje Queuee od przodu (od head do end)
void const Queue::printListF()
{
    nodePtr next=NULL;
    nodePtr prev=NULL;
    nodePtr temp=head;
    while(temp != NULL)
    {
        next=XOR(prev,temp->xptr);
        printf("%d ",temp->data);
        if(temp==end)
        {
            cout<<endl;
            return;
        }
        prev=temp;
        temp=next;
    }
    if(temp==NULL) cout<<"NULL"<<endl;
}
//wypisuje Queuee od tylu (od end do head)
void const Queue::printListB()
{
    nodePtr next=NULL;
    nodePtr prev=NULL;
    nodePtr temp=end;
    while(temp != NULL)
    {
        next=XOR(prev,temp->xptr);
        printf("%d ",temp->data);
        if(temp==head)
        {
            cout<<endl;
            return;
        }
        prev=temp;
        temp=next;
    }
    cout<<endl;
    if(temp==NULL) cout<<"NULL"<<endl;
}
//zwraca wartosc ACTUAL, jezeli Queuea jest pusta to zwraca NULL
void const Queue::getAct()
{
    if(head == NULL )
    {
        cout<<"NULL"<<endl;
        return;
    }
    if(curr != NULL) cout<<curr->data<<endl;
    else cout<<"NULL"<<endl;
}
//zwraca wartosc poprzedzajaca ACTUAL i ustawia go ACTUAL
void const Queue::getNext()
{
    if(head == NULL )
    {
        cout<<"NULL"<<endl;
        return;
    }
        nodePtr next=end;
        nodePtr temp=NULL;
        nodePtr tempNext=next;

    if(curr==end) curr=head;
    else
    {
        while(XOR(next->xptr,temp) != curr)
        {
            next=XOR(temp,tempNext->xptr);
            temp=tempNext;
            tempNext=next;
        }
        curr=next;
    }
    if(curr != NULL) cout<<curr->data<<endl;
    else cout <<"NULL"<<endl;
}
// zwraca wartosc uprzedzajaca ACTUAL i ustawia go ACTUAL
void const Queue::getPrev()
{
    if(head == NULL )
    {
        cout<<"NULL"<<endl;
        return;
    }
    if(curr == head) curr=end;
    else
    {
        node** pack=find(curr,NULL,NULL);
        nodePtr prev=pack[0];
        curr=prev;
    }
    if(curr!=NULL) cout<<curr->data<<endl;
    else cout<<"NULL"<<endl;
}
//wypisuje rozmiar listy
void const Queue::size()
{
    cout<<s<<endl;
}
//wypisuje rozmiar kolejki
void const Queue::countP()
{
    cout<<count<<endl;
}
//przypisanie wartosci 0 do wszystkich elementow listy, ktore nie naleza do kolejki
void Queue::gSoft()
{
    nodePtr temp=end;
    nodePtr next=NULL;
    nodePtr prev=NULL;
    if(s==0) return;
    if(isEmpty) {
        temp=head;
        while(temp != NULL)
        {
            next=XOR(prev,temp->xptr);
            temp->data=0;
            if(temp==end)  return;
            prev=temp;
            temp=next;
        }
    }
    if(head != end){
        node** pack=find(back,prev,temp);
        temp=pack[1];
        next=pack[2];
        prev=pack[0];
        while(temp != front){
            temp->data=0;
            next=XOR(prev,temp->xptr);
            prev=temp;
            temp=next;
            if(temp==head){
                temp=end;
                prev=NULL;
            }
        }
    }
}
//usuwanie wszystkich elementow listy, ktore nie naleza do kolejki
void Queue::gHard()
{
    node** pack=find(back,NULL,end);
    nodePtr temp=pack[1];
    nodePtr next=pack[2];
    nodePtr prev=pack[0];
    if(s==0) return;
    
    if(isEmpty) {
        while(head){
            s--;
            deleteNodeBeg();
        }
    }else{
        while(temp != front){
            if(s+1==count) return;
            next=XOR(prev,temp->xptr);
            if(temp==head) {
                deleteNodeBeg();
                temp=end;
                prev=NULL;
            }
            else if(temp==end) {
                deleteNodeEnd();
                temp=end;
                prev=NULL;
            }
            else{
                prev->xptr=XOR(XOR(prev->xptr,temp),next);
                next->xptr=XOR(XOR(next->xptr,temp),prev);
                delete temp;
                temp=next;
            }
            s--;
        }
    }
}
//sprawdzenie czy podany element nalezy do kolejki
bool const Queue::check(struct node* object)
{
    if(isEmpty) return false;
    node** pack=find(back,head,head);
    nodePtr temp=pack[1];
    nodePtr next=pack[2];
    nodePtr prev=pack[0];
    while(temp != front){
        if(temp==object) return true;
        next=XOR(prev,temp->xptr);
        prev=temp;
        temp=next;
        if(prev==head){
            temp=end;
            prev=NULL;
        }else if(prev==end)
        {
            temp=head;
            prev=NULL;
        }
        
}
    return false;
}
//znajduje odpowiednie wartosci nastepnika i poprzednika
struct Queue::node** Queue::find(struct node *side,struct node *start,struct node* val)
{
    nodePtr next=NULL;
    nodePtr prev=NULL;
    bool flag=false;
    static node** pack=(node**) malloc(3*sizeof(node*));
    if(val!=start) flag=true;
    while(start != side){
        next=XOR(prev,val->xptr);
        prev=val;
        val=next;
        if(flag) start=prev;
        else start=val;
    }
    pack[0]=prev;
    pack[1]=val;
    pack[2]=next;

    return pack;
    
}




