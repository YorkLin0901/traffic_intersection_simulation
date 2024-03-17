// The ONLY constructor for the linked node class - it takes in the
// newly created node's previous pointer, value, and next pointer,
// and assigns them.
template <class T>
LinkedNodeClass<T>::LinkedNodeClass(
    LinkedNodeClass<T> *inPrev,  // Address of node that comes before this one 
    const T &inVal,              // Value to be contained in this node  
    LinkedNodeClass<T> *inNext) {// Address of node that comes after this one 
    prevNode = inPrev;
    nodeVal = inVal;
    nextNode = inNext;
}

// Returns the value stored within this node.
template <class T>
T LinkedNodeClass<T>::getValue() const {
    return nodeVal;
}

// Returns the address of the node that follows this node.
template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getNext() const {
    return nextNode;
}

// Returns the address of the node that comes before this node.
template <class T>
LinkedNodeClass<T>* LinkedNodeClass<T>::getPrev() const {
    return prevNode;
}

// Sets the object’s next node pointer to NULL.
template <class T>
void LinkedNodeClass<T>::setNextPointerToNull() {
    nextNode = 0;
}

// Sets the object's previous node pointer to NULL.
template <class T>
void LinkedNodeClass<T>::setPreviousPointerToNull() {
    prevNode = 0;
}

// This function DOES NOT modify "this" node. Instead, it uses
// the pointers contained within this node to change the previous
// and next nodes so that they point to this node appropriately.
// In other words, if "this" node is set up such that its prevNode
// pointer points to a node (call it "A"), and "this" node's
// nextNode pointer points to a node (call it "B"), then calling
// setBeforeAndAfterPointers results in the node we're calling
// "A" to be updated so its "nextNode" points to "this" node, and
// the node we're calling "B" is updated so its "prevNode" points
// to "this" node, but "this" node itself remains unchanged.
template <class T>
void LinkedNodeClass<T>::setBeforeAndAfterPointers() {
    if (prevNode != 0) { // if there is previous node
        prevNode->nextNode = this;
    }
    if (nextNode != 0) { // if there is next node
        nextNode->prevNode = this;
    }
}