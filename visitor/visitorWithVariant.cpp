

#include <functional>
#include <iostream>
#include <variant>
#include <vector>

struct ComponentA
{
  std::string specialFoo() const { return "Special A method"; }
};

struct ComponentB
{
  std::string specialBar() const { return "Special B method"; }
};

using Component = std::variant<ComponentA, ComponentB>;

struct ConcreteVisitorA
{
  void operator()(const ComponentA& a) const {
    std::cout << "a.specialFoo() called " << a.specialFoo() << "in visitor A\n";
  };
  void operator()(const ComponentB& b) const {
    std::cout << "b.specialBar() called " << b.specialBar() << "in visitor A\n";
  }
};

struct ConcreteVisitorB
{
  void operator()(const ComponentA& a) const {
    std::cout << "a.specialFoo() called " << a.specialFoo() << "in visitor B\n";
  };
  void operator()(const ComponentB& b) const {
    std::cout << "b.specialBar() called " << b.specialBar() << "in visitor B\n";
  }
};

using Visitor = std::variant<ConcreteVisitorA, ConcreteVisitorB>;

void useCase(const std::vector<Component>& components, const Visitor& v) {
  auto visitor = [&v](auto& c) { std::visit([&](auto& vconcrete) { vconcrete(c); }, v); };

  for (auto&& comp : components)
    std::visit(visitor, comp);
}

int main() {
  ComponentA ca;
  ComponentB cb;
  std::vector<Component> cvec;
  cvec.emplace_back(ca);
  cvec.emplace_back(cb);

  ConcreteVisitorA v1;

  useCase(cvec, v1);

  ConcreteVisitorB v2;
  useCase(cvec, v2);
}