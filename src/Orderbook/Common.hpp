#pragma once
#include <vector>
#include <cstddef>
namespace Orderbook::inline v1 
{

enum class Side : bool { Buy, Sell };

using OrderId = std::size_t;
using Price = double;
using Quantity = std::size_t;

static constexpr Price InvalidPrice = std::numeric_limits<Price>::quiet_NaN();

struct LevelInfo final {
  Price price;
  Quantity quantity;
};
using LevelInfos = std::vector<LevelInfo>;


}

