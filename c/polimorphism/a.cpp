#include<iostream>
#include<vector>
#include<cassert>
#include<memory>

using namespace std;

template <typename T>
void draw(const T& x, ostream& out, size_t pos){
  out << string(pos, ' ') << x << endl;
}

class Object{
  public:
    template <typename T>
    Object(T x) : self_(make_shared<model<T>>(move(x))) {};

    friend void draw(const Object& x, ostream& out, size_t pos){
      x.self_->draw_(out, pos);
    }

  private:
    struct Concept{
      virtual ~Concept() = default;
      virtual void draw_(ostream&, size_t) const = 0;
    };

    template <typename T>
    struct model final : Concept{
      model(T x) : data_(move(x)) {};
      void draw_(ostream& out, size_t pos) const override{
        draw(data_, out, pos);
      }

      T data_;
    };

    shared_ptr<const Concept> self_;
};

using Document = vector<Object>;

void draw(const Document& x, ostream& out, size_t pos){
  out << string(pos, ' ') << "<document>" << endl;

  for(const auto& e : x) 
    draw(e, out, pos + 2);

  out << string(pos, ' ') << "</document>" << endl;
}

using History = vector<Document>;

void commit(History& x){
  assert(x.size());
  x.push_back(x.back());
}

void undo(History& x){
  assert(x.size());
  x.pop_back();
}

Document& current(History& x){
  return x.back();
}

// http://sean-parent.stlab.cc/papers-and-presentations

struct Nothing{};
ostream& operator<<(ostream& out, const Nothing& n){
  return out << "NOTHING! " << &n;
}

int main(){
  History h(1);
  Nothing n1, n2;

  current(h).emplace_back(0);
  current(h).emplace_back(n1);
  current(h).emplace_back(n2);
  current(h).emplace_back(string("Hello"));
  draw(current(h), cout, 0);

  cout << "---------------------" << endl;

  current(h)[0] = 42.5;
  current(h)[1] = string("World");
  current(h).emplace_back(current(h));
  commit(h);

  draw(current(h), cout, 0);
  
  cout << "---------------------" << endl;

  undo(h);
  draw(current(h), cout, 0);
}
