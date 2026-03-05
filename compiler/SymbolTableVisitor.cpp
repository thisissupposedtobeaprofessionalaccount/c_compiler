#include "SymbolTableVisitor.h"
#include <iostream>
#include <string>

std::any
SymbolTableVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {

  std::string varName = ctx->VAR()->getText();

  if (this->varIdx.count(varName) != 0) {
    std::cerr << "Error : variable " << varName << " already declared\n";
    return 1;
  }

  this->varIdx[varName] = (int)(++varCnt);

  return 0;
}

