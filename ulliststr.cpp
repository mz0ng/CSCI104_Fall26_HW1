#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
/**
 * Adds a new value to the back of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::push_back(const std::string& val) {
  //if tail is null, create new node
  if (tail_ == nullptr) {
    tail_ = new Item();
    head_ = tail_;
  }

  //check if there is space in the tail node
  if (tail_->last == ARRSIZE) {
    //if not, create new node
    Item* newItem = new Item();
    tail_->next = newItem;
    newItem->prev = tail_;
    tail_ = newItem;
  }

  //add value to back of node
  tail_->val[tail_->last] = val;
  tail_->last++;
  size_++;
}

/**
 * Removes a value from the back of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_back() {
  if (tail_ == nullptr) {
    return;
  }

  //pop back element
  tail_->val[tail_->last-1] = "";
  tail_->last--;
  size_--;

  //if node is now empty, delete node
  if (tail_->last == 0) {
    if (tail_->prev == nullptr) {
      delete tail_;
      tail_ = nullptr;
      head_ = nullptr;
      return;
    }
    tail_->prev->next = nullptr;
    Item* temp = tail_;
    tail_ = tail_->prev;
    delete temp;
  }
}

/**
 * Adds a new value to the front of the list.
 * If there is room before the 'first' value in
 * the head node add it there, otherwise, 
 * allocate a new head node.
 *   - MUST RUN in O(1)
 */
void ULListStr::push_front(const std::string& val) {
  //if head is null, create new node
  if (head_ == nullptr) {
    head_ = new Item();
    tail_ = head_;

    head_->first = ARRSIZE;
    head_->last = ARRSIZE;
  }

  //check if there is space in the head node
  if (head_->first == 0) {
    //if not, create new node
    Item* newItem = new Item();
    head_->prev = newItem;
    newItem->next = head_;
    head_ = newItem;

    head_->first = ARRSIZE;
    head_->last = ARRSIZE;
  }

  //add value to front of node
  head_->first--;
  head_->val[head_->first] = val;
  size_++;
}

/**
 * Removes a value from the front of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_front() {
  if (head_ == nullptr) {
    return;
  }

  //pop front element
  head_->val[head_->first] = "";
  head_->first++;
  size_--;

  //if node is now empty, delete node
  if (head_->first == ARRSIZE) {
    if (head_->next == nullptr) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
      return;
    }
    head_->next->prev = nullptr;
    Item* temp = head_;
    head_ = head_->next;
    delete temp;
  }
}

/**
 * Returns a const reference to the back element
 *   - MUST RUN in O(1)
 */
std::string const& ULListStr::back() const {
  return tail_->val[tail_->last-1];
}

/**
 * Returns a const reference to the front element
 *   - MUST RUN in O(1)
 */
std::string const& ULListStr::front() const {
  return head_->val[head_->first];
}

/** 
 * Returns a pointer to the item at index, loc,
 *  if loc is valid and NULL otherwise
 *   - MUST RUN in O(n) 
 */
std::string* ULListStr::getValAtLoc(size_t loc) const {
  //check if loc is valid
  if (loc < 0 || loc >= size_) {
    return nullptr;
  }

  //iterate through list until reaching loc
  //keep a pointer of our position in the list
  size_t count = 0;
  Item* curr = head_;
  int ptr = curr->first;
  while (true) {
    if (count == loc) {
      return &(curr->val[ptr]);
    }
    ptr++;
    if (ptr == ARRSIZE) {
      curr = curr->next;
      ptr = curr->first;
    }
    count++;
  }
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
