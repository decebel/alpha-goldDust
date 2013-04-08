#pragma once
#include <map>

template
<
   class AbstractProduct,
   typename IdentifierType,
   typename ProductCreator
>
class FactoryT
{
public:
   bool Register(const IdentifierType& id, ProductCreator creator)
   {
      return associations_.insert(
         AssocMap::value_type(id, creator)).second;
   }
   bool Unregister(const IdentifierType& id)
   {
      return associations_.erase(id) == 1;
   }
   AbstractProduct* CreateObject(const IdentifierType& id)
   {
      typename AssocMap::const_iterator i =
         associations_.find(id);
      if (i != associations_.end())
      {
         return (i->second)();
      }
      handle error
   }
private:
   typedef std::map<IdentifierType, AbstractProduct> AssocMap;
   AssocMap associations_;
};
