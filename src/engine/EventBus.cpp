#include "vida/engine/EventBus.hpp"
#include "vida/logger.h"
#include <algorithm>

namespace Vida {
namespace Event {

void EventBus::Register(std::shared_ptr<Subscriber> sub) {
  Prune();
  subs.push_back({sub});
}

void EventBus::Prune() {
  subs.erase(std::remove_if(subs.begin(), subs.end(),
                            [](const SubEntry &e) { return e.sub.expired(); }),
             subs.end());
}

std::shared_ptr<Subscriber> Subscriber::make(EventBus &bus) {
  auto sub = std::shared_ptr<Subscriber>(new Subscriber(bus));
  bus.Register(sub);
  return sub;
}

void Subscriber::Sub(const Publisher &pub) {
  auto &entry = tags[pub.Tag()];
  entry.all = true;
  entry.types.clear(); // all supersedes specific types
  vida_log(VIDA_LOG_INFO, "subscribed to all events from '%s'",
           pub.Tag().c_str());
}

void Subscriber::Unsub(const Publisher &pub) {
  tags.erase(pub.Tag());
  vida_log(VIDA_LOG_INFO, "unsubscribed from '%s'", pub.Tag().c_str());
}

bool Subscriber::SubscribedTo(const std::string &tag) const {
  return tags.count(tag) > 0;
}

} // namespace Event
} // namespace Vida
