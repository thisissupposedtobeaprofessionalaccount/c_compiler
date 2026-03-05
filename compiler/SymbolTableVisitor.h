#pragma once

#include "SymbolTable.h"
#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include <any>
#include <map>
#include <string>


class SymbolTableVisitor : public ifccBaseVisitor {
  public:
  // Declaration
  virtual std::any visitDeclaration(ifccParser::DeclarationContext *ctx) override;

  SymbolTable getSymbolTable() { return varIdx; }

protected:
  unsigned int varCnt = 0;
  SymbolTable varIdx;
};
