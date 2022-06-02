#pragma once

#include "ICollection.h"

namespace NSTypes
{
    enum class EError
    {
        EE_NO_ITEMS,
        EE_INDEX_OUT_OF_BOUNDS,
        EE_OK,
        EE_UNEXPECTED
    };

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

                if (FCount())
                {
                    for (size_t i = 0; i < FCount(); ++i)
                    {
                        if (m_items[i] == nullptr)
                        {
                            tempItems[i] = nullptr;
                            continue;
                        }

                        tempItems[i + 1] = new TItem();
                        tempItems[i + 1]->FSet(m_items[i]->FGet());
                    }
                }

                FClear();

                m_items = new TItem*[tempCount];
                m_count = tempCount;

                for (size_t i = 0; i < tempCount; ++i)
                {
                    if (tempItems[i] == nullptr)
                    {
                        m_items[i] = nullptr;
                        continue;
                    }

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
                if (!FCount())
                {
                    m_lastError = EError::EE_NO_ITEMS;
                    return TValue();
                }

                TItem** tempItems = new TItem*[FCount() - 1];
                size_t tempCount = FCount() - 1;
                TValue item = m_items[0]->FGet();

                for (size_t i = 1; i < FCount(); ++i)
                {
                    if (m_items[i] == nullptr)
                    {
                        tempItems[i] = nullptr;
                        continue;
                    }

                    tempItems[i - 1] = new TItem();
                    tempItems[i - 1]->FSet(m_items[i]->FGet());
                }

                FClear();

                m_items = new TItem*[tempCount];
                m_count = tempCount;

                for (size_t i = 0; i < tempCount; ++i)
                {
                    if (tempItems[i] == nullptr)
                    {
                        m_items[i] = nullptr;
                        continue;
                    }

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

            void FPushBack(TValue item)
            {
                TItem** tempItems = new TItem*[FCount() + 1];
                size_t tempCount = FCount() + 1;
                tempItems[FCount()] = new TItem();
                tempItems[FCount()]->FSet(item);

                if (FCount())
                {
                    for (size_t i = 0; i < FCount(); ++i)
                    {
                        if (m_items[i] == nullptr)
                        {
                            tempItems[i] = nullptr;
                            continue;
                        }

                        tempItems[i] = new TItem();
                        tempItems[i]->FSet(m_items[i]->FGet());
                    }
                }

                FClear();
                
                m_items = new TItem*[tempCount];
                m_count = tempCount;

                for (size_t i = 0; i < tempCount; ++i)
                {
                    if (tempItems[i] == nullptr)
                    {
                        m_items[i] = nullptr;
                        continue;
                    }

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
                if (!FCount())
                {
                    m_lastError = EError::EE_NO_ITEMS;
                    return TValue();
                }

                TItem** tempItems = new TItem*[FCount() - 1];
                size_t tempCount = FCount() - 1;
                TValue item = m_items[FCount() - 1]->FGet();
                
                for (size_t i = 0; i < tempCount; ++i)
                {
                    if (m_items[i] == nullptr)
                    {
                        tempItems[i] = nullptr;
                        continue;
                    }

                    tempItems[i] = new TItem();
                    tempItems[i]->FSet(m_items[i]->FGet());
                }

                FClear();

                m_items = new TItem*[tempCount];
                m_count = tempCount;

                for (size_t i = 0; i < tempCount; ++i)
                {
                    if (tempItems[i] == nullptr)
                    {
                        m_items[i] = nullptr;
                        continue;
                    }

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

            void FInsertAt(TValue item, size_t index)
            {
                if (!FCount())
                {
                    m_lastError = EError::EE_NO_ITEMS;
                    return;
                }

                if (index > FCount() - 1)
                {
                    m_lastError = EError::EE_INDEX_OUT_OF_BOUNDS;
                    return;
                }

                TItem **tempItems = new TItem*[FCount() + 1];
                size_t tempCount = FCount() + 1;

                for (size_t i = 0; i < tempCount; ++i)
                {
                    if (i < index)
                    {
                        if (m_items[i] == nullptr)
                        {
                            tempItems[i] = nullptr;
                            continue;
                        }

                        tempItems[i] = new TItem();
                        tempItems[i]->FSet(m_items[i]->FGet());
                    }
                    else if (i == index)
                    {
                        tempItems[i] = new TItem();
                        tempItems[i]->FSet(item);
                    }
                    else if (i > index)
                    {
                        if (m_items[i] == nullptr)
                        {
                            tempItems[i] = nullptr;
                            continue;
                        }

                        tempItems[i] = new TItem();
                        tempItems[i]->FSet(m_items[i - 1]->FGet());
                    }
                }
                
                FClear();

                m_items = new TItem*[tempCount];
                m_count = tempCount;

                for (size_t i = 0; i < tempCount; ++i)
                {
                    if (tempItems[i] == nullptr)
                    {
                        m_items[i] = nullptr;
                        continue;
                    }

                    m_items[i] = new TItem();
                    m_items[i]->FSet(tempItems[i]->FGet());
                }

                for (size_t i = 0; i < FCount(); ++i)
                {
                    SAFE_DELETE(tempItems[i]);
                }

                SAFE_DELETE_ARRAY(tempItems);

                m_lastError = EError::EE_OK;
                return;
            }

            size_t FRemove(TValue item)
            {
                size_t itemsRemoved = 0;
                for (size_t i = 0; i < FCount(); ++i)
                {
                    if (m_items[i] == nullptr)
                        continue;

                    if (m_items[i]->FGet() == item)
                    {
                        SAFE_DELETE(m_items[i]);
                        ++itemsRemoved;
                    }
                }

                return itemsRemoved;
            }

            void FErase(size_t index)
            {
                if (!FCount())
                {
                    m_lastError = EError::EE_NO_ITEMS;
                    return;
                }

                if (index > FCount() - 1)
                {
                    m_lastError = EError::EE_INDEX_OUT_OF_BOUNDS;
                    return;
                }

                for (size_t i = 0; i < FCount(); ++i)
                {
                    if (i == index)
                    {
                        SAFE_DELETE(m_items[i]);
                        m_lastError = EError::EE_OK;
                        return;
                    }
                }

                m_lastError = EError::EE_UNEXPECTED;
                return;
            }

            void FSet(TValue item, size_t index)
            {
                if (!FCount())
                {
                    m_lastError = EError::EE_NO_ITEMS;
                    return;
                }

                if (index > FCount() - 1)
                {
                    m_lastError = EError::EE_INDEX_OUT_OF_BOUNDS;
                    return;
                }

                for (size_t i = 0; i < FCount(); ++i)
                {
                    if (m_items[i] == nullptr)
                        continue;

                    if (i == index)
                    {
                        m_items[i]->FSet(item);
                        m_lastError = EError::EE_OK;
                        return;
                    }
                }

                m_lastError = EError::EE_UNEXPECTED;
            }

            TValue FGet(size_t index)
            {
                if (!FCount())
                {
                    m_lastError = EError::EE_NO_ITEMS;
                    return TValue();
                }

                if (index > FCount() - 1)
                {
                    m_lastError = EError::EE_INDEX_OUT_OF_BOUNDS;
                    return TValue();
                }

                for (size_t i = 0; i < FCount(); ++i)
                {
                    if (m_items[i] == nullptr)
                        continue;

                    if (i == index)
                    {
                        m_lastError = EError::EE_OK;
                        return m_items[i]->FGet();
                    }
                }

                m_lastError = EError::EE_UNEXPECTED;
                return TValue();
            }

            TValue FFront()
            {
                if (!FCount())
                {
                    m_lastError = EError::EE_NO_ITEMS;
                    return TValue();
                }

                return m_items[0]->FGet();
            }

            TValue FBack()
            {
                if (!FCount())
                {
                    m_lastError = EError::EE_NO_ITEMS;
                    return TValue();
                }

                return m_items[FCount()]->FGet();
            }

            TValue FActiveFront()
            {
                if (!FCount())
                {
                    m_lastError = EError::EE_NO_ITEMS;
                    return TValue();
                }

                size_t index = 0;
                while (index < FCount())
                {
                    if (m_items[index] != nullptr)
                    {
                        m_lastError = EError::EE_OK;
                        return m_items[index]->FGet();
                    }

                    ++index;
                }

                m_lastError = EError::EE_UNEXPECTED;
                return TValue();
            }

            TValue FActiveBack()
            {
                if (!FCount())
                {
                    m_lastError = EError::EE_NO_ITEMS;
                    return TValue();
                }

                size_t index = FCount() - 1;
                while (index >= 0)
                {
                    if (m_items[index] != nullptr)
                    {
                        m_lastError = EError::EE_OK;
                        return m_items[index]->FGet();
                    }

                    --index;
                }

                m_lastError = EError::EE_UNEXPECTED;
                return TValue();
            }

            size_t FActiveCount()
            {
                if (!FCount())
                    return 0;

                size_t activeCount = 0;

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

            EError FGetLastError()
            {
                return m_lastError;
            }

        private:
            class TItem
            {
                public:
                    TItem()
                    {
                    }

                    TItem(const TItem& item)
                    {
                        m_item = item->FGet();
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
            EError m_lastError;
    };
}
