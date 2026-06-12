#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Vida {
namespace Event {

using EventHandler = std::function<void()>;

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

  void Broadcast(const std::string &event);

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

  void On(const std::string &event, EventHandler handler);
  void Unhandle(const std::string &event);

  void Sub(const std::string &tag);
  void Sub(const Publisher &pub);
  void Unsub(const std::string &tag);

  bool Handles(const std::string &event) const;
  bool SubscribedTo(const std::string &tag) const;

private:
  explicit Subscriber(EventBus &bus) : bus(bus) {}

  EventBus &bus;
  std::map<std::string, EventHandler> handlers;
  std::vector<std::string> tags;

  friend class EventBus;
  friend class Publisher;
};

class Publisher {
public:
  Publisher(EventBus &bus, const std::string &tag) : bus(bus), tag(tag) {}

  Publisher(const Publisher &) = delete;
  Publisher &operator=(const Publisher &) = delete;
  Publisher(Publisher &&) = default;
  Publisher &operator=(Publisher &&) = delete;

  void Emit(const std::string &event);
  const std::string &Tag() const { return tag; }

private:
  EventBus &bus;
  std::string tag;
};

} // namespace Event
} // namespace Vida
