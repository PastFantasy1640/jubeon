#pragma once
#include <string>
#include <iostream>

using namespace std;

namespace Jmemo2 {
enum class TokenType {
    COMMAND,
    IDENTIFIER,
    IDENTIFIER_EMPTY,
    LITERAL,
    EQUAL,
    DELIMITER,
    LABEL,
    NONE
};

enum class LiteralType {
    STRING,
    NUMBER
};

class Token {
public:
    typedef struct Position {
        int line;
        int pos;
        Position(): line(0), pos(0){};
        Position(int l, int p): line(l), pos(p){};
    } Position;
    Token(Position pos, TokenType type, wstring value)
        : _position(pos),
        _type(type),
        _value(value) {};
    
    Token()
        : _position(),
        _type(TokenType::NONE),
        _value(L"") {};

    TokenType getType() { return _type; };
    virtual wstring getValue() { return _value; };
    Position getPosition() { return _position; };
    bool is(TokenType type) { return (_type == type); };
private:
    TokenType _type;
    Position _position;
    wstring _value;
};

class Literal : public Token {
public:
    Literal() : Token(), _valueType(LiteralType::STRING) {};
    
    Literal(Token::Position pos, float value)
        : Token(pos, TokenType::LITERAL,to_wstring(value)),
        _valueType(LiteralType::NUMBER) {};
    
    Literal(Token::Position pos, wstring value)
        : Token(pos, TokenType::LITERAL, value),
        _valueType(LiteralType::STRING){};

    LiteralType getValueType() { return _valueType; };
private:
    LiteralType _valueType;
};
};