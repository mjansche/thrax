// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Copyright 2005-2011 Google, Inc.
// Author: ttai@google.com (Terry Tai)

#include <thrax/printer.h>

#include <iostream>
#include <string>

#include <thrax/collection-node.h>
#include <thrax/fst-node.h>
#include <thrax/function-node.h>
#include <thrax/grammar-node.h>
#include <thrax/identifier-node.h>
#include <thrax/import-node.h>
#include <thrax/node.h>
#include <thrax/return-node.h>
#include <thrax/rule-node.h>
#include <thrax/statement-node.h>
#include <thrax/string-node.h>

namespace thrax {

AstPrinter::AstPrinter()
    : num_spaces_(0), out(cout) {}

AstPrinter::AstPrinter(ostream& output_stream)
    : num_spaces_(0), out(output_stream) {}

AstPrinter::~AstPrinter() {}

void AstPrinter::Visit(CollectionNode* node) {
  out << Spaces() << "CollectionNode" << endl;
  ScopedSpaceCounter ssc(&num_spaces_);
  for (int i = 0; i < node->Size(); ++i)
    (*node)[i]->Accept(this);
}

void AstPrinter::Visit(FstNode* node) {
  out << Spaces() << "FstNode" << endl;
  ScopedSpaceCounter ssc(&num_spaces_);
  out << Spaces() << "Type: " << FstNode::FstNodeTypeToString(node->GetType())
      << endl;

  // Handle subtype specific logic.
  if (node->GetType() == FstNode::STRING_FSTNODE) {
    StringFstNode* snode = static_cast<StringFstNode*>(node);
    out << Spaces() << "Parsing: ";
    if (snode->GetParseMode() == StringFstNode::BYTE)
      out << "BYTE" << endl;
    else if (snode->GetParseMode() == StringFstNode::UTF8)
      out << "UTF8" << endl;
    else
      out << "SYMBOL_TABLE" << endl;
  } else if (node->GetType() == FstNode::REPETITION_FSTNODE) {
    RepetitionFstNode* rnode = static_cast<RepetitionFstNode*>(node);
    out << Spaces() << "Subtype: "
        << RepetitionFstNode::RepetitionFstNodeTypeToString(
               rnode->GetRepetitionType())
        << endl;
    if (rnode->GetRepetitionType() == RepetitionFstNode::RANGE) {
      int min, max;
      rnode->GetRange(&min, &max);
      out << Spaces() << "Range: " << min << " to " << max << endl;
    }
  }

  if (node->NumArguments() > 0) {
    out << Spaces() << "Arguments:" << endl;
    for (int i = 0; i < node->NumArguments(); ++i)
      node->GetArgument(i)->Accept(this);
  }
  if (node->HasWeight())
    out << Spaces() << "Weight: " << node->GetWeight() << endl;
}

void AstPrinter::Visit(FunctionNode* node) {
  out << Spaces() << "FunctionNode" << endl;
  ScopedSpaceCounter ssc(&num_spaces_);
  node->GetName()->Accept(this);
  node->GetArguments()->Accept(this);
  node->GetBody()->Accept(this);
}

void AstPrinter::Visit(GrammarNode* node) {
  out << Spaces() << "GrammarNode" << endl;
  ScopedSpaceCounter ssc(&num_spaces_);
  out << Spaces() << "Imports:" << endl;
  node->GetImports()->Accept(this);
  out << Spaces() << "Functions:" << endl;
  node->GetFunctions()->Accept(this);
  out << Spaces() << "Statements:" << endl;
  node->GetStatements()->Accept(this);
}

void AstPrinter::Visit(IdentifierNode* node) {
  out << Spaces() << "IdentifierNode: " << node->Get() << endl;
}

void AstPrinter::Visit(ImportNode* node) {
  out << Spaces() << "ImportNode" << endl;
  ScopedSpaceCounter ssc(&num_spaces_);
  out << Spaces() << "Path:" << endl;
  node->GetPath()->Accept(this);
  out << Spaces() << "Alias:" << endl;
  node->GetAlias()->Accept(this);
}

void AstPrinter::Visit(RepetitionFstNode* node) {
  // Use the base FstNode version.
  Visit(static_cast<FstNode*>(node));
}

void AstPrinter::Visit(ReturnNode* node) {
  out << Spaces() << "ReturnNode" << endl;
  ScopedSpaceCounter ssc(&num_spaces_);
  node->Get()->Accept(this);
}

void AstPrinter::Visit(RuleNode* node) {
  out << Spaces() << "RuleNode"
      << (node->ShouldExport() ? " (exported)" : "") << endl;
  ScopedSpaceCounter ssc(&num_spaces_);
  node->GetName()->Accept(this);
  node->Get()->Accept(this);
}

void AstPrinter::Visit(StatementNode* node) {
  out << Spaces() << "StatementNode" << endl;
  ScopedSpaceCounter ssc(&num_spaces_);
  node->Get()->Accept(this);
}

void AstPrinter::Visit(StringFstNode* node) {
  // Use the base FstNode version.
  Visit(static_cast<FstNode*>(node));
}

void AstPrinter::Visit(StringNode* node) {
  out << Spaces() << "StringNode: " << node->Get() << endl;
}

string AstPrinter::Spaces() const {
  string output;
  for (int i = 0; i < num_spaces_; ++i) {
    if (i != num_spaces_ - 1)
      output += "|   ";
    else
      output += "|-- ";
  }
  return output;
}

AstPrinter::ScopedSpaceCounter::ScopedSpaceCounter(int* num_spaces)
    : num_spaces_(num_spaces) {
  *num_spaces_ += 1;
}

AstPrinter::ScopedSpaceCounter::~ScopedSpaceCounter() {
  *num_spaces_ -= 1;
}

}  // namespace thrax
