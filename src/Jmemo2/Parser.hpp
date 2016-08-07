#pragma once
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include "Lexer.hpp"

#include "Game/Sequence.hpp"

// Example:
// Jmemo2Parser parser;
// parser.initWithFileName(filename);
//
// vector<Note> notes = parser.getNotes();
// Music music = parser.getMusic();
//
// cout << "Level " << music.level << endl;
// cout << "offset " << music.offset << endl;

using namespace std;
namespace Jmemo2 {
enum class Difficulty {
    BASIC,
    ADVANCED,
    EXTREAM
};

typedef struct ParserState {
    int currentTime;
    bool isPreamble;
    vector<pair<int, int>> rhythmBuffer;
    vector<pair<int, int>> placementBuffer;
    ParserState():currentTime(0), isPreamble(true) {};
} ParserState;

typedef struct Music {
    wstring title;
    wstring artist;
    wstring musicFilePath;
    wstring jacketFilePath;
    int level;
    int offset;
    int difficulty;
    vector<wstring> flags;
    vector<pair<int, int>> bpmChanges;
    Music()
        : title(L""),
        artist(L""),
        musicFilePath(L""),
        jacketFilePath(L""),
        level(1),
        offset(0) {};
} Music;


class Parser {
public:
    Parser() {};
    void initWithString(string source);
    void initWithFileName(string fileName);
    Music getMusic() { return _music; };
    vector<jubeon::game::Note> getNotes() { return _notes; };
    bool parseLabel();
    bool parseCommand();
    bool parseAssign();
    bool parseMusic();

    void flushBuffer();
private:
    vector<jubeon::game::Note> _notes;
    Music _music;
    Lexer _lexer;
    ParserState _state;
};
};