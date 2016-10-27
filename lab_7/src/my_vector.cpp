#include "my_vector.h"
  MyVector::MyVector(){
  _cp=2;
  _sz=0;
  _data=new int[2];
}
  MyVector::MyVector(std::size_t init_capacity){
  _cp=init_capacity;
  _sz=0;
  _data=new int[_cp];
}
  MyVector::~MyVector(){
   delete []_data;
}

  void MyVector::set(std::size_t index, int value){
    _data[index]=value;
}
  int MyVector::get(std::size_t index){
    return _data[index];
}

  std::size_t MyVector::size(){
    return _sz;
}
  std::size_t MyVector::capacity(){
   return _cp;
}
  void MyVector::reserve(std::size_t new_capacity){
   int *b=new int[new_capacity];
   for(size_t i=0;i<=_sz;i++){
   b[i]=_data[i];
   }
   delete []_data;
   _data=b;
}
  void MyVector::resize(std::size_t new_size){
    while(_cp<new_size)
       _cp*=2;
    int *b=new int[_cp];
    for(size_t i=0;i<_sz;i++){
       b[i]=_data[i];
    }
    for(size_t i=_sz;i<_cp;i++)
       b[i]=0;
    delete []_data;
    _data=b;
    _sz=_cp;
} 
  void MyVector::push_back(int value){
    if(_sz+1>=_cp){
        _cp*=2;
    int *b=new int[_cp];
    for(size_t i=0;i<_sz;i++){
    b[i]=_data[i];
    }
    delete []_data;
    _data=b;
    }
    _data[_sz]=value;
    _sz++;
}
  void MyVector::insert(std::size_t index, int value){
    if(_sz+1>=_cp){
      _cp*=2;
    int *b=new int[_cp];
    for(size_t i=0;i<_sz;i++){
      b[i]=_data[i];
    }
    delete []_data;
    _data=b;
    }
    _sz++;
    for(size_t i=_sz;i>index;i--){
    _data[i]=_data[i-1];
    }
    _data[index]=value;
}
  void MyVector::erase(std::size_t index){
   _sz--; 
   for(size_t i=index;i<_sz;i++){
      _data[i]=_data[i+1];
}
}
