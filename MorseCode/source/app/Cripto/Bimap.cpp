#include <map>
#include <vector>
#include <utility>
#include <algorithm>

/* CONST BIMAP */
template <class Key, class Value>
class Bimap : public std::vector< std::pair<Key, Value> > {
public:
  Bimap() = default;
  Bimap(const Bimap&) = default;
  Bimap(Bimap&&) = default;

  Bimap(const std::map<Key, Value>& keyToValueMap) {
    for (auto pairElement : keyToValueMap ) {
      this->emplace_back(pairElement.first, pairElement.second);
    }
  }
  
  const Value& getValueByKey(const Key& key) {
    auto ptr = std::find_if(this->begin(), this->end(), [&] (std::pair<Key, Value> const & ref) {
	return ref.first == key; });

    return ptr->second;
  }

  const Value& getValueByKey(const Key& key) const {
    auto ptr = std::find_if(this->begin(), this->end(), [&] (std::pair<Key, Value> const & ref) {
	return ref.first == key; });

    return ptr->second;
  }
  
  const Key& getKeyByValue(const Value& key) {
    auto ptr = std::find_if(this->begin(), this->end(), [&] (std::pair<Key, Value> const & ref) {
	return ref.second == key; });

    return ptr->first;
  }

    const Key& getKeyByValue(const Value& key) const {
    auto ptr = std::find_if(this->begin(), this->end(), [&] (std::pair<Key, Value> const & ref) {
	return ref.second == key; });

    return ptr->first;
  }

  
  Bimap& operator=(const Bimap&) = default;
  Bimap& operator=(Bimap&&) = default; 
};
