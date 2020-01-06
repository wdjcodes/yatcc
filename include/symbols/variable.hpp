#ifndef __VARIABLE_HPP
#define __VARIABLE_HPP

namespace symbols {

class variable
{
private:
  /* data */
  const int stackBaseOffset;
  std::string name;
public:
  friend bool operator==(std::shared_ptr<variable>, std::string);
  int getStackBaseOffset();
  void print();
  variable(std::string, int);
  ~variable();
};

inline variable::variable(std::string n, int o)
        : stackBaseOffset(o)
{
    name = n;
}

inline bool operator==(std::shared_ptr<variable>v, std::string s){
    return !v->name.compare(s);
}

inline void variable::print(){
  std::cout << name;
}

inline int variable::getStackBaseOffset(){
  return stackBaseOffset;
}

inline variable::~variable()
{
}

}

#endif