/*
 * Copyright 2018 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Firestore/core/src/firebase/firestore/model/document_key.h"

#include <utility>

#include "Firestore/core/src/firebase/firestore/model/resource_path.h"
#include "Firestore/core/src/firebase/firestore/util/firebase_assert.h"

namespace firebase {
namespace firestore {
namespace model {

namespace {

void AssertValidPath(const ResourcePath& path) {
  FIREBASE_ASSERT_MESSAGE(DocumentKey::IsDocumentKey(path),
                          "invalid document key path: %s",
                          path.CanonicalString().c_str());
}

}  // namespace

DocumentKey::DocumentKey() : path_{std::make_shared<ResourcePath>()} {
}

DocumentKey::DocumentKey(const ResourcePath& path)
    : path_{std::make_shared<ResourcePath>(path)} {
  AssertValidPath(*path_);
}

DocumentKey::DocumentKey(ResourcePath&& path)
    : path_{std::make_shared<ResourcePath>(std::move(path))} {
  AssertValidPath(*path_);
}

DocumentKey DocumentKey::FromPathString(const absl::string_view path) {
  return DocumentKey{ResourcePath::FromString(path)};
}

DocumentKey DocumentKey::FromSegments(std::initializer_list<std::string> list) {
  return DocumentKey{ResourcePath{list}};
}

const DocumentKey& DocumentKey::Empty() {
  static DocumentKey empty;
  return empty;
}

bool DocumentKey::IsDocumentKey(const ResourcePath& path) {
  return path.size() % 2 == 0;
}

const ResourcePath& DocumentKey::path() const {
  return path_ ? *path_ : Empty().path();
}

bool operator==(const DocumentKey& lhs, const DocumentKey& rhs) {
  return lhs.path() == rhs.path();
}
bool operator!=(const DocumentKey& lhs, const DocumentKey& rhs) {
  return lhs.path() != rhs.path();
}
bool operator<(const DocumentKey& lhs, const DocumentKey& rhs) {
  return lhs.path() < rhs.path();
}
bool operator<=(const DocumentKey& lhs, const DocumentKey& rhs) {
  return lhs.path() <= rhs.path();
}
bool operator>(const DocumentKey& lhs, const DocumentKey& rhs) {
  return lhs.path() > rhs.path();
}
bool operator>=(const DocumentKey& lhs, const DocumentKey& rhs) {
  return lhs.path() >= rhs.path();
}

}  // namespace model
}  // namespace firestore
}  // namespace firebase
