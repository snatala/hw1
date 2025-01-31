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
void ULListStr::push_back(const std::string& val){
  // if list is empty, create first node
  if(empty()){
    head_ = tail_ = new Item;
    tail_->val[0] = val;
    tail_->last = 1;
    size_++;
    return;
  }

  // If there's space in the current tail node's array
  if(tail_->last < ARRSIZE){
    tail_->val[tail_->last] = val;
    tail_->last++;
  } else { // if the tail array is full, create a new node
    Item* temp = new Item;
    temp->val[0] = val;
    temp->last = 1;
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
  }
  size_++;
}

void ULListStr::push_front(const std::string& val){
  // if list is empty, create first node
  if(empty()){
    head_ = tail_ = new Item;
    head_->val[0] = val;
    head_->last = 1;
    size_++;
    return;
  }
  // If there's space in the current head node's array
  if(head_->first > 0){
    head_->first--;
    head_->val[head_->first] = val;
  } else { // if the head array is full, create a new node
    Item* temp = new Item;
    temp->val[ARRSIZE-1] = val; //Place at the end of new array
    temp->first = ARRSIZE-1;
    temp->last = ARRSIZE;
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
  }
  size_++;
}

void ULListStr::pop_back(){
  if(empty()) {
    return;
  }

  //decrease the last index and size
  tail_->last--;
  size_--;

  // If node becomes empty after pop
  if(tail_->first == tail_->last) {
    Item* temp = tail_;
    if(head_ == tail_){
      head_ = tail_ = nullptr; //If this was the only node
    } else {
      tail_ = tail_->prev; //Update tail pointer
      tail_->next = nullptr;
    }
    delete temp;
  }
}

void ULListStr::pop_front() {
  if(empty()) {
    return;
  }
  // Increase first index and decrease size
  head_->first++;
  size_--;
  //If node becomes empty after pop
  if(head_->first == head_->last){
    Item* temp = head_;

    if(head_ == tail_){
      // If this was the only node
      head_ = tail_ = nullptr;
    } else {
      //Update head pointer
      head_ = head_->next;
      head_->prev = nullptr;
    }
    delete temp;
  }
}

//Reterns last element
std::string const & ULListStr::back() const {
  return tail_->val[tail_->last -1];
}

// Returns first element
std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  if(loc >= size_){ //Check if location is valid
    return nullptr;
  }

  Item* temp = head_;
  size_t itemSize;
  size_t cummulativeSize = 0;
  // Traverse nodes until we find the right location
  while(temp != nullptr) {
    itemSize = temp->last - temp->first;
    if(loc < cummulativeSize + itemSize) {
      return &temp->val[temp->first + (loc - cummulativeSize)];
      // Calculate exact array index and return pointer
    }
    cummulativeSize += itemSize;
    temp = temp->next;
  }
  return nullptr;
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
