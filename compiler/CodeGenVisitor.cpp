#include "CodeGenVisitor.h"
#include <iostream>
#include <string>

std::any CodeGenVisitor::visitProg(ifccParser::ProgContext *ctx) {
#ifdef __APPLE__
  std::cout << ".globl _main\n";
  std::cout << " _main: \n";
#else
  std::cout << ".globl main\n";
  std::cout << " main: \n";
#endif

  for (auto statement : ctx->stmt()) {
    this->visit(statement);
  }

  this->visit(ctx->return_stmt());

  std::cout << "    ret\n";

  return 0;
}


std::any CodeGenVisitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {

  std::string varName = ctx->VAR()->getText();

  if (this->varIdx.count(varName) != 0) {
    std::cerr << "Error : variable " << varName << " already declared\n";
    return 1;
  }

  this->varIdx[varName] = (int)(++varCnt);

  return 0;
}

std::any CodeGenVisitor::visitAssignment(ifccParser::AssignmentContext *ctx) {
  std::string varName = ctx->VAR()->getText();

  if (this->varIdx.count(varName) == 0) {
    std::cerr << "Error : variable " << varName << " not declared\n";
    return 1;
  }

  this->visit(ctx->expr());

  std::cout << "    movl \%eax, " << -4 * this->varIdx[varName]
            << "(%rbp)\n";

  return 0;
}

std::any CodeGenVisitor::visitReturn_stmt(ifccParser::Return_stmtContext *ctx) {
  this->visit(ctx->expr());
  return 0;
}

std::any CodeGenVisitor::visitConst_expr(ifccParser::Const_exprContext *ctx) {
  int value = std::stoi(ctx->CONST()->getText());

  std::cout << "    movl $" << value << ", \%eax\n";

  return 0;
}
std::any CodeGenVisitor::visitVar_expr(ifccParser::Var_exprContext *ctx) {
  std::string varName = ctx->VAR()->getText();

  if (this->varIdx.count(varName) == 0) {
    std::cerr << "Error : variable " << varName << " not declared\n";
    return 1;
  }

  std::cout << "    movl " << -4 * this->varIdx[varName]
            << "(%rbp), \%eax\n";

  return 0;
}
std::any CodeGenVisitor::visitAdd_sub_expr(ifccParser::Add_sub_exprContext *ctx) {
  this->visit(ctx->expr(0));
  std::cout << "    pushq \%rax\n";
  this->visit(ctx->expr(1));
  std::cout << "    popq \%rcx\n";
  if(ctx->ADD()) 
     std::cout << "    addl \%ecx, \%eax\n";
  else if(ctx->SUB())
     std::cout << "    subl \%ecx, \%eax\n";

  return 0; 

}

std::any CodeGenVisitor::visitMult_div_mod_expr(ifccParser::Mult_div_mod_exprContext *ctx) {
    this->visit(ctx->expr(0)); // Gauche -> %eax
    std::cout << "  pushq %rax\n";
    this->visit(ctx->expr(1)); // Droite -> %eax
    
    // On met la droite dans %ecx pour libérer %eax (nécessaire pour idiv)
    std::cout << "  movl %eax, %ecx\n"; 
    std::cout << "  popq %rax\n";       // Récupère la gauche dans %eax

    if (ctx->MULT()) {
        std::cout << "  imull %ecx, %eax\n";
    } 
    else if (ctx->DIV() || ctx->MOD()) {
        std::cout << "  cltd\n";
        std::cout << "  idivl %ecx\n";
        if (ctx->MOD()) {
            std::cout << "  movl %edx, %eax\n"; // Modulo : le reste est dans %edx
        }
        // Pour la division, le résultat est déjà dans %eax
    }
    return 0;
}
std::any CodeGenVisitor::visitPar_expr(ifccParser::Par_exprContext *ctx) {
  return this->visit(ctx->expr());
}
