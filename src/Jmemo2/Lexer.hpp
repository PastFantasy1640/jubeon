#pragma once

#include <string>
#include <vector>
#include <iterator>
#include <type_traits>
#include <memory>
#include "Token.hpp"

using namespace std;
namespace Jmemo2 {
template<typename T>
struct IsTokenType
    : std::conditional<
      std::is_same<T, TokenType>::value,
      std::true_type,
      std::false_type>::type {};

typedef struct MatchResult {
    int backTrackTo;
    vector<shared_ptr<Token>> tokens;
    MatchResult() : backTrackTo(-1) {};
} MatchResult;

class Lexer {
public:
    Lexer() : _input(L""), _hasError(false), _curTokenIndex(0), _reachedTheEnd(false){};
    
    bool initWithString(wstring input);
    bool hasError() { return _hasError; };

    template<typename T, typename ... Types> 
    bool matchOrBack(MatchResult &matchResult, T head, Types ...args) {
        static_assert(Lexer::checkTypes(IsTokenType<T>::value) && Lexer::checkTypes(IsTokenType<Types>::value...), "args should be TokenType");
        if (matchResult.backTrackTo < 0) {
            matchResult.backTrackTo = _curTokenIndex;
        }
        bool res = matchOrBack(matchResult, head) && matchOrBack(matchResult, args...);
        return res;
    };

    bool matchOrBack(MatchResult &matchResult, TokenType a) {
        if (matchResult.backTrackTo < 0) {
            matchResult.backTrackTo = _curTokenIndex;
        }
        shared_ptr<Token> token = nextToken();
        if (token && token->getType() == a) {
            matchResult.tokens.push_back(token);
            return true;
        } else {
            backTrack(matchResult.backTrackTo);
            return false;
        }
    }
    bool repeatOrBack(MatchResult &matchRes, TokenType a, int minTime, bool exact) {
        while (true) {
            if (!matchOrBack(matchRes, a)) {
                break;
            } else {
                matchRes.backTrackTo++;
            }
        }
        
        if (exact) {
            return (matchRes.tokens.size() == minTime);
        } else {
            return (matchRes.tokens.size() >= minTime);
        }
    };

    shared_ptr<Token> nextToken() {
        if (_curTokenIndex + 1 >= _tokens.size()) {
			_reachedTheEnd = true;
            return nullptr;
        } else {
            return _tokens[_curTokenIndex++];
        }
    }

    shared_ptr<Token> curToken() {
		if (_reachedTheEnd) {
			return nullptr;
		}
		return _tokens[_curTokenIndex];
    }

    int getCurTokenIndex() { return _curTokenIndex; };
    void backTrack(unsigned int i) {
        if (i < _tokens.size()) {
            _curTokenIndex = i;
        }
    }
private:

    template<typename ... Types>
    constexpr static bool checkTypes(bool b, Types ... rest) {
        return b && checkTypes(rest...);
    }

    constexpr static bool checkTypes(bool b) {
        return b;
    }


    wstring _input;
    vector<shared_ptr<Token>> _tokens;
	bool _reachedTheEnd;
    bool _hasError;
    unsigned int _curTokenIndex;
};
};
