#pragma once

#include <array>
#include <utility>
#include <optional>

namespace custom {

template<typename K, typename V>
struct const_mpair
{
    K key;
    V value;
};

template<std::size_t Size, typename Key, typename Value>
class const_map
{
    using Container = std::array<const_mpair<Key, Value>, Size>;

    private:
        Container m_data;

    public:
        constexpr explicit const_map(Container newData) : m_data(newData)
        {}

        constexpr void operator=(Container newData)
        {
            m_data = newData;
        }

        [[nodiscard]] constexpr std::optional<Value> at(const Key& key) const
        {
            for(const auto& entry : m_data)
            {
                if(entry.key == key)
                    return entry.value;
            }
            return {};
        }

        [[nodiscard]] constexpr std::optional<Value> operator[](const Key& key) const
        {
            return this->at(key);
        }

        [[nodiscard]] constexpr bool assign(const Key& key, const Value& value)
        {
            for(auto& entry : m_data)
            {
                if(entry.key == key)
                {
                    entry.value = value;
                    return true;
                }
            }
            return false;
        }

        [[nodiscard]] constexpr bool empty() const
        {
            return count() == 0;
        }

        [[nodiscard]] constexpr void erase(const Key& key)
        {
            for (auto& entry : m_data)
                if (entry.key == key)
                    entry.value = 0;
        }

        [[nodiscard]] constexpr std::size_t count() const
        {
            return Size;
        }

        [[nodiscard]] constexpr bool contains(const Key& key) const
        {
            for (auto& entry : m_data)
                if (entry.key == key)
                    return true;
            return false;
        }

        [[nodiscard]] constexpr typename Container::const_iterator cbegin() const
        {
            return m_data.cbegin();
        }

        [[nodiscard]] constexpr typename Container::const_iterator cend() const
        {
            return m_data.cend();
        }
};
}