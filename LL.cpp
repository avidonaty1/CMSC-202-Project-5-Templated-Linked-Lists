#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
    Node( const T& data ); //Node Constructor - Assume each quan
    pair<T,int>& GetData(); //Node Data Getter
    void SetData( const pair<T,int>& ); //Node Data Setter
    Node<T>* GetNext(); //Node m_next getter
    void SetNext( Node<T>* next ); //Node m_next setter
private:
    pair <T,int> m_data; //Holds templated data
    Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
    m_data = make_pair(data,1);
    m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
    return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
    m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
    return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
    m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
public:
    // Name: LL() (Linked List) - Default Constructor
    // Desc: Used to build a new linked list
    // Preconditions: None
    // Postconditions: Creates a new linked list where m_head points to nullptr
    LL();
    // Name: ~LL() - Destructor
    // Desc: Used to destruct a LL
    // Preconditions: There is an existing LL with at least one node
    // Postconditions: A LL is deallocated (including dynamically allocated nodes)
    //                 to have no memory leaks!
    ~LL();
    // Name: LL (Copy Constructor)
    // Desc: Creates a copy of existing LL
    //       Requires a LL - REQUIRED to be implemented even if not used
    // Preconditions: Source LL exists
    // Postconditions: Copy of source LL
    LL(const LL&);
    // Name: operator= (Overloaded Assignment Operator)
    // Desc: Makes two LL of the same type have identical number of nodes and values
    // Preconditions: Requires two linked lists of the same templated type
    //                REQUIRED to be implemented even if not used
    // Postconditions: Two idenetical LL
    LL<T>& operator= (const LL&);
    // Name: Find
    // Desc: Iterates through LL and returns node if data found
    // Preconditions: LL Populated
    // Postconditions: Returns nullptr if not found OR Node pointer if found
    Node<T>* Find(const T& data);
    // Name: Insert
    // Desc: Either inserts a node to the linked list OR increments frequency of first
    //       Takes in data. If "first" (of pair) NOT in list, adds node
    //       If "first" (of pair) is already in list, increments quantity
    //       Inserts "first" in order with no duplicates
    // Preconditions: Requires a LL.
    // Postconditions: Node inserted in LL based on first value (or quantity incremented)
    void Insert(const T&);
    // Name: RemoveAt
    // Desc: Removes a node at a particular position based on data passed (matches first)
    // Preconditions: LL with at least one node.
    // Postconditions: Removes first node with passed value (in first)
    void RemoveAt(const T&);
    // Name: Display
    // Desc: Display all nodes in linked list
    // Preconditions: Outputs the LL
    // Postconditions: Displays the pair in each node of LL
    void Display();
    // Name: GetSize
    // Desc: Returns the size of the LL
    // Preconditions: Requires a LL
    // Postconditions: Returns m_size
    int GetSize();
    // Name: operator<< (Overloaded << operator)
    // Desc: Returns the ostream of the data in each node
    // Preconditions: Requires a LL
    // Postconditions: Returns an ostream with the data from each node on different line
    template <class U>
    friend ostream& operator<<(ostream& output, const LL<U>&);
    // Name: Overloaded [] operator
    // Desc: When passed an integer, returns the data at that location
    // Precondition: Existing LL
    // Postcondition: Returns pair from LL using []
    pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL
private:
    Node <T> *m_head; //Node pointer for the head
    int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement LL here



// Name: LL() (Linked List) - Default Constructor
// Desc: Used to build a new linked list
// Preconditions: None
// Postconditions: Creates a new linked list where m_head points to nullptr
template <class T>
LL<T>::LL() {
    m_head = nullptr;
    m_size = 0;
}


// Name: ~LL() - Destructor
// Desc: Used to destruct a LL
// Preconditions: There is an existing LL with at least one node
// Postconditions: A LL is deallocated (including dynamically allocated nodes)
//                 to have no memory leaks!
template <class T>
LL<T>::~LL() {
    Node<T> *curr = m_head;   // sets current node to the front

    while (curr != nullptr) {
        curr = curr->GetNext();
        delete m_head;
        m_head = curr;
    }

    // resets head, tail, and size to original
    m_head = nullptr;
    m_size = 0;
}


// Name: LL (Copy Constructor)
// Desc: Creates a copy of existing LL
//       Requires a LL - REQUIRED to be implemented even if not used
// Preconditions: Source LL exists
// Postconditions: Copy of source LL
template <class T>
LL<T>::LL(const LL& myList) {

    // resets m_head and m_size to receive new data
    m_head = nullptr;
    m_size = 0;

    Node<T> *curr = myList.m_head;   // sets current node to the front of passed-in list

    // iterates through passed-in list and adds each element to new list
    while (curr != nullptr) {
        for (int i = 0; i < curr->GetData().second; i++) {
            this->Insert(curr->GetData().first);
        }
        curr = curr->GetNext();
    }
}


// Name: operator= (Overloaded Assignment Operator)
// Desc: Makes two LL of the same type have identical number of nodes and values
// Preconditions: Requires two linked lists of the same templated type
//                REQUIRED to be implemented even if not used
// Postconditions: Two idenetical LL
template <class T>
LL<T>& LL<T>::operator= (const LL& myList) {

    Node<T>* curr = m_head;

    // deletes contents of list
    if (&myList != this) {

        while (curr != nullptr) {
            curr = curr->GetNext();
            delete m_head;
            m_head = curr;
        }

        // resets values of "this"
        m_head = nullptr;
        m_size = 0;

        curr = myList.m_head;   // sets current node to the front

        // iterates through passed-in list and adds each element to new list
        while (curr != nullptr) {
            for (int i = 0; i < curr->GetData().second; i++) {
                this->Insert(curr->GetData().first);
            }
            curr = curr->GetNext();
        }
    }

    return *this;

}


// Name: Find
// Desc: Iterates through LL and returns node if data found
// Preconditions: LL Populated
// Postconditions: Returns nullptr if not found OR Node pointer if found
template <class T>
Node<T>* LL<T>::Find(const T& data) {

    Node<T>* curr = m_head;

    // if LL is empty
    if (curr == nullptr) {
        cout << "The linked list is empty" << endl;
        return nullptr;
    }
    else {
        // iterates through LL and returns node pointer with correct data or nullptr if not
        while (curr != nullptr) {
            if (curr->GetData().first == data) {
                return curr;
            }
            curr = curr->GetNext();
        }
        cout << "Here" << endl;
        // if iterates through and doesn't find data, returns nullptr
        return nullptr;
    }
}



// Name: Insert
// Desc: Either inserts a node to the linked list OR increments frequency of first
//       Takes in data. If "first" (of pair) NOT in list, adds node
//       If "first" (of pair) is already in list, increments quantity
//       Inserts "first" in order with no duplicates
// Preconditions: Requires a LL.
// Postconditions: Node inserted in LL based on first value (or quantity incremented)
template <class T>
void LL<T>::Insert(const T& data) {
    Node<T>* curr = m_head;
    Node<T>* temp = new Node<T>(data);
    temp->SetNext(nullptr);
    Node<T>* prev = curr;

    // if linked list is empty it sets temp to only pair in list
    if (m_head == nullptr) {
        m_head = temp;
        m_size++;
        return;
    }

    // if list size is one and temp's word is "greater than" element in list
    // it will add it second
    if (m_size == 1 and temp->GetData().first > m_head->GetData().first) {
        m_head->SetNext(temp);
        m_size++;
        return;
    }

    // if temp's word is "less than" first word in list it adds it first
    if (temp->GetData().first < m_head->GetData().first) {
        temp->SetNext(m_head);
        m_head = temp;
        m_size++;
        return;
    }

    // iterates through loop. if any word matches temp's word it increments quantity
    // and deletes temp
    while (curr != nullptr) {
        if (curr->GetData().first == data) {
            curr->GetData().second++;
            delete temp;
            temp = nullptr;
            return;
        }

        // first time temp's word is "greater than" curr's word it inserts
        // temp's word between prev and curr
        else if (curr->GetData().first > temp->GetData().first) {
            prev->SetNext(temp);
            temp->SetNext(curr);
            m_size++;
            return;
        }

        // if we're at end of list and no word matches it puts temp's word last
        else if (curr->GetNext() == nullptr) {
            curr->SetNext(temp);
            m_size++;
            return;
        }

        // moves prev and curr up
        else {
            prev = curr;
            curr = curr->GetNext();
        }

    }

}


// Name: RemoveAt
// Desc: Removes a node at a particular position based on data passed (matches first)
// Preconditions: LL with at least one node.
// Postconditions: Removes first node with passed value (in first)
template <class T>
void LL<T>::RemoveAt(const T& place) {
    Node<T>* curr = m_head;
    Node<T>* prev = m_head;


    // if list is empty
    if (curr == nullptr) {
        cout << "Linked list is empty" << endl;
    }
    else {
        // iterates through until gets to correct node then deletes node
        while (curr != nullptr) {

            // if first node in list has same key as place
            if (place == (*this)[0].first) {
                prev = m_head->GetNext();
                delete m_head;
                m_head = prev;
                m_size--;
                curr = nullptr;
            }

            // deletes node with same word in data key
            else if (curr->GetData().first == place) {
                prev->SetNext(curr->GetNext());
                delete curr;
                curr = nullptr;
                m_size--;
            }
            else {
                prev = curr;
                curr = curr->GetNext();
            }
        }
    }
}


// Name: Display
// Desc: Display all nodes in linked list
// Preconditions: Outputs the LL
// Postconditions: Displays the pair in each node of LL
template <class T>
void LL<T>::Display() {
    Node<T>* curr = m_head;

    // condition for if list is empty
    if (curr == nullptr) {
        cout << "List is empty" <<endl;
    }
    else {
        // iterates through LL and prints each pair
        while (curr != nullptr) {
            cout << curr->GetData().first << ": " << curr->GetData().second << endl;
            curr = curr->GetNext();
        }
    }
}


// Name: GetSize
// Desc: Returns the size of the LL
// Preconditions: Requires a LL
// Postconditions: Returns m_size
template <class T>
int LL<T>::GetSize() {
    return m_size;
}


// Name: operator<< (Overloaded << operator)
// Desc: Returns the ostream of the data in each node
// Preconditions: Requires a LL
// Postconditions: Returns an ostream with the data from each node on different line
template <class U>
ostream& operator<<(ostream& output, const LL<U>& myList) {
    Node<U>* curr = myList.m_head;

    // iterates through and prints out both halves of each node's data pair
    while (curr != nullptr) {
        output << curr->GetData().first << ": " << curr->GetData().second << endl;
        curr = curr->GetNext();
    }
    return output;
}


// Name: Overloaded [] operator
// Desc: When passed an integer, returns the data at that location
// Precondition: Existing LL
// Postcondition: Returns pair from LL using []
template <class T>
pair<T,int>& LL<T>::operator[] (int x) {   //Overloaded [] operator to pull data from LL
    int count = 0;  // how many time iterated through the list

    Node<T>* curr = m_head;

    while (curr != nullptr) {
        if (count == x) {
            return curr->GetData();
        }
        else {
            count++;
            curr = curr->GetNext();
        }
    }

    // this will never get returned. just returning this to prevent warning
    return m_head->GetData();
}

