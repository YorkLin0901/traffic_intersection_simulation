// Default Constructor. Will properly initialize a list to
// be an empty list, to which values can be added.
template <class T>
SortedListClass<T>::SortedListClass() {
    head = 0;
    tail = 0;
}

// Copy constructor. Will make a complete (deep) copy of the list, such
// that one can be changed without affecting the other.
template <class T>
SortedListClass<T>::SortedListClass(const SortedListClass<T> &rhs) {
    head = 0;
    tail = 0;

    // get the head of rhs
    LinkedNodeClass<T> *currNode = rhs.head;
    // copy until tail
    while (currNode != 0) {
        insertValue(currNode->getValue());
        currNode = currNode->getNext();
    }
}

// Destructor. Responsible for making sure any dynamic memory
// associated with an object is freed up when the object is
// being destroyed.
template <class T>
SortedListClass<T>::~SortedListClass() {
    clear();
}

// Assignment operator. Will assign one list (on left hand side of
// operator) to be a duplicate of the other (on the right hand side
// of operator).
template <class T>
SortedListClass<T>& SortedListClass<T>::operator=(
    const SortedListClass<T> &rhs) {
    clear();

    // get the head of rhs
    LinkedNodeClass<T> *currNode = rhs.head;
    // copy until tail
    while (currNode != 0) {
        insertValue(currNode->getValue());
        currNode = currNode->getNext();
    }

    // dereference
    return *this;
}

// Clears the list to an empty state without resulting in any
// memory leaks.
template <class T>
void SortedListClass<T>::clear() {
    // delete node if head is not null
    while (head != 0) {
        LinkedNodeClass<T> *currNode = head;
        head = head->getNext();
        delete currNode;
    }

    // set tail back to default
    tail = 0;
}

// Allows the user to insert a value into the list. Since this
// is a sorted list, there is no need to specify where in the list
// to insert the element. It will insert it in the appropriate
// location based on the value being inserted. If the node value
// being inserted is found to be "equal to" one or more node values
// already in the list, the newly inserted node will be placed AFTER
// the previously inserted nodes.
template <class T>
void SortedListClass<T>::insertValue(
    const T &valToInsert) { //The value to insert into the list
    // add a node if empty
    if (head == 0) {
        LinkedNodeClass<T> *nodeToInsert = new LinkedNodeClass<T>(0, 
                                                                  valToInsert,
                                                                  0);
        head = nodeToInsert;
        tail = nodeToInsert;
        return;
    }
    
    // if not empty, search from head until null or greater val is found
    LinkedNodeClass<T> *currNode = head;
    while (currNode != 0) {
        if (currNode->getValue() <= valToInsert) {
            currNode = currNode->getNext();
        }
        else {
            LinkedNodeClass<T> *nodeToInsert = new LinkedNodeClass<T>(
                                                    currNode->getPrev(), 
                                                    valToInsert, 
                                                    currNode);
            nodeToInsert->setBeforeAndAfterPointers();
            // situation the val is samllest
            if (nodeToInsert->getPrev() == 0) {
                head = nodeToInsert;
            }
            return;
        }        
    }

    // situation that the val is greatest
    LinkedNodeClass<T> *nodeToInsert = new LinkedNodeClass<T>(tail,
                                                              valToInsert,
                                                              0);
    nodeToInsert->setBeforeAndAfterPointers();
    tail = nodeToInsert;
}

// Prints the contents of the list from head to tail to the screen.
// Begins with a line reading "Forward List Contents Follow:", then
// prints one list element per line, indented two spaces, then prints
// the line "End Of List Contents" to indicate the end of the list.
template <class T>
void SortedListClass<T>::printForward() const {
    cout << "Forward List Contents Follow:" << endl;

    // loop from the from
    LinkedNodeClass<T> *currNode = head;
    while (currNode != 0) {
        cout << "  " << currNode->getValue() << endl;
        currNode = currNode->getNext();
    }

    cout << "End Of List Contents" << endl;
}

// Prints the contents of the list from tail to head to the screen.
// Begins with a line reading "Backward List Contents Follow:", then
// prints one list element per line, indented two spaces, then prints
// the line "End Of List Contents" to indicate the end of the list.
template <class T>
void SortedListClass<T>::printBackward() const {
    cout << "Backward List Contents Follow:" << endl;
    
    // loop from the back
    LinkedNodeClass<T> *currNode = tail;
    while (currNode != 0) {
        cout << "  " << currNode->getValue() << endl;
        currNode = currNode->getPrev();
    }

    cout << "End Of List Contents" << endl;
}

// Removes the front item from the list and returns the value that
// was contained in it via the reference parameter. If the list
// was empty, the function returns false to indicate failure, and
// the contents of the reference parameter upon return is undefined.
// If the list was not empty and the first item was successfully
// removed, true is returned, and the reference parameter will
// be set to the item that was removed.
template <class T>
bool SortedListClass<T>::removeFront(T &theVal) {
    if (head == 0) {
        return false;
    }
    else {
        LinkedNodeClass<T> *currNode = head;
        theVal = currNode->getValue();
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

// Removes the last item from the list and returns the value that
// was contained in it via the reference parameter. If the list
// was empty, the function returns false to indicate failure, and
// the contents of the reference parameter upon return is undefined.
// If the list was not empty and the last item was successfully
// removed, true is returned, and the reference parameter will
// be set to the item that was removed.
template <class T>
bool SortedListClass<T>::removeLast(T &theVal) {
    if (head == 0) {
        return false;
    }
    else {
        LinkedNodeClass<T> *currNode = tail;
        theVal = currNode->getValue();
        // if there is only one element
        if (currNode->getPrev() == 0) {
            head = 0;
            tail = 0;
        }
        else {
            tail = currNode->getPrev();
            tail->setNextPointerToNull();
        }

        delete currNode;
        return true;
    }
}

// Returns the number of nodes contained in the list.
template <class T>
int SortedListClass<T>::getNumElems() const {
    int num = 0;
    LinkedNodeClass<T> *currNode = head;
    while (currNode != 0) {
        num++;
        currNode = currNode->getNext();
    }
    return num;
}

// Provides the value stored in the node at index provided in the
// 0-based "index" parameter. If the index is out of range, then outVal
// remains unchanged and false is returned. Otherwise, the function
// returns true, and the reference parameter outVal will contain
// a copy of the value at that location.
template <class T>
bool SortedListClass<T>::getElemAtIndex(const int index, T &outVal) const {
    if (head == 0 || index < 0) {
        return false;
    }
    int currIdx = 0;
    LinkedNodeClass<T> *currNode = head;
    
    while (currNode != 0) {
        if (currIdx == index) {
            outVal = currNode->getValue();
            return true;
        }
        // step in
        currIdx++;
        currNode = currNode->getNext();
    }

    // currNode touch tail before touching inout index
    return false;
}