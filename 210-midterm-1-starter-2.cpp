#include <iostream>   //includes the standard input/output stream library
using namespace std;  // allows use of standard library names

// constants used for list generation/validation
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// DoublyLinkedList() intializes an empty doubly linked list
// arguments: none
// returns: nothing
class DoublyLinkedList {
 private:
  struct Node {
    int data;    // Stores integer value of the node
    Node* prev;  // Pointer to the previous node in the list
    Node* next;  // Pointer to the next node in the list

    // Constructor that initializes nod with valu and prev/next pointers
    Node(int val, Node* p = nullptr, Node* n = nullptr) {
      data = val;
      prev = p;
      next = n;
    }
  };

  Node* head;  // points to the first node in the list
  Node* tail;  // points to the last node in the list

 public:
  // constructor initializes an empty list
  DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
  }

  // insert_after() inserts a node with the given value after the specified
  // position
  // arguments: int value, int position
  // returns: nothing
  void insert_after(int value, int position) {
    if (position < 0) {  // checks if the position is out of bounds
      cout << "Position must be >= 0." << endl;
      return;
    }

    Node* newNode = new Node(value);  // creates a new node
    if (!head) {  // checks if the list is empty aka head does not point to
                  // anything and is null
      head = tail = newNode;  // then set head and tail to th new node
      return;
    }

    Node* temp = head;  // temporary node pointer to head
    for (int i = 0; i < position && temp;
         ++i)  // traverses the list between the position and the temp
      temp = temp->next;

    if (!temp) {  // If position
      cout << "Position exceeds list size. Node not inserted.\n";
      delete newNode;
      return;
    }

    // link the new nod into the list
    newNode->next = temp->next;    // point newmode to temp's next
    newNode->prev = temp;          // point newnode back to temp
    if (temp->next)                // if temp isn't the last node
      temp->next->prev = newNode;  // fix the back link of the next node
    else
      tail = newNode;      // if temp was the last node, update tail
    temp->next = newNode;  // link temp forward to newnode
  }

  void delete_val(int value) {
    if (!head) return;  // if list is empty, exit

    Node* temp = head;  // start from the head

    // look for the node with the matching valuee
    while (temp && temp->data != value) temp = temp->next;

    if (!temp) return;  // value not found

    // fix the previous node's next pointer
    if (temp->prev)
      temp->prev->next = temp->next;
    else
      head = temp->next;

    // fix the next node's prev pointer
    if (temp->next)
      temp->next->prev = temp->prev;
    else
      tail = temp->prev;  // if we're deleting the tail, move tail back

    delete temp;  // free the memory for the deleted node
  }
  // delete_pos() deletes the node at the specified position
  // arguments: int p
  // returns: nothing
  void delete_pos(int pos) {
    if (!head) {
      cout << "List is empty." << endl;
      return;
    }

    if (pos == 1) {
      pop_front();
      return;
    }

    Node* temp = head;

    for (int i = 1; i < pos; i++) {
      if (!temp) {
        cout << "Position doesn't exist." << endl;
        return;
      } else
        temp = temp->next;
    }
    if (!temp) {
      cout << "Position doesn't exist." << endl;
      return;
    }

    if (!temp->next) {
      pop_back();
      return;
    }

    Node* tempPrev = temp->prev;
    tempPrev->next = temp->next;
    temp->next->prev = tempPrev;
    delete temp;
  }
  // push_back() appends an element to the list's tail
  // arguments: int v
  // returns: nothing
  void push_back(int v) {
    Node* newNode = new Node(v);
    if (!tail)
      head = tail = newNode;
    else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
  }

  // push_front() adds a node with the given value to the front of the list
  // arguments: int value
  // returns: nothing
  void push_front(int v) {
    Node* newNode = new Node(v);
    if (!head)
      head = tail = newNode;
    else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
  }

  void pop_front() {
    if (!head) {  // if head is null aka the list is empty
      cout << "List is empty." << endl;
      return;
    }

    Node* temp = head;

    if (head->next) {
      head = head->next;
      head->prev = nullptr;
    } else
      head = tail = nullptr;
    delete temp;
  }

  void pop_back() {
    if (!tail) {  // if tail is null aka the list is empty
      cout << "List is empty." << endl;
      return;
    }
    Node* temp = tail;

    if (tail->prev) {
      tail = tail->prev;
      tail->next = nullptr;
    } else
      head = tail = nullptr;
    delete temp;
  }
  // Destructor used to deallocate the dynamically-allocated memory used by the
  // linked list
  ~DoublyLinkedList() {
    while (head) {        // while head is not null
      Node* temp = head;  // we store the current node in temp
      head = head->next;  // then we set head to the next node
      delete temp;        // delete the previous head's node
    }
  }

  // print() displays the list from head to tail
  // arguments: none
  // returns: nothing
  void print() {
    Node* current = head;
    if (!current) {
      cout << "List is empty." << endl;
      return;
    }
    while (current) {
      cout << current->data << " ";
      current = current->next;
    }
    cout << endl;
  }
  // print_reverse() displays the list from tail to head
  // arguments: none
  // returns: nothing
  void print_reverse() {
    Node* current = tail;  // sets the pointer current to the node's tail
    if (!current) {        // if current is null aka the list is empty
      cout
          << "List is empty."
          << endl;  // output that the list is empty and end the line after that
      return;  // stops the print_reverse() from running further and returns
    }
    while (current) {  // then if current is not null and the list does exist
      cout << current->data
           << " ";  // output whatever data that current is pointing to
      current =
          current
              ->prev;  // then set the pointer to the previous node in the list
    }
    cout << endl;  // once the loop is done meaning we've reached the beginning
                   // of the loop and there is nothing more to output, end the
                   // line to signify the end of the while loop
  }

  // every_other_element() outputs the every other data structure in the list
  // starting with the first element (outputs first, skips second, outputs
  // third, etc.) arguments: none returns: nothing
  void every_other_element() {
    Node* current = head;  // set a pointer called current to the node's head
    bool print = true;     // set a bool for when to print and not print

    if (!current) {  // if current is null aka the list is empty
      cout
          << "List is empty."
          << endl;  // output that the list is empty and end the line after that
      return;  // stops the print_reverse() from running further and returns
    }

    while (current) {                  // while current points to a node's head
      if (print) {                     // if print is true
        cout << current->data << " ";  // output the current's data
      }
      current = current->next;  // set current to the next node
      print = !print;  // switch whatever prints current condition is, this
                       // allows us to alternate between printing and not
                       // printing for each element
    }
    cout << endl;
  }
};

int main() {
  // cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid
  // compiler warning

  DoublyLinkedList list;

  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);

  list.print();

  list.every_other_element();

  return 0;
}