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
// STL container functions.

#ifndef THRAX_COMPAT_STL_FUNCTIONS_H_
#define THRAX_COMPAT_STL_FUNCTIONS_H_

namespace thrax {

template <class ForwardIterator>
void STLDeleteContainerPointers(ForwardIterator begin,
                                ForwardIterator end) {
  while (begin != end) {
    ForwardIterator temp = begin;
    ++begin;
    delete *temp;
  }
}

template <class ForwardIterator>
void STLDeleteContainerPairPointers(ForwardIterator begin,
                                    ForwardIterator end) {
  while (begin != end) {
    ForwardIterator temp = begin;
    ++begin;
    delete temp->first;
    delete temp->second;
  }
}

template <class ForwardIterator>
void STLDeleteContainerPairSecondPointers(ForwardIterator begin,
                                          ForwardIterator end) {
  while (begin != end) {
    ForwardIterator temp = begin;
    ++begin;
    delete temp->second;
  }
}

template <class T>
void STLDeleteElements(T *container) {
  if (!container) return;
  STLDeleteContainerPointers(container->begin(), container->end());
  container->clear();
}

template <typename T>
void STLDeleteValues(T *v) {
  if (!v) return;
  STLDeleteContainerPairSecondPointers(v->begin(), v->end());
  v->clear();
}

template <class Collection>
const typename Collection::value_type::second_type
&FindOrDie(const Collection &collection,
          const typename Collection::value_type::first_type &key) {
  const auto it = collection.find(key);
  if (it == collection.end())  {
    LOG(FATAL) << "Map key not found: " << key;
  }
  return it->second;
}

template <class Collection>
const typename Collection::value_type::second_type
*FindOrNull(const Collection& collection,
           const typename Collection::value_type::first_type &key) {
  const auto it = collection.find(key);
  if (it == collection.end()) {
    return nullptr;
  }
  return &it->second;
}

template <class Collection>
typename Collection::value_type::second_type
*FindOrNull(Collection &collection,
           const typename Collection::value_type::first_type &key) {
  auto it = collection.find(key);
  if (it == collection.end()) {
    return 0;
  }
  return &it->second;
}

template <class Collection>
bool InsertIfNotPresent(Collection *const collection,
    const typename Collection::value_type::first_type& key,
    const typename Collection::value_type::second_type& value) {
  return collection->emplace(key, value).second;
}

template <class Collection>
typename Collection::value_type::second_type *const
InsertOrReturnExisting(Collection *const collection,
                       const typename Collection::value_type &vt) {
  const auto ret = collection->insert(vt);
  if (ret.second) {
    return nullptr;  // Inserted, no existing previous value.
  } else {
    return &ret.first->second;  // Return address of already existing value.
  }
}

// Same as above, except for explicit key and data.
template <class Collection>
typename Collection::value_type::second_type *const
InsertOrReturnExisting(Collection *const collection,
    const typename Collection::value_type::first_type &key,
    const typename Collection::value_type::second_type &data) {
  return InsertOrReturnExisting(collection, {key, data});
}

template <class T>
void MapUtilAssignNewDefaultInstance(T **location) {
  *location = new T();
}                                  

template <class T>
typename T::value_type::second_type
LookupOrInsertNew(T *const collection,
                  const typename T::value_type::first_type &key) {
  auto result = collection->emplace(key,
      static_cast<typename T::value_type::second_type>(nullptr));
  if (result.second) MapUtilAssignNewDefaultInstance(&(result.first->second));
  return result.first->second;
}

}  // namespace thrax

#endif  // THRAX_COMPAT_STL_FUNCTIONS_H_
