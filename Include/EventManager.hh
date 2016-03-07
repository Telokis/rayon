#pragma once

#ifndef RAYON_EVENTMANAGER_HH_
#define RAYON_EVENTMANAGER_HH_

#include <string>
#include <map>
/*
namespace RayOn
{

  typedef	void(*t_callback)(void *, void *);

  class	EventManager
  {
  public:
    EventManager();
    ~EventManager();
    void		on(const std::string &event, const std::string &id, t_callback callback, void *param);
    void		cancel(const std::string &event, const std::string &id);
    void		trigger(const std::string &event, void *triggerParam);

    class	EventHandler
    {
    public:
      EventHandler(const std::string &name, t_callback func, void *param);
      ~EventHandler();
      void		call(void *triggerParam);

    private:
      EventHandler(const EventHandler &model);
      EventHandler	&operator=(const EventHandler &model);
      std::string		_name;
      void		*_param;
      t_callback		_func;
    };

  private:
    EventManager(const EventManager &model);
    EventManager		&operator=(const EventManager &model);
    std::map<std::string, std::map<std::string, EventManager::EventHandler *> >	_events;
  };

  typedef	std::map<std::string, std::map<std::string, EventManager::EventHandler *> >	t_collection;
  typedef Singleton<EventManager>	InternalEvents;

} // namespace RayOn
*/
#endif // RAYON_EVENTMANAGER_HH_ 