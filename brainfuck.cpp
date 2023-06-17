#include <fstream>
#include <iostream>
#include <cstdint>
using namespace std;

// Simple Brainfuck Interpreter                                            |
//
// Author:                                                                 |
//
// +[----->+++<]>.++.+++++++++++.------------.[--->+<]>---.+[->+++<        |
// ]>.[-->+<]>---.--[--->+<]>-.++++++++++++.--.+++[->+++++<]>-.+.[-        |
// ---->+<]>--.++++++.+.                                                   |
//
// 06/16/2023                                                              |


// using any register outside of 1-50000                                   |
// can result in undefined behavior                                        |
//
// unclosed brackets can result in undefined                               |
// behavior                                                                |
// does not fully conform to the                                           |
// official bf standard bc im lazy                                         |
//                                                                         |
// https://github.com/brain-lang/brainfuck/blob/master/brainfuck.md        |
//
//
// + Debugging Operator [?] - prints value in number form;





uint8_t *tape = new uint8_t[50000];
char *instructions = new char[50000];
bool debug = false;

bool validInstruction(char c) {
  switch (c) {
    case '>':
    case '<':
    case '+':
    case '-':
    case '.':
    case ',':
    case '[':
    case ']':
    case '?':
      return true;
      break;
  }

  return false;

}

void jumpToMatchingClose() {
  int bracketCount = 1;

  while (bracketCount != 0) {
    ++instructions;

    if ((*instructions) == '[')
      ++bracketCount;

    if ((*instructions) == ']')
      --bracketCount;
  }
}

void jumpToMatchingOpen() {
  int bracketCount = 1;

  while (bracketCount != 0) {
    --instructions;

    if ((*instructions) == ']')
      ++bracketCount;

    if ((*instructions) == '[')
      --bracketCount;
  }
}
void interpret(char c) {
  switch (c) {
  case '>':
    ++tape;
    break;

  case '<':
    --tape;
    break;

  case '+':
    ++(*tape);
    break;

  case '-':
    --(*tape);
    break;

  case '.':
    cout << static_cast<char>(*tape);
    break;

  case ',':
    char buffer;
    cin >> buffer;

    *tape = static_cast<int>(buffer);
    break;

  case '[':
    if ((*tape) == 0) {
      jumpToMatchingClose();
    }
    break;

  case ']':
    if ((*tape) != 0) {
      jumpToMatchingOpen();
    }
    break;

  case '?':
    cout << static_cast<int>(*tape);
    break;
  }
}

void printUsage() {
  cout << '\n'
  << "Usage: brainfuck [FILENAME]\n\n";
}

int main(int argc, char *argv[]) {

  //
  // I PROGRAMMED THIS AT 3AM
  // DON'T JUDGE ME
  //


  if (argc == 1) {
    printUsage();
    cerr << "Brainfuck: error: You must provide one file to interpret.\n";
    return 2;
  }

  ifstream file{argv[1]};
  if (!file) {
    cerr << "Could not open file: " << argv[1] << '\n';
    return 1;
  }


  // Load instructions into memory
  char currentCmd;
  char* start = instructions;
  while (file >> currentCmd) {
    if(validInstruction(currentCmd)) {
      *instructions = currentCmd;
      if (debug) cout << "Added instruction: "<< *instructions << " @ " << &instructions << "\n";
      ++instructions;
    }
  }
  //null character
  *instructions = 0;

  //Put pointer at start
  //begin execution
  instructions = start;
  if (debug) cout << "starting instruction: " << *instructions << '\n'; 

  while(*instructions) {
    if (debug) cout << "interpreting: " << *instructions;
    interpret(*instructions);
    if (debug) cout << " | reg value: " << *tape << '\n';
    ++instructions;
  }

  if (debug) cout << "\n\n----------\nEND OF INSTRUCTIONS\n----------" << '\n';

  cout << '\n';

  return EXIT_SUCCESS;
}


/* +[------->++<]>-.------------.+++.+.--[--->+<]>-.--[->++++<]>-.+[->+++<]>+
 * .+++++++++++.------------.--[--->+<]>--.++[->+++<]>.++++++++++++.+++.--.+.
 * --.+++[->+++<]>++.--[--->+<]>-.-----------.++++++.-.>++++++++++..-[->+++++
 *  <]>.[--->++<]>++.[-->+++++<]>-.--[--->+<]>-.++++++.+.-[---->+<]>+++.--[->
 *  ++<]>.---------. */

// https://copy.sh/brainfuck/text.html
