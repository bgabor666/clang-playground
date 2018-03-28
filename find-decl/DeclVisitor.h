#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/Type.h"
#include "clang/Basic/SourceManager.h"
#include "llvm/Support/raw_ostream.h"

#include <string>
#include <sstream>

class DeclVisitor : public clang::RecursiveASTVisitor<DeclVisitor> {
  clang::SourceManager &SourceManager;

public:
  DeclVisitor(clang::SourceManager &SourceManager)
      : SourceManager(SourceManager) {}

  bool VisitNamedDecl(clang::NamedDecl *NamedDecl) {
    //llvm::outs() << "Found " << NamedDecl->getQualifiedNameAsString() << ", with kind: " << NamedDecl->getDeclKindName() << " with QualType: " << NamedDecl->getName()  << " at "
      //           << getDeclLocation(NamedDecl->getLocStart()) << "\n";
    //NamedDecl->dump();
    return true;
  }


  bool VisitTypeDecl(clang::TypeDecl *TypeDecl) {
    clang::QualType QT(TypeDecl->getTypeForDecl(), 0);
    llvm::outs() << "getAsString(): " << QT.getAsString() << "\n";
    //llvm::outs() << "getCanonicalType().getAsString(): " << QT.getCanonicalType().getAsString() << "\n";
    TypeDecl->dump();
    //TypeDecl->getTypeForDecl()->dump();
    //TypeDecl->getTypeForDecl()->getUnqualifiedDesugaredType()->dump();
    //TypeDecl->getTypeForDecl()->getUnqualifiedDesugaredType().getAsString();
    //llvm::outs() << "getAsString(): " << TypeDecl->getTypeForDecl()->getLocallyUnqualifiedSingleStepDesugaredType().getAsString() << "\n";
    //llvm::outs() << "getAsString: " << clang::QualType::getAsString(TypeDecl) << "\n";
    return true;
  }

  bool VisitValueDecl(clang::ValueDecl *ValueDecl) {
    //clang::QualType QT(ValueDecl->getType(), 0);
    llvm::outs() << "getAsString(): " << ValueDecl->getType().getAsString() << "\n";
    llvm::outs() << "getCanonicalType().getAsString(): " << ValueDecl->getType().getCanonicalType().getAsString() << "\n";
    ValueDecl->dump();
    return true;
  }

private:
  std::string getDeclLocation(clang::SourceLocation Loc) const {
    std::ostringstream OSS;
    OSS << SourceManager.getFilename(Loc).str() << ":"
        << SourceManager.getSpellingLineNumber(Loc) << ":"
        << SourceManager.getSpellingColumnNumber(Loc);
    return OSS.str();
  }
};
