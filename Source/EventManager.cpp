//
// EventManager.cpp for nib in /home/sana_c/dev/cpp_nibbler
// 
// Made by Cedric
// Login   <sana_c@epitech.net>
// 
// Started on  Mon Mar 31 10:07:49 2014 Cedric
// Last update Mon Mar 31 12:35:06 2014 Cedric
//

#include "EventManager.hh"
/*
EventManager::EventManager()
{
}

EventManager::~EventManager()
{
  std::map<std::string, EventHandler *>::const_iterator	it2;
  std::map<std::string, EventHandler *>::const_iterator	end2;
  t_collection::const_iterator	it1;
  t_collection::const_iterator	end1;

  end1 = this->_events.end();
  for (it1 = this->_events.begin();
       it1 != end1;
       ++it1)
    {
      end2 = it1->second.end();
      for (it2 = it1->second.begin();
	   it2 != end2;
	   ++it2)
	{
	  delete (it2->second);
	}
    }
}

void		EventManager::on(const std::string &event,
				 const std::string &id,
				 t_callback callback,
				 void *param)
{
  this->cancel(event, id);
  this->_events[event][id] = new EventHandler(id, callback, param);
}

void		EventManager::cancel(const std::string &event, const std::string &id)
{
  if (this->_events.find(event) != this->_events.end() &&
      this->_events[event].find(id) != this->_events[event].end())
    {
      delete (this->_events[event][id]);
      this->_events[event].erase(id);
    }
}

void				EventManager::trigger(const std::string &event,
						      void *triggerParam)
{
  std::map<std::string, EventHandler *>::const_iterator	it;
  std::map<std::string, EventHandler *>::const_iterator	end;

  end = this->_events[event].end();
  for (it = this->_events[event].begin();
       it != end;
       ++it)
    {
      it->second->call(triggerParam);
    }
}

EventManager::EventHandler::EventHandler(const std::string &name,
					 t_callback func,
					 void *param)
  : _name(name), _param(param), _func(func)
{
}

EventManager::EventHandler::~EventHandler()
{
}

void		EventManager::EventHandler::call(void *triggerParam)
{
  this->_func(triggerParam, this->_param);
}
*/