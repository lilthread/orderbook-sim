#pragma once
#include "Common.hpp"
#include <vector>
namespace Orderbook::inline v1 
{
class Trade final {
  struct Info {
    OrderId id;
    Quantity quantity;
    Price price;
  }_bidTrade, _askTrade;
public:
  [[nodiscard]] explicit Trade(const Info& bidTrade, const Info& askTrade) noexcept
    : _bidTrade{bidTrade}
    , _askTrade{askTrade} {}

  [[nodiscard]] Info const& GetBidTrade() const noexcept { return _bidTrade; }
  [[nodiscard]] Info const& GetAskTrade() const noexcept { return _bidTrade; }
};

using Trades = std::vector<Trade>;
}
