#include <stddef.h>

#include "seqList.h"

template <class T>
class sLinkList : public list<T> {
   private:
    struct node {
        T data;
        node *next;
        node(const T &x, node *n = NULL) {
            data = x, next = n;
        }
        node() : next(NULL) {}
        ~node() {}
    };

    node *head;
    int currentLength;
    node *move(int i) const;  // Return the address of the ith element

   public:
    sLinkList();
    ~sLinkList() {
        clear();
        delete head;
    }
    void clear();
    int length() const { return currentLength; }
    void insert(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    T visit(int i) const;
    void traverse() const;
    void erase(int i);
    int size();
    void erase(int i, int j);
    void erase_xy(int i, int j);
    void reverse();
};

template <class T>
class dLinkList : public list<T> {
   private:
    struct node {  
        T data;
        node *prev, *next;
        node(const T &x, node *p = NULL, node *n = NULL) {
            data = x;
            next = n;
            prev = p;
        }
        node() : next(NULL), prev(NULL) {}
        ~node() {}
    };
    node *head, *tail;        
    int currentLength;        
    node *move(int i) const; 

   public:
    dLinkList();
    ~dLinkList() {
        clear();
        delete head;
        delete tail;
    }
    void clear();
    int length() const { return currentLength; }
    void insert(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    T visit(int i) const;
    void traverse() const;
    void erase(int i);
};

// Single Linked List
template <class T>
sLinkList<T>::sLinkList() {
    head = new node;  // node() : next(NULL) {}, new returns a pointer
    currentLength = 0;
}
template <class T>
typename sLinkList<T>::node *sLinkList<T>::move(int i) const {  // getElement of index i
    node *p = head;
    while (i-- >= 0)
        p = p->next;
    return p;
}
template <class T>
void sLinkList<T>::insert(int i, const T &x) {
    // if (i == 0) {
    //     cout << "Indexing startes from 1!" << endl;
    //     throw "Indexing startes from 1!";
    // }
    node *pos;
    pos = move(i - 1);
    pos->next = new node(x, pos->next);
    ++currentLength;
}
template <class T>
void sLinkList<T>::remove(int i) {
    node *pos, *delp;
    pos = move(i - 1);
    delp = pos->next;
    pos->next = delp->next;  // 绕过delp
    delete delp;
    --currentLength;
}
template <class T>
void sLinkList<T>::clear() {
    node *p = head->next, *q;
    head->next = NULL;
    while (p != NULL) {  // 删除链表中的所有结点
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}
template <class T>
int sLinkList<T>::search(const T &x) const {
    node *p = head->next;
    int i = 0;
    while (p != NULL && p->data != x) {
        p = p->next;
        ++i;
    }
    if (p == NULL)
        return -1;
    else
        return i;
}
template <class T>
void sLinkList<T>::traverse() const {
    node *p = head->next;
    cout << endl;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
template <class T>
void sLinkList<T>::erase(int i) {
    /*erase nodes whoes value equals node's value with i-th index*/
    node *pre = move(i - 1);
    node *delp = pre->next;
    T tmp = delp->data;
    int cnt = 1;
    pre->next = delp->next;
    delete delp;
    pre = head;  // TODO  try to change to head-> next
    while (pre->next != NULL) {
        if (pre->next->data == tmp) {
            delp = pre->next;
            pre->next = delp->next;
            delete delp;
            ++cnt;
        } else
            pre = pre->next; // fixed bug when have several  tmp[i] in a raw 
    }
    currentLength -= cnt;
}
template <class T>
int sLinkList<T>::size(){
    return currentLength;
}
template <class T>
void sLinkList<T>::erase(int i, int j) {
    /* erase nodes whoes values are between [i, j] */
    node *pre, *delp;
    int cnt = 0;

    pre = head; 
    while (pre->next != NULL) {
        if (i <= pre->next->data && pre->next->data <= j) {
            delp = pre->next;
            pre->next = delp->next;
            delete delp;
            ++cnt;
        } else
            pre = pre->next; // fixed bug when have several  tmp[i] in a raw 
    }
    currentLength -= cnt;
}

template <class T>
void sLinkList<T>::erase_xy(int x, int y) {
    /* deletes all nodes who's values equal to node values from x-th to y-th indecies  */
    int cnt = 0;
    int i;
    node *delp;
    int arrSize = y - x + 1;
    T *tmp = new T[arrSize];
    node *pre = move(x - 1);
    // time complexity (O(n^2))
    for (i = 0; i < arrSize; i++) {
        node *delp = pre->next;
        tmp[i] = delp->data;
        // map[delp->data] = true;
        pre->next = delp->next;
        delete delp;
        cnt++;
    }
    for (i = 0; i < arrSize; i++) {
        pre = head; 
        while (pre->next != NULL) {
            if (pre->next->data == tmp[i]) {
                delp = pre->next;
                pre->next = delp->next;
                delete delp;
                ++cnt;
            } else
                pre = pre->next; // fixed bug when have several  tmp[i] in a raw 
        }
    }
    
    currentLength -= cnt;
}

template <class T>
T sLinkList<T>::visit(int i) const {
    return move(i)->data;
}

template <class T>
void sLinkList<T>::reverse() {
    node* curr = head->next; // always assign to head->next, not head
    node* prev = nullptr;
    node* next = nullptr;
    while(curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head -> next = prev;
}
//-------------------------------------------------------------------------------------------------------
// Double Linked List
template <class T>
dLinkList<T>::dLinkList() {
    head = new node;
    head->next = tail = new node;
    tail->prev = head;
    currentLength = 0;
}

template <class T>
typename dLinkList<T>::node *dLinkList<T>::move(int i) const {
    node *p = head;
    while (i-- >= 0)
        p = p->next;
    return p;
}
template <class T>
void dLinkList<T>::insert(int i, const T &x) {
    node *pos, *tmp;
    pos = move(i);                      // 注意，move需要自行实现
    tmp = new node(x, pos->prev, pos);  // 结点构造函数
    pos->prev->next = tmp;
    pos->prev = tmp;
    ++currentLength;
}
template <class T>
void dLinkList<T>::remove(int i) {
    node *pos;
    pos = move(i);  // 与单链表不同，可直接定位到删除结点
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    delete pos;
    --currentLength;
}
template <class T>
void dLinkList<T>::clear() {
    node *p = head->next, *q;
    head->next = NULL;
    tail->prev = head;
    while (p != tail) {  // 删除链表中的所有结点
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}
template <class T>
int dLinkList<T>::search(const T &x) const {
    node *p = head->next;
    int i = 0;
    while (p != tail && p->data != x) {
        p = p->next;
        ++i;
    }
    if (p == tail)
        return -1;
    else
        return i;
}
template <class T>
void dLinkList<T>::traverse() const {
    node *p = head->next;
    cout << endl;
    while (p != tail) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
// TODO, but worked ))
template <class T>
void dLinkList<T>::erase(int i) {
    node *pre = move(i - 1);
    node *delp = pre->next;
    T tmp = delp->data;
    int cnt = 1;
    pre->next = delp->next;
    delete delp;
    for (pre = head; pre->next != NULL; pre = pre->next)
        if (pre->next->data == tmp) {
            delp = pre->next;
            pre->next = delp->next;
            delete delp;

            ++cnt;
        }
    currentLength -= cnt;
}
template <class T>
T dLinkList<T>::visit(int i) const {
    return move(i)->data;
}