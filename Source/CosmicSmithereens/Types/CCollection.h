namespace NSTypes
{
    template<class TKey, class TValue>
    class CCollection
    {
        public:
            CCollection()
            {
                
            }

            CCollection(const CCollection &collection)
            {
                while(collection.FCount() > 0)
                {
                    TValue item = collection.FPopFront();
                    this->FPushBack(item);
                }
            }

            ~CCollection()
            {
                while(this->FCount() > 0)
                {
                    this->FPopBack();
                }
            }

            void FPushFront(TValue item)
            {
                m_items.push_front(item);
            }

            TValue FPopFront()
            {
                return m_items.pop_front();
            }

            void FPushBack(TValue item)
            {
                m_items.push_back(item);
            }

            TValue FPopBack()
            {
                return m_items.pop_back();
            }

            void FInsertAt(TValue item, TKey index)
            {
                m_items.insert(std::pair<TKey, TValue>(index, item));
            }

            void FRemove(TValue item)
            {
                m_items.erase(m_items.at(index));
            }

            void FSet(TValue item, TKey index)
            {
                m_items.erase(m_items.at(index));
                m_items.insert(std::pair<TKey, TValue>(index, item));
            }

            TValue FGet(TKey index)
            {
                return m_items.at(index);
            }

            TValue FFront()
            {
                return m_items.at(0);
            }

            TValue FBack()
            {
                return m_items.at(m_items.count() - 1);
            }

            TKey FCount()
            {
                return m_items.count();
            }

            void FClear()
            {
                m_items.clear();
            }

        private:
            std::map<TKey, TValue> m_items;
    };
}
