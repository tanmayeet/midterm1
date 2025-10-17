#include <iostream>   //includes the standard input/output stream library
using namespace std;  // includes

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
    Node(int val, Node* p = nullptr, Node* n = nullptr) {
      data = val;
      prev = p;
      next = n;
    }
  };

  Node* head;
  Node* tail;

 public:
  DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
  }

  void insert_after(int value, int position) {
    if (position < 0) {
      cout << "Position must be >= 0." << endl;
      return;
    }

    Node* newNode = new Node(value);
    if (!head) {
      head = tail = newNode;
      return;
    }

    Node* temp = head;
    for (int i = 0; i < position && temp; ++i) temp = temp->next;

    if (!temp) {
      cout << "Position exceeds list size. Node not inserted.\n";
      delete newNode;
      return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next)
      temp->next->prev = newNode;
    else
      tail = newNode;
    temp->next = newNode;
  }

  void delete_val(int value) {
    if (!head) return;

    Node* temp = head;

    while (temp && temp->data != value) temp = temp->next;

    if (!temp) return;

    if (temp->prev)
      temp->prev->next = temp->next;
    else
      head = temp->next;

    if (temp->next)
      temp->next->prev = temp->prev;
    else
      tail = temp->prev;

    delete temp;
  }

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
    if (!head) {
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
    if (!tail) {
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
  //
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

  void every_other_element() {
    Node* current = head;
    bool print = true;

    if (!current) {  // if current is null aka the list is empty
      cout
          << "List is empty."
          << endl;  // output that the list is empty and end the line after that
      return;  // stops the print_reverse() from running further and returns
    }

    while (current) {
      if (print) {
        cout << current->data << " ";
      }
      current = current->next;
      print = !print;
    }

    cout << endl;
  }
};

int main() {
  cout << MIN_NR + MIN_LS + MAX_NR +
              MAX_LS;  // dummy statement to avoid compiler warning
  return 0;
}