#ifndef CMDCUSTOMMAP_HPP_INCLUDED
#define CMDCUSTOMMAP_HPP_INCLUDED

#include <map>
#include <string>

class CustomMap {
   private:
    std::map<std::string, std::string> *map;

   public:
    CustomMap(std::map<std::string, std::string> *map);
    std::string getOrDefault(std::string key, std::string def_value);
};

#endif
