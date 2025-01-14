

#include <iostream>
#include <vector>

struct ComponentA;
struct ComponentB;

struct Visitor
{
  virtual ~Visitor(){}
  virtual void visit(const ComponentA& a) const = 0;
  virtual void visit(const ComponentB& a) const = 0;
};


struct Component{
  virtual ~Component(){}
  virtual void accept(Visitor& v) const =0;
};

struct ComponentA:Component{
   void accept(Visitor& v) const override
   {
     v.visit(*this);
   };


   std::string specialFoo() const
   {
     return "Special A method";
   }
};

struct ComponentB:Component{
  void accept(Visitor& v) const override
  {
    v.visit(*this);
  };


  std::string specialBar() const
  {
    return "Special B method";
  }
};



struct ConcreteVisitorA: Visitor
{
   void visit(const ComponentA& a) const override
   {
     std::cout<<"a.specialFoo() called "<< a.specialFoo()<<"in visitor A\n";
   };
   void visit(const ComponentB& b) const override
   {
     std::cout<<"b.specialBar() called "<< b.specialBar()<<"in visitor A\n";

   }
};

struct ConcreteVisitorB: Visitor
{
  void visit(const ComponentA& a) const override
  {
    std::cout<<"a.specialFoo() called "<< a.specialFoo()<<"in visitor B\n";
  };
  void visit(const ComponentB& b) const override
  {
    std::cout<<"b.specialBar() called "<< b.specialBar()<<"in visitor B\n";

  }
};


void useCase(const std::vector<const Component* >& components, Visitor& v)
{
  for (auto&& comp: components)
  {
    comp->accept(v);
  }
}


int main()
{
  ComponentA ca;
  ComponentB cb;

  ConcreteVisitorA v1;
  useCase({&ca,&cb},v1);

  ConcreteVisitorB v2;
  useCase({&ca,&cb},v2);
}