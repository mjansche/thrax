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
// Simple implementation of StrCat, needed in various places. This version
// allows from 2 to 5 combinations of strings and ints.

#ifndef THRAX_COMPAT_STRUTILS_H_
#define THRAX_COMPAT_STRUTILS_H_

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdarg>
#include <cstdio>

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <fst/compat.h>

using std::string;

namespace thrax {

// Operations on strings.

class StringOrInt {
 public:
  StringOrInt(const string &s) : str_(s) {}  // NOLINT

  StringOrInt(const char *s) : str_(string(s)) {}  // NOLINT

  StringOrInt(int i) {  // NOLINT
    char buf[1024];
    sprintf(buf, "%d", i);
    str_ = string(buf);
  }

  const string &Get() const { return str_; }

 private:
  string str_;
};

// TODO(kbg): Make this work with variadic template, maybe.

inline string StringCat(const StringOrInt &s1, const StringOrInt &s2) {
  return s1.Get() + s2.Get();
}

inline string StringCat(const StringOrInt &s1,
                        const StringOrInt &s2,
                        const StringOrInt &s3) {
  return s1.Get() + StringCat(s2, s3);
}

inline string StringCat(const StringOrInt &s1,
                        const StringOrInt &s2,
                        const StringOrInt &s3,
                        const StringOrInt &s4) {
  return s1.Get() + StringCat(s2, s3, s4);
}

inline string StringCat(const StringOrInt &s1,
                        const StringOrInt &s2,
                        const StringOrInt &s3,
                        const StringOrInt &s4,
                        const StringOrInt &s5) {
  return s1.Get() + StringCat(s2, s3, s4, s5);
}

namespace internal {

// Destructive variants.

inline void StringReplace(string *full, const string &before,
                          const string &after) {
  size_t pos = 0;
  while ((pos = full->find(before, pos)) != string::npos) {
    full->replace(pos, before.size(), after);
    pos += after.size();
  }
}

inline void StripTrailingAsciiWhitespace(string *full) {
  const auto lambda = [](char ch) { return !std::isspace(ch); };
  const auto pos = std::find_if(full->rbegin(), full->rend(), lambda).base();
  full->erase(pos, full->end());
}

}  // namespace internal

inline string StringReplace(const string &full, const string &before,
                            const string &after, bool /* ignored */) {
  string copy(full);
  internal::StringReplace(&copy, before, after);
  return copy;
}

inline string StripTrailingAsciiWhitespace(const string &full) {
  string copy(full);
  internal::StripTrailingAsciiWhitespace(&copy);
  return copy;
}

string StringJoin(const std::vector<string> &elements, const string &delim);

std::vector<string> StringSplit(const string &full, const char *delim);

inline std::vector<string> StringSplit(const string &full, char delim) {
  return StringSplit(full, string(1, delim).c_str());
}

inline std::vector<string> StringSplit(const string &full,
                                       const string &delim) {
  return StringSplit(full, delim.c_str());
}

string StringPrintf(const char *format, ...);

void SplitStringAllowEmpty(const string &full, const char *delim,
                           std::vector<string> *result);

// Operations on filenames.

string JoinPath(const string &dirname, const string &basename);

const char *Suffix(const char *filename);

const string Suffix(const string &filename);

string StripBasename(const char *filename);

string StripBasename(const string &filename);

bool Readable(const string &filename);

void ReadFileToStringOrDie(const string &filename, string *store);

bool RecursivelyCreateDir(const string &path);

class File {
 public:
  File() {}

  explicit File(std::fstream *stream) : stream_(stream) {}

  void SetStream(std::fstream *stream) { stream_.reset(stream); }

  std::fstream *Stream() { return stream_.get(); }

  void Close() {
    stream_->close();
    stream_.reset();
  }

 private:
  std::unique_ptr<std::fstream> stream_;
};

// 2^14 should be enough for 1 line for the intended use.

class InputBuffer {
 public:
  constexpr static int kMaxLine = 16384;

  explicit InputBuffer(File *fp) : fp_(fp) {}

  bool ReadLine(string *line) {
    line->clear();
    fp_->Stream()->getline(buf_, kMaxLine);
    if (!fp_->Stream()->gcount()) {
      fp_.reset();
      return false;
    }
    line->append(buf_);
    return true;
  }

 private:
  std::unique_ptr<File> fp_;
  char buf_[kMaxLine];
};

File *Open(const string &filename, const string &mode);

File *OpenOrDie(const string &filename, const string &mode);

}  // namespace thrax

#endif  // THRAX_COMPAT_STRUTILS_H_
