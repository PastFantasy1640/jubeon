#include "Parser.hpp"
#include <iostream>
#include <fstream>
#include <functional>
#include <locale>
#include <codecvt>
#include <vector>
#include <string>
#include <wchar.h>
#include <regex>
#include <unordered_map>
#include <random>
#include "Lexer.hpp"
#include "Token.hpp"

using namespace std;
namespace Jmemo2 {
void Parser::initWithString(string source) {
    // utf8 -> wstringへの変換器
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> cv;
    
    // Lexerの初期化
    _lexer.initWithString(cv.from_bytes(source));
    
    // 構文解析
    while(true) {
        shared_ptr<Token> curToken = _lexer.curToken();
        if (curToken == nullptr) {
            break;
		}
        if (_state.isPreamble) {
            bool matched = false;
            if (curToken->is(TokenType::IDENTIFIER)) {
                matched = parseAssign();
            } else if (curToken->is(TokenType::COMMAND)) {
                matched = parseCommand();
            }
            _state.isPreamble = matched;
        } else if (curToken->is(TokenType::LABEL)) {
            parseLabel();
        } else if (curToken->is(TokenType::IDENTIFIER)) {
            if (!parseAssign() && !parseMusic()) {
                break;
			}
        }
    }
    flushBuffer();
};

void Parser::initWithFileName(string filename) {
    ifstream ifs(filename);
    istreambuf_iterator<char> iter(ifs), iter_end;
    initWithString(string(iter, iter_end));
};
bool Parser::parseLabel() {
    MatchResult matchRes;
    return _lexer.matchOrBack(matchRes, TokenType::LABEL);
};

bool Parser::parseMusic() {
    MatchResult matchPlacement;

    // 配置定義
    bool isPlacement = _lexer.matchOrBack(
            matchPlacement,
            TokenType::IDENTIFIER,
            TokenType::IDENTIFIER,
            TokenType::IDENTIFIER,
            TokenType::IDENTIFIER);
    if (!isPlacement) {
        return false;
    }

    // リズム定義
    auto isDelimitorFunc = [this] (MatchResult matchRes){
        bool res =  _lexer.matchOrBack(matchRes, TokenType::DELIMITER);
        return res;
    };
    bool isRhythm = true;
    MatchResult matchRhythm;
    if(!isDelimitorFunc(matchRhythm)
        || !_lexer.repeatOrBack(matchRhythm, TokenType::IDENTIFIER, 4, false)
        || !isDelimitorFunc(matchRhythm)) {
        isRhythm = false;
    }

    if (isRhythm) {
        float currentBpm = static_cast<float>(_music.bpmChanges.back().second);
        
        // 時間の単位はミリ秒で統一する
        int timePerUnit = 60 * 1000 / currentBpm / (matchRhythm.tokens.size());
        for(auto token : matchRhythm.tokens) {
            if (token->getValue() == L"1") {
                flushBuffer();
            }

            if (token->getValue() != L"-") {
                // token->getValue() からintへ変換しなければならない
                int noteOrder = 0;
                vector<wstring> orderIdents{
                    L"1", L"2", L"3", L"4",
                    L"5", L"6", L"7", L"8",
                    L"9", L"a", L"b", L"c",
                    L"d", L"e", L"f", L"g"};
                auto it = find(orderIdents.begin(), orderIdents.end(), token->getValue());
                if (it != orderIdents.end()) {
                    noteOrder = distance(orderIdents.begin(), it);
                }
                pair<int, int> rhythm(noteOrder, _state.currentTime);
                _state.rhythmBuffer.push_back(rhythm);
            }
            _state.currentTime += timePerUnit;
        }
    }

    // バッファ処理
    static int measureIndex = 0;
    for(int i = 0; i < matchPlacement.tokens.size(); i++) {
        auto token = matchPlacement.tokens[i];
        vector<wstring> orderIdents{
           L"1", L"2", L"3", L"4",
           L"5", L"6", L"7", L"8",
           L"9", L"a", L"b", L"c",
           L"d", L"e", L"f", L"g"};
        auto it = find(orderIdents.begin(), orderIdents.end(), token->getValue());

        int placementOrder = 0;
        if (it != orderIdents.end() && token->getValue() != L"x") {
            placementOrder = distance(orderIdents.begin(), it);
            int panelIndex = 4 * (measureIndex % 4) + i;
            pair<int, int> placement(placementOrder, panelIndex);
            _state.placementBuffer.push_back(placement);
        }
    }
    measureIndex++;

    return (isPlacement || isRhythm);
}

void Parser::flushBuffer() {
   auto& placementBuff = _state.placementBuffer;
   auto& rhythmBuff = _state.rhythmBuffer;
   sort(placementBuff.begin(), placementBuff.end(), [](pair<int, int> a, pair<int, int> b) {
       return (a.first < b.first);
   });
   for(auto placement : placementBuff) {
       auto rhythm = rhythmBuff[placement.first];
       _notes.push_back(jubeon::game::Note(rhythm.second, placement.second, 0, 0));
   }
   // バッファをクリア
   _state.rhythmBuffer.clear();
   _state.placementBuffer.clear();
};

bool Parser::parseAssign() {
    // 変数への代入
    MatchResult matchResult;
    bool assignToVar = _lexer.matchOrBack(
            matchResult,
            TokenType::IDENTIFIER,
            TokenType::EQUAL,
            TokenType::LITERAL);
    
    std::vector<shared_ptr<Token>> matchedTokens = matchResult.tokens;
    if (assignToVar && matchedTokens.size() == 3) {
        wstring name = matchedTokens[0]->getValue();
        shared_ptr<Literal> literal = static_pointer_cast<Literal>(matchedTokens[2]);
        if (name == L"t" && literal->getValueType() == LiteralType::NUMBER) {
            pair<int, int> bpmChange;
            bpmChange.first = _state.currentTime;
            bpmChange.second = stoi(literal->getValue());
            _music.bpmChanges.push_back(bpmChange);
        } else if (name == L"m" && literal->getValueType() == LiteralType::STRING) {
            _music.musicFilePath = literal->getValue();
        } else if (name == L"o" && literal->getValueType() == LiteralType::NUMBER) {
            auto value = literal->getValue().c_str();
            _music.offset = stoi(literal->getValue());
        } else if (name == L"r" && literal->getValueType() == LiteralType::NUMBER) {
            _music.offset += stoi(literal->getValue());
        }

        return true;
    } else {
        return false;
    }
};

bool Parser::parseCommand() {
    // 代入式付きコマンド
    {
        MatchResult matchResult;
        bool commandWithAssign = _lexer.matchOrBack(
                matchResult,
                TokenType::COMMAND,
                TokenType::EQUAL,
                TokenType::LITERAL);
        vector<shared_ptr<Token>> matchedTokens = matchResult.tokens;
        if (commandWithAssign && matchedTokens.size() == 3) {
            wstring name = matchedTokens[0]->getValue();
            shared_ptr<Literal> literal = static_pointer_cast<Literal>(matchedTokens[2]);
            if (name == L"title") {
                _music.title = literal->getValue();
            } else if (name == L"artist") {
                _music.artist = literal->getValue();
            } else if (name == L"dif" && literal->getValueType() == LiteralType::NUMBER) {
                _music.difficulty = stoi(literal->getValue());
            } else if (name == L"lev" && literal->getValueType() == LiteralType::NUMBER) {
                _music.level = stoi(literal->getValue());
            }

            return true;
        }
    }
    {
        MatchResult matchResult;
        bool command = _lexer.matchOrBack(
                matchResult,
                TokenType::COMMAND);
        if (command) {
            wstring commandName = matchResult.tokens[0]->getValue();
            _music.flags.push_back(commandName);
            return true;
        }
    }
    return false;
};
};