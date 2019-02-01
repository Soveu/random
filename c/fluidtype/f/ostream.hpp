#pragma once

#include "fluid.hpp"

std::ostream& operator<<(std::ostream& out, const Fluid::Object& obj);
std::ostream& operator<<(std::ostream& out, const Fluid::Array& arr);

std::ostream& operator<<(std::ostream& out, Fluid::Undefined){
  return out << "undefined";
}

std::ostream& operator<<(std::ostream& out, const Fluid::Boolean& b){
  return out << (b ? "true" : "false");
}

std::ostream& operator<<(std::ostream& out, const Fluid::Function& f){
  return out << "<function>";
}

std::ostream& operator<<(std::ostream& out, const Fluid& f){
  switch(f.type()){
    case Fluid::Type::Undefined:
      out << Fluid::Undefined{}; 
      break;
    case Fluid::Type::Boolean:
      out << ( std::get<Fluid::Boolean>(f.value) ? "true" : "false" ); 
      break;
    case Fluid::Type::Number:
      out << std::get<Fluid::Number>(f.value); 
      break;
    case Fluid::Type::String:
      out << "\"" << std::get<Fluid::String>(f.value) << "\""; 
      break;
    case Fluid::Type::Array:
      out << std::get<Fluid::Array>(f.value); 
      break;
    case Fluid::Type::Object:
      out << std::get<Fluid::Object>(f.value); 
      break;
    case Fluid::Type::Function:
      out << std::get<Fluid::Function>(f.value);
      break;
  }

  return out;
}

std::ostream& operator<<(std::ostream& out, const Fluid::Array& arr){
  out << '[';

  for(auto& item : arr){
    out << item << ", ";
  }

  return out << ']';
}

std::ostream& operator<<(std::ostream& out, const Fluid::Object& obj){
  out << '{';

  for(auto& kv : obj){
    out << '"' << kv.first << "\": " << kv.second << ", ";
  }

  return out << '}';
}


