#include <debug.h>
#include <fileioc.h>
#include <stdint.h> //NOLINT
#include <ti/getcsc.h>
#include <ti/getkey.h>
#include <ti/screen.h>

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

uint8_t *tape = new uint8_t[5000]{0};
char *instructions = new char[1000]{0};

bool validInstruction(char c) {
  switch (c) {
  //>
  case 0x6c:
  //<
  case 0x6b:
  //+
  case 0x70:
  //-
  case 0x71:
  //.
  case 0x3a:
  //,
  case 0x2b:
  //[
  case 0x06:
  //]
  case 0x07:
    return true;
    break;
  }

  return false;
}

void jumpToMatchingClose() {
  int bracketCount = 1;

  while (bracketCount != 0) {
    ++instructions;

    //[
    if ((*instructions) == 0x06)
      ++bracketCount;

    //]
    if ((*instructions) == 0x07)
      --bracketCount;
  }
}

void jumpToMatchingOpen() {
  int bracketCount = 1;

  while (bracketCount != 0) {
    --instructions;

    //]
    if ((*instructions) == 0x07)
      ++bracketCount;

    //[
    if ((*instructions) == 0x06)
      --bracketCount;
  }
}
void interpret(char c) {
  switch (c) {
  //>
  case 0x6c:
    dbg_printf("right\n");
    ++tape;
    break;

  //<
  case 0x6b:
    dbg_printf("left\n");
    --tape;
    break;

  //+
  case 0x70:
    dbg_printf("adding\n");
    ++(*tape);
    break;

  //-
  case 0x71:
    dbg_printf("subtracting\n");
    --(*tape);
    break;

  //.
  case 0x3a:
    dbg_printf("printing\n");
    outchar(static_cast<char>(*tape));
    break;

  //[
  case 0x06:
    dbg_printf("begin loop\n");
    if ((*tape) == 0) {
      jumpToMatchingClose();
    }
    break;

  //]
  case 0x07:
    dbg_printf("end loop\n");
    if ((*tape) != 0) {
      jumpToMatchingOpen();
    }
    break;

  //,
  case 0x2b:
    dbg_printf("input\n");
    *tape = getchar();
    break;

  }
}

int main() {
  os_ClrHome();
  char program_name[50];

  os_GetStringInput("BF Program Name: ", program_name, 50);
  auto file = ti_Open(program_name, "r");
  if (file == 0) {
    os_ClrHome();
    os_PutStrLine("Error: Program not found!");
    while (!os_GetCSC())
      ;
    return 0;
  }

  ti_Read(instructions, 1, 1000, file);
  ti_Close(file);

  //DEBUG
  for (int i = 0; i < 6; ++i) {
    dbg_printf("%x, ", *(instructions + i));
  }
  dbg_printf("\n");

  // Clear screen
  // Put pointer at start
  // begin execution
  os_ClrHome();
  for (; validInstruction(*instructions); ++instructions) {
    dbg_printf("interpreting %x\n", (*instructions));
    interpret(*instructions);
  }

  while (!os_GetCSC())
    ;

  delete[] tape;
  return 0;
}

/* +[------->++<]>-.------------.+++.+.--[--->+<]>-.--[->++++<]>-.+[->+++<]>+
 * .+++++++++++.------------.--[--->+<]>--.++[->+++<]>.++++++++++++.+++.--.+.
 * --.+++[->+++<]>++.--[--->+<]>-.-----------.++++++.-.>++++++++++..-[->+++++
 *  <]>.[--->++<]>++.[-->+++++<]>-.--[--->+<]>-.++++++.+.-[---->+<]>+++.--[->
 *  ++<]>.---------. */

// https://copy.sh/brainfuck/text.html
