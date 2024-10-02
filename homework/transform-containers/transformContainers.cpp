#include "transformContainers.hpp"
#include <iterator>
#include <unordered_set>
#include "algorithm"

std::map<int, std::string> removeDuplicateAndTranformToMap(std::list<std::string> str_l, std::deque<int> deq) {
    std::unordered_set<int> seen;

    std::map<int, std::string> result;
    str_l.sort();
    str_l.unique();

    deq.erase(std::remove_if(begin(deq), end(deq), [&seen](const auto& x) {
                  if (seen.find(x) == end(seen)) {
                      seen.insert(x);
                      return false;
                  }

                  return true;
              }),
              end(deq));

    std::transform(begin(deq), end(deq),
                   begin(str_l),
                   std::inserter(result, end(result)),
                   [](const auto& x, const auto& str) {
                       return std::make_pair(x, str);
                   });

    return result;
}
