#include "checkSemantics.h"
#include "expr.h"
#include "symscope.h"


void CheckSemantics::preProcessExpr(Expr* expr) {
  if (CallExpr* parenOpExpr = dynamic_cast<CallExpr*>(expr)) {
    if (parenOpExpr->opTag >= OP_GETSNORM) {
      if (parenOpExpr->get(1)->isConst() || parenOpExpr->get(1)->isParam()) {
        USR_FATAL(parenOpExpr, "Assigning to a constant expression");
      }
    }
  }

  if (DefExpr* defExpr = dynamic_cast<DefExpr*>(expr)) {
    if (defExpr->sym->isParam()) {
      if (defExpr->init && !dynamic_cast<IntLiteral*>(defExpr->init)) {
        USR_FATAL(defExpr, "Initializing parameter to a variable expression.");
      }
      if (!defExpr->init && dynamic_cast<FnSymbol*>(defExpr->parentSymbol) &&
          defExpr->parentScope->type != SCOPE_PARAM) {
        USR_FATAL(defExpr, "Top-level params must be initialized.");
      }
    }
  }
}

