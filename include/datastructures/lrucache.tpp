#ifndef _LRU_CACHE
#define _LRU_CACHE

#include <unordered_map>
#include <memory>
#include <iterator>
#include <list>
#include <optional>

// Some tests here
//@TODO extensive testing required
// https://godbolt.org/z/nssfqj187

template<typename key,typename dataType,std::size_t size = 4>
class lru_cache
{
    private:
        typedef typename std::list<dataType>::iterator list_iterator;
        std::list<dataType> data_list_;
        std::unordered_map<key,list_iterator> umap_; // key -> datatype
    public:
        lru_cache()=default;
        std::optional<dataType> get(key searchKey)
        {
            if(umap_.find(searchKey)!=umap_.end())
            {
                list_iterator foundEntry = umap_[searchKey];
                dataType ret = std::move(*foundEntry);
                data_list_.erase(umap_[searchKey]);
                umap_.erase(umap_.find(searchKey));
                return ret;
            }
            return std::nullopt;
        }
        void add(key searchKey,dataType && data)
        {
            if(umap_.find(searchKey)!=umap_.end())  
            {
                data_list_.erase(umap_[searchKey]);
                umap_.erase(umap_.find(searchKey));
            } 
            if(data_list_.size()>=size)
            {
                list_iterator backentry = data_list_.end();
                umap_.erase(umap_.find(searchKey));
                data_list_.erase(backentry);
            }
            data_list_.push_front(data);
            umap_[searchKey] = data_list_.begin();
        }
};

#endif //_LRU_CACHE