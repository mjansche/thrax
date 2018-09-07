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
// A registry for named functions to be used by the compiler. The function of
// the registry is to allow users to define new functions easily so that the
// compiler is extensible.

#ifndef THRAX_COMPAT_REGISTRY_H_
#define THRAX_COMPAT_REGISTRY_H_

#include <map>
#include <string>

#include <thrax/compat/stlfunctions.h>

namespace thrax {

using std::string;

template <class T>
class Registry {
 public:
  Registry() = default; 

  ~Registry() {
    STLDeleteValues(&registry_);
  };

  void Register(const string &name, T object) {
    // Will silently do nothing if already present.
    registry_.emplace(name, object);
  }

  T Get(const string &name) {
    const auto it = registry_.find(name);
    return it == registry_.end() ? nullptr : it->second;
  }

  const T Get(const string &name) const {
    const auto it = registry_.find(name);
    return it == registry_.end() ? nullptr : it->second;
  }

 private:
  std::map<string, T> registry_;

  Registry(const Registry &) = delete;
  Registry &operator=(const Registry &) = delete;
};

}  // namespace thrax

#endif  // THRAX_COMPAT_REGISTRY_H_
