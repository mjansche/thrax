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

#include <thrax/compat/utils.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdarg>
#include <cstdio>

#include <fstream>
#include <numeric>
#include <string>
#include <vector>

// For Cygwin and other installations that do not define ACCESSPERMS (thanks to
// Damir Cavar).
#ifndef ACCESSPERMS
#define ACCESSPERMS (S_IRWXU|S_IRWXG|S_IRWXO)
#endif

namespace thrax {

// Operations on strings.

namespace {

// Computes size of joined string.
size_t GetResultSize(const std::vector<string> &elements, size_t s_size) {
  const auto lambda = [](size_t partial, const string &right) {
      return partial + right.size();
  };
  return (std::accumulate(elements.begin(), elements.end(), 0, lambda) +
          s_size * (elements.size() - 1));
}

}  // namespace

// Joins a vector of strings on a given delimiter.
string StringJoin(const std::vector<string> &elements, const string &delim) {
  string result;
  if (elements.empty()) return result;
  size_t s_size = delim.size();
  result.reserve(GetResultSize(elements, s_size));
  auto it = elements.begin();
  result.append(it->data(), it->size());
  for (++it; it != elements.end(); ++it) {
    result.append(delim.data(), s_size);
    result.append(it->data(), it->size());
  }
  return result;
}

// Splits a string according to delimiter, skipping over consecutive
// delimiters.
std::vector<string> StringSplit(const string &full, const char *delim) {
  size_t prev = 0;
  size_t found = full.find_first_of(delim);
  size_t size = found - prev;
  std::vector<string> result;
  if (size > 0) result.push_back(full.substr(prev, size));
  while (found != string::npos) {
    prev = found + 1;
    found = full.find_first_of(delim, prev);
    size = found - prev;
    if (size > 0) result.push_back(full.substr(prev, size));
  }
  return result;
}

// Split a string according to the delimiters, including consecutive
// delimiters as empty strings.
void StripSplitAllowEmpty(const string &full, const char *delim,
                           std::vector<string> *result) {
  size_t prev = 0;
  size_t found = full.find_first_of(delim);
  result->push_back(full.substr(prev, found - prev));
  while (found != string::npos) {
    prev = found + 1;
    found = full.find_first_of(delim, prev);
    result->push_back(full.substr(prev, found - prev));
  }
}

string StringPrintf(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  char buf[1024];
  vsnprintf(buf, 1024, format, ap);
  string retval(buf);
  va_end(ap);
  return retval;
}

// Operations on filenames.

string JoinPath(const string &dirname, const string &basename) {
  if ((!basename.empty() && basename[0] == '/') || dirname.empty()) {
    return basename;
  } else if (dirname[dirname.size() - 1] == '/') {
    return dirname + basename;
  } else {
    return dirname + "/" + basename;
  }
}

const char *Suffix(const char *filename) {
  const char *base = strrchr(filename, '/');
  if (!base) base = filename;
  const char *last_dot = strrchr(base, '.');
  return (last_dot ? last_dot + 1 : nullptr);
}

const string Suffix(const string &filename) {
  return string(Suffix(filename.c_str()));
}

string StripBasename(const char *filename) {
  const char *base = strrchr(filename, '/');
  if (!base) return(string(""));
  string sfilename(filename);
  return sfilename.substr(0, base - filename);
}

string StripBasename(const string &filename) {
  return StripBasename(filename.c_str());
}

bool Readable(const string &filename) {
  const int fdes = open(filename.c_str(), O_RDONLY);
  if (fdes == -1) return false;
  close(fdes);
  return true;
}

void ReadFileToStringOrDie(const string &file, string *store) {
  std::ifstream stream(file.c_str(), std::ios::in);
  if (stream.fail()) {
    if (file.empty()) {
      LOG(FATAL) << "No file specified for reading";
    } else {
      LOG(FATAL) << "Can't open file " << file << " for reading";
    }
  }
  stream.seekg(0, std::ios::end);
  const size_t length = stream.tellg();
  stream.seekg(0, std::ios::beg);
  char *buf = new char[length];
  stream.read(buf, length);
  store->append(buf, length);
  delete[] buf;
  stream.close();
}

// A partial (largely non-) implementation of this functionality.

bool RecursivelyCreateDir(const string &path) {
  if (path.empty()) return true;
  std::vector<string> path_comp(StringSplit(path, "/"));
  if (path[0] == '/') path_comp[0] = "/" + path_comp[0];
  struct stat stat_buf;
  string rpath;
  for (auto it = path_comp.begin(); it != path_comp.end(); ++it) {
    rpath = rpath.empty() ? *it : rpath + "/" + *it;
    const char *crpath = rpath.c_str();
    const int statval = stat(crpath, &stat_buf);
    if (statval == 0) {
      if (S_ISDIR(stat_buf.st_mode)) continue;
      return false;
    } else {
      if (mkdir(crpath, ACCESSPERMS) == -1) return false;
    }
  }
  return true;
}

File *Open(const string &filename, const string &mode) {
  std::ios_base::openmode m = static_cast<std::ios_base::openmode>(0);
  if (mode.find('r') != string::npos) m |= std::ios::in;
  if (mode.find('w') != string::npos) m |= std::ios::out;
  if (mode.find('a') != string::npos) m |= std::ios::app;
  auto *streamptr = new std::fstream(filename.c_str(), m);
  if (streamptr->fail()) {
    delete streamptr;
    return nullptr;
  }
  return new File(streamptr);
}

File *OpenOrDie(const string &filename, const string &mode) {
  auto *file = Open(filename, mode);
  if (!file) {
    if (filename.empty()) {
      LOG(FATAL) << "No file specified";
    } else {
      LOG(FATAL) << "Can't open file " << filename << " for reading";
    }
  }
  return file;
}

}  // namespace thrax
