// Default Constructor. Will properly initialize a queue to
// be an empty queue, to which values can be added.
template <class T>
FIFOQueueClass<T>::FIFOQueueClass() {
    head = 0;
    tail = 0;
}

// NOTE: This class does NOT have a copy ctor or an overloaded
// assignment operator – therefore, using either of those
// things will result in a shallow copy. Users should not
// attempt to copy a FIFOQueueClass object using either of
// these approaches!
// Destructor. Responsible for making sure any dynamic memory
// associated with an object is freed up when the object is
// being destroyed.
template <class T>
FIFOQueueClass<T>::~FIFOQueueClass() {
    clear();
}

// Inserts the value provided (newItem) into the queue.
template <class T>
void FIFOQueueClass<T>::enqueue(const T &newItem) {
    // add a node if empty
    if (head == 0) {
        LinkedNodeClass<T> *nodeToInsert = new LinkedNodeClass<T>(0, 
                                                                  newItem, 
                                                                  0);
        head = nodeToInsert;
        tail = nodeToInsert;
        return;
    }
    // if not empty
    LinkedNodeClass<T> *nodeToInsert = new LinkedNodeClass<T>(tail,
                                                              newItem, 
                                                              0);
    nodeToInsert->setBeforeAndAfterPointers();
    tail = nodeToInsert;
}

// Attempts to take the next item out of the queue. If the
// queue is empty, the function returns false and the state
// of the reference parameter (outItem) is undefined. If the
// queue is not empty, the function returns true and outItem
// becomes a copy of the next item in the queue, which is
// removed from the data structure.
template <class T>
bool FIFOQueueClass<T>::dequeue(T &outItem) {
    // empty queue
    if (head == 0) {
        return false;
    }
    // deque from front
    else {
        LinkedNodeClass<T> *currNode = head;
        outItem = currNode->getValue();
        // if there is only one element
        if (currNode->getNext() == 0) {
            head = 0;
            tail = 0;
        }
        else {
            head = currNode->getNext();
            head->setPreviousPointerToNull();
        }

        delete currNode;
        return true;
    }
}

// Prints out the contents of the queue. All printing is done
// on one line, using a single space to separate values, and a
// single newline character is printed at the end. Values will
// be printed such that the next value that would be dequeued
// is printed first.
template <class T>
void FIFOQueueClass<T>::print() const {
    LinkedNodeClass<T> *currNode = head;
    while (currNode != 0) {
        cout << " " << currNode->getValue();
        currNode = currNode->getNext();
    }
    cout << endl;
}

// Returns the number of nodes contained in the queue.
template <class T>
int FIFOQueueClass<T>::getNumElems() const {
    int num = 0;
    LinkedNodeClass<T> *currNode = head;
    while (currNode != 0) {
        num++;
        currNode = currNode->getNext();
    }
    return num;
}

// Clears the queue to an empty state without resulting in any
// memory leaks.
template <class T>
void FIFOQueueClass<T>::clear() {
    // delete node if head is not null
    while (head != 0) {
        LinkedNodeClass<T> *currNode = head;
        head = head->getNext();
        delete currNode;
    }

    // set tail back to default
    tail = 0;
}