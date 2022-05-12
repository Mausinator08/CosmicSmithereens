#pragma once

#include "ICollection.h"

namespace NSTypes
{
    template<class TValue>
    class CCollection: public ICollection
    {
        public:
            CCollection()
            {
                m_items = nullptr;
                m_count = 0;
            }

            CCollection(const CCollection &collection)
            {
                m_items = new TItem*[collection.FCount()];
                m_count = collection.FCount();

                size_t count = 0;
                while(collection.FCount() > 0)
                {
                    TValue item = collection.FPopFront();
                    m_items[count] = new TItem();
                    m_items[count]->FSet(item);
                    ++count;
                }
            }

            ~CCollection()
            {
                FClear();
            }

            void FPushFront(TValue item)
            {
                TItem** tempItems = new TItem*[FCount() + 1];
                size_t tempCount = FCount() + 1;
                tempItems[0] = new TItem();
                tempItems[0]->FSet(item);

                for (size_t i = 0; i < FCount(); ++i)
                {
                    tempItems[i + 1] = new TItem();
                    tempItems[i + 1]->FSet(m_items[i]->FGet());
                }

                FClear();

                m_items = new TItem*[tempCount];
                m_count = tempCount;

                for (size_t i = 0; i < tempCount; ++i)
                {
                    m_items[i] = new TItem();
                    m_items[i]->FSet(tempItems[i]->FGet());
                }

                if (FCount())
                {
                    for (size_t i = 0; i < FCount(); ++i)
                    {
                        SAFE_DELETE(tempItems[i]);
                    }
                }

                SAFE_DELETE_ARRAY(tempItems);
            }

            TValue FPopFront()
            {
                TItem** tempItems = new TItem*[FCount() - 1];
                size_t tempCount = FCount() - 1;
                TValue item = m_items[0]->FGet();

                for (size_t i = 1; i < FCount(); ++i)
                {
                    tempItems[i - 1] = TItem();
                    tempItems[i - 1]->FSet(m_items[i]->FGet());
                }

                FClear();

                m_items = new TItem*[tempCount];
                m_count = tempCount;

                for (size_t i = 0; i < tempCount; ++i)
                {
                    m_items[i] = TItem();
                    m_items[i].FSet(tempItems[i]->FGet());
                }

                if (FCount())
                {
                    for (size_t i = 0; i < FCount(); ++i)
                    {
                        SAFE_DELETE(tempItems[i]);
                    }
                }

                SAFE_DELETE_ARRAY(tempItems);

                return item;
            }

            void FPushBack(TValue item)
            {
                TItem** tempItems = new TItem*[FCount() + 1];
                size_t tempCount = FCount() + 1;
                tempItems[FCount()] = new TItem();
                tempItems[FCount()]->FSet(item);

                for (size_t i = 0; i < FCount(); ++i)
                {
                    tempItems[i] = new TItem();
                    tempItems[i]->FSet(m_items[i]->FGet());
                }

                FClear();
                
                m_items = new TItem*[tempCount];
                m_count = tempCount;

                for (size_t i = 0; i < tempCount; ++i)
                {
                    m_items[i] = new TItem();
                    m_items[i]->FSet(tempItems[i]->FGet());
                }

                if (FCount())
                {
                    for (size_t i = 0; i < FCount(); ++i)
                    {
                        SAFE_DELETE(tempItems[i]);
                    }
                }

                SAFE_DELETE_ARRAY(tempItems);
            }

            TValue FPopBack()
            {
                TItem** tempItems = new TItem*[FCount() - 1];
                size_t tempCount = FCount() - 1;
                TValue item = m_items[FCount() - 1]->FGet();
                
                for (size_t i = 0; i < tempCount; ++i)
                {
                    tempItems[i] = new TItem();
                    tempItems[i]->FSet(m_items[i]->FGet());
                }

                FClear();

                m_items = new TItem*[tempCount];
                m_count = tempCount;

                for (size_t i = 0; i < tempCount; ++i)
                {
                    m_items[i] = new TItem();
                    m_items[i]->FSet(tempItems[i]->FGet());
                }

                if (FCount())
                {
                    for (size_t i = 0; i < FCount(); ++i)
                    {
                        SAFE_DELETE(tempItems[i]);
                    }
                }

                SAFE_DELETE_ARRAY(tempItems);
                
                return item;
            }

            int FInsertAt(TValue item, size_t index)
            {
                if (!FCount())
                    return 1;

                if (index < 0)
                {
                    return 3;
                }

                if (index > FActiveCount() - 1)
                {
                    return 4;
                }

                for (size_t activeIndex = 0, i = 0; activeIndex < FActiveCount() && i < FCount(); ++i)
                {
                    if (m_items[i] == nullptr)   
                        continue;

                    if (activeIndex == index)
                    {
                        TItem **tempItems = new TItem*[FCount() + 1];
                        size_t tempCount = FCount() + 1;

                        for (size_t j = 0; j < FCount(); ++j)
                        {
                            if (j < i)
                            {
                                tempItems[j] = new TItem();
                                tempItems[j]->FSet(m_items[j]->FGet());
                            }
                            else if (j == i)
                            {
                                tempItems[j] = new TItem();
                                tempItems[j]->FSet(item);
                            }
                            else if (j > i)
                            {
                                tempItems[j + 1] = new TItem();
                                tempItems[j + 1]->FSet(m_items[j]->FGet());
                            }
                        }

                        FClear();

                        m_items = new TItem*[tempCount];
                        m_count = tempCount;

                        for (size_t j = 0; j < tempCount; ++j)
                        {
                            m_items[j] = new TItem();
                            m_items[j]->FSet(tempItems[j]-FGet());
                        }

                        if (FCount())
                        {
                            for (size_t i = 0; i < FCount(); ++i)
                            {
                                SAFE_DELETE(tempItems[i]);
                            }
                        }

                        SAFE_DELETE_ARRAY(tempItems);

                        return 0;
                    }

                    ++activeIndex;
                }

                return 2;
            }

            size_t FRemove(TValue item)
            {
                size_t itemsRemoved = 0;
                for (size_t i = 0; i < FCount(); ++i)
                {
                    if (m_items[i]->Get() == item)
                    {
                        SAFE_DELETE(m_items[i]);
                        ++itemsRemoved;
                    }
                }

                return itemsRemoved;
            }

            int FErase(size_t index)
            {
                if (!FCount())
                    return 1;

                if (index < 0)
                {
                    return 3;
                }

                if (index > FActiveCount() - 1)
                {
                    return 4;
                }

                for (size_t activeIndex = 0, i = 0; activeIndex < FActiveCount() && i < FCount(); ++i)
                {
                    if (activeIndex == index)
                    {
                        SAFE_DELETE(m_items[i]);
                        return 0;
                    }

                    ++activeIndex;
                }

                return 2;
            }

            int FSet(TValue item, size_t index)
            {
                if (!FCount())
                    return 1;

                if (index < 0)
                {
                    return 3;
                }

                if (index > FActiveCount() - 1)
                {
                    return 4;
                }

                for (size_t activeIndex = 0, i = 0; activeIndex < FActiveCount() && i < FCount(); ++i)
                {
                    if (m_items[i] == nullptr)
                    {   
                        continue;
                    }

                    if (activeIndex == index)
                    {
                        m_items[i]->FSet(item);
                        return 0;
                    }

                    ++activeIndex;
                }

                return 2;
            }

            int FGet(size_t index, TValue* itemOut)
            {
                if (!FCount())
                    return 1;

                itemOut = nullptr;

                if (index < 0)
                {
                    return 3;
                }

                if (index > FActiveCount() - 1)
                {
                    return 4;
                }

                for (size_t activeIndex = 0, i = 0; activeIndex < FActiveCount() && i < FCount(); ++i)
                {
                    if (m_items[i] == nullptr)
                    {   
                        continue;
                    }

                    if (activeIndex == index)
                    {
                        itemOut = &(m_items[i]->FGet());
                        return 0;
                    }

                    ++activeIndex;
                }

                return 2;
            }

            int FFront(TValue* itemOut)
            {
                if (!FCount())
                    return 1;

                itemOut = nullptr;
                size_t index = 0;
                while (index < FCount())
                {
                    if (m_items[index] != nullptr)
                    {
                        itemOut = &(m_items[index]->FGet());
                        return 0;
                    }

                    ++index;
                }

                return 2;
            }

            int FBack(TValue* itemOut)
            {
                if (!FCount())
                    return 1;

                itemOut = nullptr;
                size_t index = FCount() - 1;
                while (index >= 0)
                {
                    if (m_items[index] != nullptr)
                    {
                        itemOut = &(m_items[index]->FGet());
                        return 0;
                    }

                    --index;
                }

                return 2;
            }

            size_t FActiveCount()
            {
                if (!FCount())
                    return 0;

                size_t activeCount;

                for (size_t i = 0; i < FCount(); ++i)
                {
                    if (m_items[i] == nullptr)
                        continue;

                    activeCount += 1;
                }

                return activeCount;
            }

            size_t FCount()
            {
                return m_count;
            }

            size_t FActiveSize()
            {
                if (!FCount())
                    return 0;

                size_t activeSize = 0;

                for (size_t i = 0; i < FCount(); ++i)
                {
                    if (m_items[i] == nullptr)
                        continue;

                    activeSize += sizeof(m_items[i]->FGet());
                }

                return activeSize;
            }

            size_t FSize()
            {
                if (!FCount())
                    return 0;

                size_t size = 0;
                for (size_t i = 0; i < FCount(); ++i)
                {
                    size += sizeof(m_items[i]->FGet());
                }

                return size;
            }

            void FClear()
            {
                if (FCount())
                {
                    for (size_t i = 0; i < FCount(); ++i)
                    {
                        SAFE_DELETE(m_items[i]);
                    }
                }

                SAFE_DELETE_ARRAY(m_items);

                m_count = 0;
            }

        private:
            class TItem
            {
                public:
                    TItem()
                    {
                        
                    }

                    ~TItem()
                    {
                        
                    }

                    TValue FGet()
                    {
                        return m_item;
                    }

                    void FSet(TValue item)
                    {
                        m_item = item;
                    }
                
                private:
                    TValue m_item;
            };

            TItem** m_items;
            size_t m_count;
    };
}
