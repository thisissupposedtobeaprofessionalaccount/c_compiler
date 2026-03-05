#pragma once

#include "antlr4-runtime.h"
#include "generated/ifccBaseVisitor.h"
#include <any>
#include <map>
#include <string>

class CodeGenVisitor : public ifccBaseVisitor {
public:
  virtual std::any visitProg(ifccParser::ProgContext *ctx) override;

  // Return
  virtual std::any
  visitReturn_stmt(ifccParser::Return_stmtContext *ctx) override;
  // Declaration and Assignment
  virtual std::any
  visitDeclaration(ifccParser::DeclarationContext *ctx) override;
  virtual std::any visitAssignment(ifccParser::AssignmentContext *ctx) override;

  // Expr
  virtual std::any visitMult_div_mod_expr(ifccParser::Mult_div_mod_exprContext *ctx) override;
  virtual std::any visitMinus_expr(ifccParser::Minus_exprContext *ctx) override;
  virtual std::any visitAdd_sub_expr(ifccParser::Add_sub_exprContext *ctx) override;
  virtual std::any visitNot_expr(ifccParser::Not_exprContext *ctx) override;
  virtual std::any visitShift_expr(ifccParser::Shift_exprContext *ctx) override;
  virtual std::any visitBit_and_expr(ifccParser::Bit_and_exprContext *ctx) override;
  virtual std::any visitBit_or_expr(ifccParser::Bit_or_exprContext *ctx) override;
  virtual std::any visitBool_and_expr(ifccParser::Bool_and_exprContext *ctx) override;
  virtual std::any visitBool_or_expr(ifccParser::Bool_or_exprContext *ctx) override;
  virtual std::any visitPar_expr(ifccParser::Par_exprContext *ctx) override;
  virtual std::any visitCmp_expr(ifccParser::Cmp_exprContext *ctx) override;
  virtual std::any visitCmp_eq_expr(ifccParser::Cmp_eq_exprContext *ctx) override;
  virtual std::any visitEq_expr(ifccParser::Eq_exprContext *ctx) override;

  virtual std::any visitConst_expr(ifccParser::Const_exprContext *ctx) override;
  virtual std::any visitVar_expr(ifccParser::Var_exprContext *ctx) override;

protected:
  unsigned int varCnt = 0;
  std::map<std::string, int> varIdx;
};
