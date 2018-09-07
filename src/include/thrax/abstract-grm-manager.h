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
//
// The AbstractGrmManager holds a set of FSTs in memory and performs
// rewrites via composition. The class is parametrized by the FST arc
// type. AbstractGrmManager is thread-compatible.

#ifndef NLP_GRM_LANGUAGE_ABSTRACT_GRM_MANAGER_H_
#define NLP_GRM_LANGUAGE_ABSTRACT_GRM_MANAGER_H_

#include <map>
#include <string>
#include <vector>

#include <fst/compat.h>
#include <thrax/compat/compat.h>
#include <fst/extensions/mpdt/compose.h>
#include <fst/extensions/mpdt/mpdt.h>
#include <fst/extensions/pdt/compose.h>
#include <fst/extensions/pdt/pdt.h>
#include <fst/extensions/pdt/shortest-path.h>
#include <fst/arc.h>
#include <fst/fstlib.h>
#include <fst/fst.h>
#include <fst/string.h>
#include <fst/vector-fst.h>
#include <thrax/make-parens-pair-vector.h>
#include <thrax/compat/stlfunctions.h>

namespace thrax {

template <typename Arc>
class AbstractGrmManager {
 public:
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;
  typedef typename Arc::Label Label;

  virtual ~AbstractGrmManager();

  // Read-only access to the underlying FST map.
  const std::map<string, const Transducer*> &GetFstMap() const { return fsts_; }

  // Compile-time access to the FST table.
  std::map<string, const Transducer*> *GetFstMap() { return &fsts_; }

  // ***************************************************************************
  // REWRITE: These functions perform the actual rewriting of inputs using the
  // named FSTs.

  // Rewrites the input to the output (in various parse modes).  Returns false
  // on a failed rewrite (i.e., the input was not accepted by the rule's FST)
  // and true otherwise.  Notably, a return value of true and an empty string
  // output is a deliberate rewrite to the empty string and not a failed match.
  // If pdt_parens_rule is not empty, then it the transducer associated with
  // "rule" is assumed to be a pushdown automaton, and that associated with
  // pdt_parens_rule is assumed to specify the parentheses.
  // If pdt_assignments_rule is not empty, then this is assumed to be an MPDT.
  bool RewriteBytes(const string& rule, const string& input,
                    string* output,
                    const string& pdt_parens_rule = "",
                    const string& mpdt_assignments_rule = "") const;
  bool RewriteBytes(const string& rule, const Transducer& input,
                    string* output,
                    const string& pdt_parens_rule = "",
                    const string& mpdt_assignments_rule = "") const;
  // Unlike RewriteBytes(), The MutableTransducer output of Rewrite() contains
  // all the possible output paths. A Rewrite() call only returns false if the
  // specified rule(s) cannot be found. Notably, the call returns true even if
  // the output transducer contains no accepting path.
  bool Rewrite(const string& rule, const string& input,
               MutableTransducer* output,
               const string& pdt_parens_rule = "",
               const string& mpdt_assignments_rule = "") const;
  bool Rewrite(const string& rule, const Transducer& input,
               MutableTransducer* output,
               const string& pdt_parens_rule = "",
               const string& mpdt_assignments_rule = "") const;

  // This helper function (when given a potential string fst) takes the shortest
  // path, projects the output, and then removes epsilon arcs.
  static void StringifyFst(MutableTransducer* output);

  // ***************************************************************************
  // The following functions give access to, modify, or serialize internal data.

  // Returns the FST associated with the particular name.  This class returns
  // the actual pointer to the FST (or nullptr if it is not found), so the
  // caller should not free the pointer.
  const Transducer* GetFst(const string& name) const;

  // Gets the named FST, just like GetFst(), but this function doesn't
  // lock anything and is thread-safe because it returns a transducer
  // safely shallow-copied from the original. The caller assumes the
  // ownership of the returned transducer.
  Transducer* GetFstSafe(const string& name) const;

  // Modify the transducer under the given name.
  // If no such rule name exists, returns false, otherwise returns true.
  // Note: For thread-safety, it is assumed this function will not be
  // used in a multi-threaded context.
  bool SetFst(const string& name, const Transducer& input);

  // This function will write the created FSTs into an FST archive with the
  // provided filename.
  virtual void ExportFar(const string& filename) const = 0;

  // Sorts input labels of all FSTs in the archive.
  void SortRuleInputLabels();

 protected:
  AbstractGrmManager();

  // Loads up the FSTs given the supplied reader. Returns true on
  // success and false otherwise.
  template <typename FarReader>
  bool LoadArchive(FarReader *reader);

  // The list of FSTs held by this manager.
  std::map<string, const Transducer*> fsts_;

 private:
  DISALLOW_COPY_AND_ASSIGN(AbstractGrmManager);
};

template <typename Arc>
AbstractGrmManager<Arc>::AbstractGrmManager() {
}

template <typename Arc>
AbstractGrmManager<Arc>::~AbstractGrmManager() {
  STLDeleteContainerPairSecondPointers(fsts_.begin(), fsts_.end());
}

template <typename Arc>
template <typename FarReader>
bool AbstractGrmManager<Arc>::LoadArchive(FarReader *reader) {
  STLDeleteValues(&fsts_);
  for (reader->Reset(); !reader->Done(); reader->Next()) {
    const string& name = reader->GetKey();
    const Transducer* fst = new MutableTransducer(*(reader->GetFst()));
    fsts_[name] = fst;
  }
  SortRuleInputLabels();
  return true;
}

template <typename Arc>
void AbstractGrmManager<Arc>::SortRuleInputLabels() {
  for (typename std::map<string, const Transducer*>::iterator pos =
           fsts_.begin();
       pos != fsts_.end(); ++pos) {
    const Transducer *fst = pos->second;
    if (!fst->Properties(fst::kILabelSorted, false)) {
      VLOG(1) << "Updating FST " << fst << " with input label sorted version.";
      MutableTransducer* sorted_fst = new MutableTransducer(*fst);
      fst::ArcSort(sorted_fst, fst::ILabelCompare<Arc>());
      delete fst;
      pos->second = static_cast<const Transducer*>(sorted_fst);
    }
  }
}

template <typename Arc>
const typename AbstractGrmManager<Arc>::Transducer*
AbstractGrmManager<Arc>::GetFst(const string& name) const {
  typename std::map<string, const Transducer*>::const_iterator pos =
      fsts_.find(name);
  if (pos != fsts_.end()) {
    return pos->second;
  }
  return nullptr;
}

template <typename Arc>
typename AbstractGrmManager<Arc>::Transducer*
AbstractGrmManager<Arc>::GetFstSafe(const string& name) const {
  const Transducer *fst = GetFst(name);
  if (fst) {
    return fst->Copy(true);
  } else {
    return nullptr;
  }
}

template <typename Arc>
bool AbstractGrmManager<Arc>::SetFst(
    const string& name,
    const Transducer& input) {
  if (fsts_.count(name) == 0) {
    return false;
  }
  delete fsts_[name];
  fsts_[name] = input.Copy(true);
  return true;
}

template <typename Arc>
bool AbstractGrmManager<Arc>::RewriteBytes(
    const string& rule, const string& input,
    string* output,
    const string& pdt_parens_rule,
    const string& mpdt_assignments_rule) const {
  fst::StringCompiler<Arc> string_compiler(fst::StringTokenType::BYTE);
  MutableTransducer str_fst;
  if (!string_compiler(input, &str_fst))
    return false;
  return RewriteBytes(rule, str_fst, output, pdt_parens_rule,
                      mpdt_assignments_rule);
}

template <typename Arc>
bool AbstractGrmManager<Arc>::RewriteBytes(
    const string& rule,
    const Transducer& input,
    string* output,
    const string& pdt_parens_rule,
    const string& mpdt_assignments_rule) const {
  MutableTransducer output_fst;
  if (!Rewrite(rule, input, &output_fst, pdt_parens_rule,
               mpdt_assignments_rule))
    return false;

  StringifyFst(&output_fst);

  fst::StringPrinter<Arc> printer(fst::StringTokenType::BYTE);
  return printer(output_fst, output);
}

template <typename Arc>
bool AbstractGrmManager<Arc>::Rewrite(
    const string& rule, const string& input,
    MutableTransducer* output,
    const string& pdt_parens_rule,
    const string& mpdt_assignments_rule) const {
  fst::StringCompiler<Arc> string_compiler(fst::StringTokenType::BYTE);
  MutableTransducer str_fst;
  if (!string_compiler(input, &str_fst))
    return false;

  return Rewrite(rule, str_fst, output, pdt_parens_rule,
                 mpdt_assignments_rule);
}

template <typename Arc>
bool AbstractGrmManager<Arc>::Rewrite(
    const string& rule, const Transducer& input,
    MutableTransducer* output,
    const string& pdt_parens_rule,
    const string& mpdt_assignments_rule) const {
  const Transducer *rule_fst = GetFstSafe(rule);
  if (!rule_fst) {
    LOG(ERROR) << "Rule " << rule << " not found.";
    return false;
  }

  const Transducer* pdt_parens_fst = nullptr;
  if (!pdt_parens_rule.empty()) {
    pdt_parens_fst = GetFstSafe(pdt_parens_rule);
    if (!pdt_parens_fst) {
      LOG(ERROR) << "PDT parentheses rule " << pdt_parens_rule << " not found.";
      delete rule_fst;
      return false;
    }
  }

  const Transducer* mpdt_assignments_fst = nullptr;
  if (!mpdt_assignments_rule.empty()) {
    mpdt_assignments_fst = GetFstSafe(mpdt_assignments_rule);
    if (!mpdt_assignments_fst) {
      LOG(ERROR) << "MPDT assignments rule " << mpdt_assignments_rule
                 << " not found.";
      delete rule_fst;
      if (pdt_parens_fst) {
        delete pdt_parens_fst;
      }
      return false;
    }
  }

  if (pdt_parens_fst) {
    MutableTransducer mut_pdt_parens_fst(*pdt_parens_fst);
    std::vector<std::pair<Label, Label> > pdt_parens;
    MakeParensPairVector(mut_pdt_parens_fst, &pdt_parens);

    // EXPAND_FILTER removes the parentheses, allowing for subsequent
    // application of PDTs. At the end (in StringifyFst() we use ordinary
    // ShortestPath().
    if (mpdt_assignments_fst) {
      MutableTransducer mut_mpdt_assignments_fst(*mpdt_assignments_fst);
      std::vector<Label> mpdt_assignments;
      MakeAssignmentsVector(mut_mpdt_assignments_fst, pdt_parens,
                            &mpdt_assignments);
      fst::MPdtComposeOptions opts(true, fst::EXPAND_FILTER);
      fst::Compose(input, *rule_fst, pdt_parens, mpdt_assignments,
                       output, opts);
      delete mpdt_assignments_fst;
    } else {
      fst::PdtComposeOptions opts(true, fst::EXPAND_FILTER);
      fst::Compose(input, *rule_fst, pdt_parens, output, opts);
    }
    delete pdt_parens_fst;
  } else {
    fst::ComposeOptions opts(true, fst::ALT_SEQUENCE_FILTER);
    fst::Compose(input, *rule_fst, output, opts);
  }
  delete rule_fst;
  return true;
}


template <typename Arc>
void AbstractGrmManager<Arc>::StringifyFst(MutableTransducer* fst) {
  MutableTransducer temp;
  fst::ShortestPath(*fst, &temp);
  fst::Project(&temp, fst::PROJECT_OUTPUT);
  fst::RmEpsilon(&temp);
  *fst = temp;
}

// Triple of main rule, pdt_parens and mpdt assignments

struct RuleTriple {
  string main_rule, pdt_parens_rule, mpdt_assignments_rule;

  explicit RuleTriple(const string& rule_def) {
    auto main_pos = rule_def.find('$');
    if (main_pos == string::npos) {
      main_pos = rule_def.find(':');
    }
    main_rule = rule_def.substr(0, main_pos);
    if (main_pos == string::npos) {
      return;
    }
    auto pdt_parens_pos = rule_def.find('$', main_pos + 1);
    if (pdt_parens_pos == string::npos) {
      pdt_parens_pos = rule_def.find(':', main_pos + 1);
    }
    if (pdt_parens_pos == string::npos) {
      pdt_parens_rule = rule_def.substr(main_pos + 1);
      return;
    }
    pdt_parens_rule =
        rule_def.substr(main_pos + 1, pdt_parens_pos - main_pos - 1);
    mpdt_assignments_rule = rule_def.substr(pdt_parens_pos + 1);
  }
};

// Does not own the grm pointer.
template <typename Arc>
class RuleCascade {
  typedef fst::Fst<Arc> Transducer;
  typedef fst::VectorFst<Arc> MutableTransducer;

 public:
  RuleCascade() : grm_(nullptr) {}
  // Initializes the cascade from rule triples.
  bool Init(const AbstractGrmManager<Arc>* grm,
            std::vector<RuleTriple> rule_triples);
  // Parses the rule definitions and initializes the cascade.
  bool InitFromDefs(const AbstractGrmManager<Arc>* grm,
                    const std::vector<string>& rule_defs);
  ~RuleCascade() {}

  bool RewriteBytes(const string& input, string* output) const;
  bool RewriteBytes(const Transducer& input, string* output) const;
  bool Rewrite(const string& input, MutableTransducer* output) const;
  bool Rewrite(const Transducer& input, MutableTransducer* output) const;

 private:
  // Validates all rules.
  bool ValidateRules();
  const AbstractGrmManager<Arc>* grm_;
  std::vector<RuleTriple> rule_triples_;
};

template <typename Arc>
bool RuleCascade<Arc>::ValidateRules() {
  for (auto& rule_triple : rule_triples_) {
    if (!grm_->GetFst(rule_triple.main_rule)) {
      LOG(ERROR) << "Cannot find rule: " << rule_triple.main_rule;
      return false;
    }
    if (!rule_triple.pdt_parens_rule.empty() &&
        !grm_->GetFst(rule_triple.pdt_parens_rule)) {
      LOG(ERROR) << "Cannot find rule: " << rule_triple.pdt_parens_rule;
      return false;
    }
    if (!rule_triple.mpdt_assignments_rule.empty() &&
        !grm_->GetFst(rule_triple.mpdt_assignments_rule)) {
      LOG(ERROR) << "Cannot find rule: " << rule_triple.mpdt_assignments_rule;
      return false;
    }
  }
  return true;
}

template <typename Arc>
bool RuleCascade<Arc>::Init(const AbstractGrmManager<Arc>* grm,
                            std::vector<RuleTriple> rule_triples) {
  grm_ = grm;
  rule_triples_ = std::move(rule_triples);
  return ValidateRules();
}

template <typename Arc>
bool RuleCascade<Arc>::InitFromDefs(const AbstractGrmManager<Arc>* grm,
                                    const std::vector<string>& rules) {
  grm_ = grm;
  for (auto& rule : rules) {
    rule_triples_.push_back(RuleTriple{rule});
  }
  return ValidateRules();
}

template <typename Arc>
bool RuleCascade<Arc>::RewriteBytes(const string& input,
                                    string* output) const {
  fst::StringCompiler<Arc> string_compiler(fst::StringTokenType::BYTE);
  MutableTransducer input_fst;
  if (!string_compiler(input, &input_fst))
    return false;
  MutableTransducer output_fst;
  if (!Rewrite(input_fst, &output_fst))
    return false;
  AbstractGrmManager<Arc>::StringifyFst(&output_fst);
  fst::StringPrinter<Arc> printer(fst::StringTokenType::BYTE);
  return printer(output_fst, output);
}

template <typename Arc>
bool RuleCascade<Arc>::RewriteBytes(const Transducer& input,
                                    string* output) const {
  MutableTransducer output_fst;
  if (!Rewrite(input, &output_fst))
    return false;
  AbstractGrmManager<Arc>::StringifyFst(&output_fst);
  fst::StringPrinter<Arc> printer(fst::StringTokenType::BYTE);
  return printer(output_fst, output);
}

template <typename Arc>
bool RuleCascade<Arc>::Rewrite(const string& input,
                               MutableTransducer* output) const {
  fst::StringCompiler<Arc> string_compiler(fst::StringTokenType::BYTE);
  MutableTransducer str_fst;
  if (!string_compiler(input, &str_fst))
    return false;
  return Rewrite(str_fst, output);
}

template <typename Arc>
bool RuleCascade<Arc>::Rewrite(const Transducer& input,
                               MutableTransducer* output) const {
  MutableTransducer tmp_input(input);
  CHECK(grm_ != nullptr);
  for (auto& rule_triple : rule_triples_) {
    if (!grm_->Rewrite(rule_triple.main_rule,
                       tmp_input, output,
                       rule_triple.pdt_parens_rule,
                       rule_triple.mpdt_assignments_rule))
      return false;
    tmp_input = *output;
  }
  return true;
}

}  // namespace thrax

#endif  // NLP_GRM_LANGUAGE_ABSTRACT_GRM_MANAGER_H_
