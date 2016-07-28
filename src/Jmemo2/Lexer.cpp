#include "Lexer.hpp"

#include <codecvt>
#include <iostream>
#include <locale>
#include <regex>
#include <wchar.h>
#include <iterator>
#include <sstream>
#include <memory>
#include "Token.hpp"

using namespace std;

namespace Jmemo2 {

bool Lexer::initWithString(wstring input) {
    _input = input;
    wstringstream inputStream(_input);
    wstring line;

    bool isPreamble = true;
    for(int i = 0; (getline(inputStream, line) && !_hasError); i++) {
        auto it = line.begin();
        auto itEnd = line.end();
        if (line.size() <= 0) {
            continue;
        }

        // 行の最初の文字が"1-0"または"x"だった場合、譜面行として字句解析を行う
        if (isPreamble) {
            wstring firstStr = line.substr(0, 1);
            bool isnum = regex_match(firstStr, wregex(L"[1-9a-g]"));
            isPreamble = !(isnum || firstStr == L"x");
        }
        
        while (it != itEnd) {
            if (*(it) == L' ') {
                advance(it, 1);
            } else if (*it == L'#') {
                // "#"から始まる場合、コマンドであると推測する
                match_results<wstring::iterator> match;
                wregex re(L"^#[0-9a-zA-Z]*");
                regex_search(it, itEnd, match, re);
                wstring commandName = match.str();

                // コマンド名が空の場合エラー
                if (commandName.size() <= 0) {
                    _hasError = true;
                    break;
                } else {
                    // コマンド名から#を取り除く
                    commandName = commandName.substr(1, commandName.size() - 1);

                    Token::Position tokenPos(i, distance(line.begin(), it));
                    shared_ptr<Token> token(
                        new Token(tokenPos, TokenType::COMMAND, commandName));
                    _tokens.push_back(token);
                    advance(it, commandName.size() + 1);
                }
            } else if (iswdigit(*it) != 0) {
                wregex re(L"^[0-9]+");
                match_results<wstring::iterator> match;
                regex_search(it, itEnd, match, re);
                wstring number = match.str();

                Token::Position tokenPos(i, distance(line.begin(), it));
                if (!isPreamble) {
                    // 4 is panel size
                    if (line.size() == number.size() && line.size() < 4) {
                        shared_ptr<Token> token(
                            new Token(tokenPos, TokenType::LABEL, number));
                        _tokens.push_back(token);
                        advance(it, number.size());
                    } else {
                        wstring str = wstring(&*it, 1);
                        shared_ptr<Token> token(
                            new Token(tokenPos, TokenType::IDENTIFIER, str));
                        _tokens.push_back(static_pointer_cast<Token>(token));
                        advance(it, 1);
                    }
                } else {
                    shared_ptr<Literal> literal(
                        new Literal(tokenPos, stof(number)));
                    _tokens.push_back(static_pointer_cast<Token>(literal));
                    advance(it, number.size());
                }
            } else if (regex_match(wstring(&*it, 1), wregex(L"[a-zA-Z0-9-_]"))){
                Token::Position tokenPos(i, distance(line.begin(), it));
                if (((*it) == L'-' || ((*it)) == L'x') && !isPreamble) {
                    wstring str(&*it, 1);
                    shared_ptr<Token> token(
                        new Token(tokenPos, TokenType::IDENTIFIER, str));
                    _tokens.push_back(token);
                    advance(it, 1);
                } else if (regex_match(wstring(&*it, 1), wregex(L"[a-g]")) && !isPreamble) {
                    wstring str(&*it, 1);
                    shared_ptr<Token> token(
                        new Token(tokenPos, TokenType::IDENTIFIER, str));
                    _tokens.push_back(token);
                    advance(it, 1);
                } else {
                    wregex re(L"^[a-zA-Z0-9_]+");
                    match_results<wstring::iterator> match;
                    regex_search(it, itEnd, match, re);
                    wstring identVal = match.str();
                    shared_ptr<Token> token(
                        new Token(tokenPos, TokenType::IDENTIFIER, identVal));
                    _tokens.push_back(token);
                    advance(it, identVal.size());
                }
            } else if (*it == L'"') {
                match_results<wstring::iterator> match;
                wregex re(L"^\"(.+)\"");
                regex_search(it, itEnd, match, re);
                wstring stringVal = match.str(1);
                Token::Position tokenPos(i, distance(line.begin(), it));
                Token token(tokenPos, TokenType::LITERAL, stringVal);
                shared_ptr<Literal> literal(
                    new Literal(tokenPos, stringVal));
                _tokens.push_back(static_pointer_cast<Token>(literal));
                advance(it, stringVal.size() + 2);
            } else if (*(it) == L'=') {
                // 代入演算子
                Token::Position tokenPos(i, distance(line.begin(), it));
                shared_ptr<Token> token(
                    new Token(tokenPos, TokenType::EQUAL, L"="));
                _tokens.push_back(token);
                advance(it, 1);
            } else if (*it == L'|') {
                Token::Position tokenPos(i, distance(line.begin(), it));
                shared_ptr<Token> token(
                    new Token(tokenPos, TokenType::DELIMITER, L"|"));
                _tokens.push_back(token);
                advance(it, 1);
            } else {
                _hasError = true;
                break;
            }
        }

    }

    return _hasError;
};
};