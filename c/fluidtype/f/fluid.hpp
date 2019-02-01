#pragma once

#include<iostream>
#include<variant>
#include<string>
#include<functional>
#include<vector>
#include<map>

struct Fluid{
  enum class Type{
    Undefined,
    Boolean,
    Number,
    String,
    Array,
    Object,
    Function
  };

  struct Undefined{};
  using Boolean   = bool;
  using Number    = double;
  using String    = std::basic_string<char>;
  using Array     = std::vector<Fluid>;
  using Object    = std::map<std::string, Fluid>;
  using Function  = std::function<Fluid(Fluid)>;

  std::variant<Undefined, Boolean, Number, String, Array, Object, Function> value;

  constexpr inline auto type() const noexcept{
    return static_cast<Type>(value.index());
  }

  Fluid(const char* c) : value{String(c)} {};
  Fluid() : value{Undefined{}} {};

  template<typename T>
  Fluid(const T& x) : value{x} {};

  template<typename T>
  Fluid& push(const T& f){
    return std::get<Array>(value).emplace_back(Fluid{f});
  }

  Fluid pop(){
    auto& arr = std::get<Array>(value);
    Fluid res = arr.back();
    arr.pop_back();

    return res;
  }

  Fluid& operator[](const std::size_t s){
    return std::get<Array>(value)[s];
  }

  Fluid& operator[](const std::string& s){
    return std::get<Object>(value)[s];
  }

  Fluid operator()() const{
    return std::get<Function>(value)(Undefined{});
  }

  Fluid operator()(Fluid a) const{
    return std::get<Function>(value)(a);
  }
};

