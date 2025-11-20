#include "dictionary.h"

// Lookup Table for Token Type from Token Special
TokenType token_type_lookup(TokenSpecial ts) {
  if (TS_NONE == ts) return T_INVALID;

  if (TS_IF <= ts && ts <= TS_PRINT) return T_KEYWORD;
  if (TS_SWITCH <= ts && ts <= TS_CONTINUE) return T_RESERVED;
  if (TS_INT <= ts && ts <= TS_STRING) return T_NOISE;
  if (TS_TRUE <= ts && ts <= TS_FLOAT_LITERAL) return T_CONSTANT;
  if (TS_SEMICOLON <= ts && ts <= TS_R_BRACE) return T_DELIMITER;
  if (TS_INCREMENT <= ts && ts <= TS_GREATER_THAN) return T_OPERATOR;
  if (TS_IDENTIFIER == ts) return T_IDENTIFIER;
  if (TS_COMMENT_BLOCK == ts || ts == TS_COMMENT_LINE) return T_COMMENT;

  return T_UNKNOWN;
}

char* tt2str(TokenType token_type) {
  switch (token_type) {
    case T_INVALID:
      return "T_INVALID";
    case T_KEYWORD:
      return "T_KEYWORD";
    case T_RESERVED:
      return "T_RESERVED";
    case T_IDENTIFIER:
      return "T_IDENTIFIER";
    case T_CONSTANT:
      return "T_CONSTANT";
    case T_OPERATOR:
      return "T_OPERATOR";
    case T_DELIMITER:
      return "T_DELIMITER";
    case T_COMMENT:
      return "T_COMMENT";
    case T_NOISE:
      return "T_NOISE";
    default:
      return "TS_UNKNOWN";
  }
}

char* ts2str(TokenSpecial token_type_special) {
  switch (token_type_special) {
    case TS_NONE:
      return "TS_NONE";
    case TS_IF:
      return "TS_IF";
    case TS_ELSE:
      return "TS_ELSE";
    case TS_FOR:
      return "TS_FOR";
    case TS_WHILE:
      return "TS_WHILE";
    case TS_VAR:
      return "TS_VAR";
    case TS_PRINT:
      return "TS_PRINT";
    case TS_SWITCH:
      return "TS_SWITCH";
    case TS_FUNC:
      return "TS_FUNC";
    case TS_RETURN:
      return "TS_RETURN";
    case TS_CASE:
      return "TS_CASE";
    case TS_DEFAULT:
      return "TS_DEFAULT";
    case TS_BREAK:
      return "TS_BREAK";
    case TS_CONTINUE:
      return "TS_CONTINUE";
    case TS_INT:
      return "TS_INT";
    case TS_FLOAT:
      return "TS_FLOAT";
    case TS_BOOL:
      return "TS_BOOL";
    case TS_CHAR:
      return "TS_CHAR";
    case TS_STRING:
      return "TS_STRING";
    case TS_TRUE:
      return "TS_TRUE";
    case TS_FALSE:
      return "TS_FALSE";
    case TS_CHAR_LITERAL:
      return "TS_CHAR_LITERAL";
    case TS_STRING_LITERAL:
      return "TS_STRING_LITERAL";
    case TS_INTEGER_LITERAL:
      return "TS_INTEGER_LITERAL";
    case TS_FLOAT_LITERAL:
      return "TS_FLOAT_LITERAL";
    case TS_SEMICOLON:
      return "TS_SEMICOLON";
    case TS_L_PAREN:
      return "TS_L_PAREN";
    case TS_R_PAREN:
      return "TS_R_PAREN";
    case TS_L_BRACE:
      return "TS_L_BRACE";
    case TS_R_BRACE:
      return "TS_R_BRACE";
    case TS_INCREMENT:
      return "TS_INCREMENT";
    case TS_DECREMENT:
      return "TS_DECREMENT";
    case TS_ADD:
      return "TS_ADD";
    case TS_SUBTRACT:
      return "TS_SUBTRACT";
    case TS_MULTIPLY:
      return "TS_MULTIPLY";
    case TS_DIVIDE:
      return "TS_DIVIDE";
    case TS_MODULO:
      return "TS_MODULO";
    case TS_DIVIDE_FLOOR:
      return "TS_DIVIDE_FLOOR";
    case TS_ASSIGNMENT:
      return "TS_ASSIGNMENT";
    case TS_POWER:
      return "TS_POWER";
    case TS_EQUAL:
      return "TS_EQUAL";
    case TS_NOT_EQUAL:
      return "TS_NOT_EQUAL";
    case TS_LESS_EQUAL:
      return "TS_LESS_EQUAL";
    case TS_GREATER_EQUAL:
      return "TS_GREATER_EQUAL";
    case TS_AND:
      return "TS_AND";
    case TS_OR:
      return "TS_OR";
    case TS_NOT:
      return "TS_NOT";
    case TS_LESS_THAN:
      return "TS_LESS_THAN";
    case TS_GREATER_THAN:
      return "TS_GREATER_THAN";
    case TS_IDENTIFIER:
      return "TS_IDENTIFIER";
    case TS_COMMENT_LINE:
      return "TS_COMMENT_LINE";
    case TS_COMMENT_BLOCK:
      return "TS_COMMENT_BLOCK";
    default:
      return "TS_UNKNOWN";
  }
}