template <class Object>
Deque<Object>::Deque() { // the constructor
    front = back = NULL;
}

template <class Object>
Deque<Object>::Deque(const Deque& rhs) { // the copy constructor
    front = back = NULL;
    *this = rhs;
}

template <class Object>
Deque<Object>::~Deque() {                         // the destructor
    clear();
}

template <class Object>
bool Deque<Object>::isEmpty() const {             // check if a deque is empty
    return front == NULL;
}

template <class Object>
int Deque<Object>::size() const {                 // retrieves # deque nodes
    int i = 0;
    if (!isEmpty()) {
        i++;
        for (DequeNode* ptr = front; ptr != back; ptr = ptr->next) // traverse que
            ++i;
    }
    return i;
}

template <class Object>
const Object& Deque<Object>::getFront() const {   // retrieve the front node
    if (isEmpty())
        throw "empty queue";
    return front->item;
}

template <class Object>
const Object& Deque<Object>::getBack() const {    // retrieve the tail node
    if (isEmpty())
        throw "empty queue";
    return back->item;
}

template <class Object>
void Deque<Object>::clear() {          // clean up all entries.
    while (!isEmpty())                 // dequeue till the queue gets empty.
        removeFront();
}

// add a new node to front
template <class Object>
void Deque<Object>::addFront(const Object& obj) {
    DequeNode* node = new DequeNode;
    node->item = obj;
    //if deque is empty, then node should equal the front and back of the deque
    if (isEmpty()) {
        front = back = node;
        //if there is more than one node, add new node to the front of the deque
    }
    else {
        node->prev = back;
        node->next = front;
        front->prev = node;
        back->next = node;
        front = node;
    }
}

// add a new node to tail
template <class Object>
void Deque<Object>::addBack(const Object& obj) {
    DequeNode* node = new DequeNode;
    node->item = obj;
    //if deque is empty, then node should equal to the front and back of the deque
    if (isEmpty()) {
        front = back = node;
        front->next = front;
        front->prev = front;
        //if there is more than one node, add new node to the back of the deque
    }
    else {
        node->prev = back;
        back->next = node;
        back = node;
        front->prev = node;
        node->next = front;
    }
}

template <class Object>
Object Deque<Object>::removeFront() {
    //check if deque is empty
    if (isEmpty()) throw "Deque is empty";
    // if there is more than one node, then remove the front node
    else if (size() > 1) {
        Object output = front->item;
        DequeNode* removeFront = front;
        front = front->next;
        front->prev = back;
        delete removeFront;
        removeFront = nullptr;
        return output;
        //if there is only one node, then deque is NULL
    }
    else {
        DequeNode* remove = front;
        Object output = remove->item;
        front = back = NULL;
        delete remove;
        remove = nullptr;
        return output;
    }
}

template <class Object>
Object Deque<Object>::removeBack() {
    //check if the deque is empty 
    if (isEmpty())
        throw "Deque is empty";
    // if there is more than one node, then remove the back node
    else if (size() > 1) {
        Object output = back->item;
        DequeNode* removeBack = back;
        back = back->prev;
        back->next = front;
        front->prev = back;
        delete removeBack;
        removeBack = nullptr;
        return output;
    }
    //if there is only one node, then deque is NULL
    else {
        DequeNode* remove = back;
        Object output = remove->item;
        front = back = NULL;
        delete remove;
        remove = nullptr;
        return output;
    }
}

template <class Object>
const Deque<Object>& Deque<Object>::operator=(const Deque& rhs) { // assign
    if (this != &rhs) { // avoid self assignment
        clear();
        DequeNode* rptr = rhs.front;
        for (int i = 0; i < rhs.size(); i++) {
            addBack(rptr->item);
            rptr = rptr->next;
        }
    }
    return *this;
}


