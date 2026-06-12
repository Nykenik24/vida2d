#pragma once

#include "vida/logger.h"
#include <cxxabi.h>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <typeindex>
#include <vector>

namespace Vida {
namespace Event {

class Subscriber;
class Publisher;

class EventBus {
public:
  EventBus() = default;
  ~EventBus() = default;

  EventBus(const EventBus &) = delete;
  EventBus &operator=(const EventBus &) = delete;
  EventBus(EventBus &&) = default;
  EventBus &operator=(EventBus &&) = default;

  template <typename T> void Broadcast(const T &event);

private:
  struct SubEntry {
    std::weak_ptr<Subscriber> sub;
  };

  std::vector<SubEntry> subs;

  void Register(std::shared_ptr<Subscriber> sub);
  void Prune();

  friend class Subscriber;
  friend class Publisher;
};

class Subscriber : public std::enable_shared_from_this<Subscriber> {
public:
  static std::shared_ptr<Subscriber> make(EventBus &bus);

  ~Subscriber() = default;
  Subscriber(const Subscriber &) = delete;
  Subscriber &operator=(const Subscriber &) = delete;

  void Sub(const Publisher &pub);

  template <typename T> void Sub(const Publisher &pub);

  void Unsub(const Publisher &pub);
  template <typename T> void Unsub(const Publisher &pub);

  template <typename T> void On(std::function<void(T)> handler);
  template <typename T> void Unhandle();

  template <typename T> bool Handles() const;
  bool SubscribedTo(const std::string &tag) const;
  template <typename T> bool SubscribedTo(const std::string &tag) const;

private:
  explicit Subscriber(EventBus &bus) : bus(bus) {}

  struct TagEntry {
    bool all = false;
    std::vector<std::type_index> types;

    bool Matches(std::type_index t) const {
      if (all)
        return true;
      for (auto &ti : types)
        if (ti == t)
          return true;
      return false;
    }
  };

  EventBus &bus;
  std::map<std::string, TagEntry> tags;
  std::map<std::type_index, std::function<void(const void *)>> handlers;

  template <typename T>
  void Dispatch(const T &event, std::optional<std::string> from_tag);

  friend class EventBus;
  friend class Publisher;
};

template <typename T> void EventBus::Broadcast(const T &event) {
  Prune();
  for (auto &entry : subs) {
    if (auto sub = entry.sub.lock())
      sub->Dispatch(event, std::nullopt);
  }
}

class Publisher {
public:
  Publisher(EventBus &bus, const std::string &tag) : bus(bus), tag(tag) {}

  Publisher(const Publisher &) = delete;
  Publisher &operator=(const Publisher &) = delete;
  Publisher(Publisher &&) = default;
  Publisher &operator=(Publisher &&) = delete;

  template <typename T> void Emit(const T &event) {
    vida_log(VIDA_LOG_INFO, "emitting '%s' from '%s'", typeid(T).name(),
             tag.c_str());
    bus.Prune();
    size_t count = 0;
    for (auto &entry : bus.subs) {
      if (auto sub = entry.sub.lock()) {
        if (sub->SubscribedTo<T>(tag)) {
          sub->Dispatch(event, tag);
          count++;
        }
      }
    }
    vida_log(VIDA_LOG_INFO, "emit '%s' reached %zu subscribers",
             typeid(T).name(), count);
  }

  const std::string &Tag() const { return tag; }

private:
  EventBus &bus;
  std::string tag;
};

template <typename T> void Subscriber::On(std::function<void(T)> handler) {
  handlers[typeid(T)] = [h = std::move(handler)](const void *ptr) {
    h(*static_cast<const T *>(ptr));
  };
}

template <typename T> void Subscriber::Unhandle() { handlers.erase(typeid(T)); }

template <typename T> bool Subscriber::Handles() const {
  return handlers.count(typeid(T)) > 0;
}

template <typename T> void Subscriber::Sub(const Publisher &pub) {
  auto &entry = tags[pub.Tag()];
  if (entry.all)
    return;
  auto ti = std::type_index(typeid(T));
  for (auto &t : entry.types)
    if (t == ti)
      return;
  entry.types.push_back(ti);
  vida_log(VIDA_LOG_INFO, "subscribed to '%s' for type '%s'", pub.Tag().c_str(),
           typeid(T).name());
}

template <typename T> void Subscriber::Unsub(const Publisher &pub) {
  auto it = tags.find(pub.Tag());
  if (it == tags.end())
    return;
  auto ti = std::type_index(typeid(T));
  auto &types = it->second.types;
  for (auto tit = types.begin(); tit != types.end();) {
    if (*tit == ti)
      tit = types.erase(tit);
    else
      ++tit;
  }
  if (!it->second.all && types.empty())
    tags.erase(it);
}

template <typename T>
bool Subscriber::SubscribedTo(const std::string &tag) const {
  auto it = tags.find(tag);
  if (it == tags.end())
    return false;
  return it->second.Matches(typeid(T));
}

template <typename T>
void Subscriber::Dispatch(const T &event, std::optional<std::string> from_tag) {

  if (from_tag.has_value() && !SubscribedTo<T>(*from_tag))
    return;

  auto it = handlers.find(typeid(T));
  if (it == handlers.end())
    return;

  it->second(static_cast<const void *>(&event));
  vida_log(VIDA_LOG_INFO, "dispatched '%s'", typeid(T).name());
}

} // namespace Event
} // namespace Vida
