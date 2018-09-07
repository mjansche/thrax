#ifndef FST_UTIL_STRING_STRIPCOMMENT_H_
#define FST_UTIL_STRING_STRIPCOMMENT_H_

#include <string>

#include <thrax/compat/utils.h>


// Defines comment syntax for string files.
//
// The comment character is '#', and has scope until the end of the line. Any
// preceding whitespace before a comment is ignored.
//
// To use the '#' literal (i.e., to ensure it is not interpreted as the start of
// a comment) escape it with '\'; the escaping '\' in "\#" also removed.
//
// TODO(rws,kbg): Merge stringfile functionality across Pynini and Thrax.

namespace fst {
namespace internal {

inline string StripComment(const string &line) {
  char prev_char = '\0';
  for (size_t i = 0; i < line.size(); ++i) {
    const char this_char = line[i];
    if (this_char == '#' && prev_char != '\\') {
      // Strips comment and any trailing whitespace.
      return string(thrax::StripTrailingAsciiWhitespace(line.substr(0, i)));
    }
    prev_char = this_char;
  }
  return line;
}

inline string RemoveEscape(const string &line) {
  return thrax::StringReplace(StripComment(line), "\\#", "#", true);
}

}  // namespace internal

inline string StripCommentAndRemoveEscape(const string &line) {
  return internal::RemoveEscape(internal::StripComment(line));
}

}  // namespace fst

#endif  // FST_UTIL_STRING_STRIPCOMMENT_H_
