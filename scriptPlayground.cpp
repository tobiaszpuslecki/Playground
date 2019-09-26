//Playground - noun: a place where people can play

#include <iostream>
#include <map>
using namespace std;

typedef map<string, int> Memory;





class Expression
{
public:
  virtual int eval(Memory& m) = 0;
  virtual ~Expression() {}
};

class Constant : public Expression
{
public:
  int value;

  Constant(int v) : value(v){}

  virtual int eval(Memory& m)
  {
    return value;
  }
};


class BinaryOperation : public Expression
{
public:
  char symbol;
  Expression* left;
  Expression* right;

  BinaryOperation(char s, Expression* l, Expression* r) : symbol(s), left(l), right(r) {}

  virtual int eval(Memory& m)
  {
    switch (symbol)
    {
      case '+': return left->eval(m) + right->eval(m);
      // other ops

    }
  }

  virtual ~BinaryOperation()
  {
    delete left;
    delete right;
  }
};

class VariableNotFound {};

class Variable : public Expression
{
public:
  string name;

  Variable(string n) : name(n) {}

  virtual int eval(Memory& m)
  {
    Memory::iterator it = m.find(name);
    if (it == m.end())
      throw VariableNotFound();
    return it->second;
  }

};


class NotParsed {};

class Parser
{
  string input;
  size_t position;

public:

  Parser(string input);

  void skipWhitespace();

  char lookAhead();

  Expression* parseExpression();

  Expression* parseSum();
  Expression* parseMult();
  Expression* parseTerm();
  Expression* parseConstant();
  Expression* parseVariable();
  Expression* parseParenthesis();

};

const char EOS = '\0';

Parser::Parser(string input) : input(input), position(0)
{
  input.push_back(EOS);
}

void Parser::skipWhitespace()
{
  while(isspace(input[position])) position++;
}

char Parser::lookAhead()
{
  skipWhitespace();
  return input[position];
}

Expression* Parser::parseExpression()
{
  Expression* e = parseSum();
  if (lookAhead() == EOS)
    return e;
  else
  {
    delete e;
    throw NotParsed();
  }
}

Expression* Parser::parseSum()
{
  Expression* e = NULL;

try{
  e = parseMult();

  char c = lookAhead();

  while (c == '+' || c == '-')
  {
    position++;
    e = new BinaryOperation(c, e , parseMult());
    c = lookAhead();
  }
}catch (NotParsed)
{
  delete e;
  throw NotParsed();
}

  return e;
}

Expression* Parser::parseMult()
{
  Expression* e = NULL;

try{
  e = parseTerm();
  char c = lookAhead();

  while (c == '*' || c == '/' || c == '%')
  {
    position++;
    e = new BinaryOperation(c, e, parseTerm());
    c = lookAhead();
  }
}catch (NotParsed){
  delete e;
  throw NotParsed();
}
  return e;
}

Expression* Parser::parseTerm()
{
  char c = lookAhead();

  if (isdigit(c))
    return parseConstant();
  else if(isalpha(c))
    return parseVariable();
  else if(c == '(')
    return parseParenthesis();
  else
    throw NotParsed();
}

Expression* Parser::parseConstant()
{
  int n = 0;
  while (isdigit(input[position]))
  {
    n*=10;
    n+=input[position] - '0';
    position++;
  }
  return new Constant(n);
}

Expression* Parser::parseVariable()
{
  string s = "";

  while(isalpha(input[position]))
  {
    s.push_back(input[position]);
    position++;
  }
  return new Variable(s);
}

Expression* Parser::parseParenthesis()
{
  position++;

  Expression* e = parseSum();

  if(lookAhead()==')')
  {
    position++;
    return e;
  }
  else
  {
    delete e;
    throw NotParsed();
  }
}



int main(int argc, char const *argv[])
{
  /* code */
  return 0;
}
