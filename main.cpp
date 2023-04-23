#include <cstdint>
#include <cstdio>
#include <chrono>
#include <algorithm>
#include <random>
#include <string_view>

#include "map.hpp"

template<std::size_t S, typename K, typename V>
constexpr auto mapFiller()
{
    std::array<custom::const_mpair<K, V>, S> content = {};
    for(std::size_t i = 0; i < S; i++)
    {
        constexpr char time[] = __TIME__;
        constexpr int32_t seed = (time[0] - '0') * 100000 +
                             (time[1] - '0') * 10000 + (time[3] - '0') * 1000 +
                             (time[4] - '0') * 100 + (time[6] - '0') * 10 +
                             time[7] - '0';
        content.at(i) = { static_cast<K>(i), static_cast<V>(i * seed) };

    }
    return custom::const_map<S, K, V>{content};
}

constexpr void constMapValidator()
{
    constexpr std::size_t size = 100;
    std::printf("%s\n", __TIME__);
    constexpr custom::const_map<size, uint32_t, int32_t> cmap = mapFiller<size, uint32_t, int32_t>();


    constexpr int32_t valueAt0 = cmap.at(0).value_or(-1);
    constexpr int32_t valueAt1 = cmap.at(1).value_or(-1);

    constexpr int32_t valueBracket0 = cmap[0].value_or(-1);
    constexpr int32_t valueBracket1 = cmap[1].value_or(-1);

    constexpr std::size_t index       = size + 1;
    constexpr int32_t     valNotFound = cmap[index].value_or(-1);

    std::printf("K: .at(%i),\tV: %i\n", 0,     valueAt0);
    std::printf("K: .at(%i),\tV: %i\n", 1,     valueAt1);
    std::printf("K: [%i],\t\tV: %i\n",  0,     valueBracket0);
    std::printf("K: [%i],\t\tV: %i\n",  1,     valueBracket1);
    std::printf("K: [%i],\tV: %i\n",    index, valNotFound);

    std::for_each(cmap.cbegin(), cmap.cend(), [](const auto kv) constexpr -> void {
        std::printf("Key -> %i, Value -> %i\n", kv.key, kv.value);
    });
}

int main()
{
    using namespace std::chrono;

    const steady_clock::time_point begin = std::chrono::steady_clock::now();
    constMapValidator();
    const steady_clock::time_point end = std::chrono::steady_clock::now();
    const auto ms = duration_cast<microseconds>(end - begin).count();

    std::printf("%i ms\n", ms);
    return 0;
}