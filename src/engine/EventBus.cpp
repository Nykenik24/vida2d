#include "vida/engine/EventBus.hpp"
#include "vida/logger.h"
#include <algorithm>
#include <cstddef>
#include <stdexcept>

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

void EventBus::Broadcast(const std::string &event) {
  Prune();
  for (auto &entry : subs) {
    if (auto sub = entry.sub.lock()) {
      if (sub->Handles(event)) {
        sub->handlers.at(event)();
        vida_log(VIDA_LOG_INFO, "broadcast '%s' reached subscriber",
                 event.c_str());
      }
    }
  }
}

std::shared_ptr<Subscriber> Subscriber::make(EventBus &bus) {
  auto sub = std::shared_ptr<Subscriber>(new Subscriber(bus));
  bus.Register(sub);
  return sub;
}

void Subscriber::On(const std::string &event, EventHandler handler) {
  handlers[event] = std::move(handler);
}

void Subscriber::Unhandle(const std::string &event) {
  if (!handlers.erase(event))
    throw std::runtime_error(
        "can't unhandle: subscriber does not handle event '" + event + "'");
  vida_log(VIDA_LOG_INFO, "unhandled '%s'", event.c_str());
}

bool Subscriber::Handles(const std::string &event) const {
  return handlers.count(event) > 0;
}

void Subscriber::Sub(const std::string &tag) {
  if (SubscribedTo(tag))
    throw std::runtime_error("already subscribed to '" + tag + "'");
  tags.push_back(tag);
  vida_log(VIDA_LOG_INFO, "subscribed to '%s'", tag.c_str());
}

void Subscriber::Sub(const Publisher &pub) { Sub(pub.Tag()); }

void Subscriber::Unsub(const std::string &tag) {
  auto it = std::find(tags.begin(), tags.end(), tag);
  if (it == tags.end())
    throw std::runtime_error("can't unsub: not subscribed to '" + tag + "'");
  tags.erase(it);
  vida_log(VIDA_LOG_INFO, "unsubscribed from '%s'", tag.c_str());
}

bool Subscriber::SubscribedTo(const std::string &tag) const {
  return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

void Publisher::Emit(const std::string &event) {
  vida_log(VIDA_LOG_INFO, "emitting '%s' from '%s'", event.c_str(),
           tag.c_str());
  bus.Prune();
  size_t count = 0;
  for (auto &entry : bus.subs) {
    if (auto sub = entry.sub.lock()) {
      if (sub->SubscribedTo(tag) && sub->Handles(event)) {
        sub->handlers.at(event)();
        count++;
      }
    }
  }

  vida_log(VIDA_LOG_INFO, "emit '%s' reached %lu subscribers", event.c_str(),
           count);
}

} // namespace Event
} // namespace Vida
