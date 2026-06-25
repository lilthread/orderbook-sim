#pragma once
#include "Common.hpp"
#include <memory>
#include <stdexcept>
#include <format>
namespace Orderbook::inline v1 
{
enum class OrderType {
  LIMIT,
  MARKET,
  CANCEL
};

class Order final {
public:
  [[nodiscard]] explicit Order(OrderType type,OrderId id, Side side, Price price, Quantity quantity) noexcept 
    : _orderType{type}
    , _orderId{id}
    , _side{side}
    , _price{price}
    , _initialQuantity{quantity}
    , _remainingQuantity{quantity}{}

  void Fill(Quantity quantity) {
    if (quantity > GetRemainingQuantity())
      throw std::logic_error(std::format("Order ({}) cannot be filled for more than its remaining quantity.", GetOrderId()));

    _remainingQuantity  -= quantity;
  }
  void ToGoodTillCancel(Price price) { 
    if (GetOrderType() != OrderType::MARKET)
      throw std::logic_error(std::format("Order ({}) cannot have its price adjusted, only market orders can.", GetOrderId()));

    _price = price;
    _orderType = OrderType::LIMIT;
  }
  [[nodiscard]] OrderType GetOrderType() const noexcept { return _orderType; }
  [[nodiscard]] OrderId GetOrderId() const noexcept { return _orderId; }
  [[nodiscard]] Side GetSide() const noexcept { return _side; }
  [[nodiscard]] Price GetPrice() const noexcept { return _price; }
  [[nodiscard]] Quantity GetInitialQuantity() const noexcept { return _initialQuantity; }
  [[nodiscard]] Quantity GetRemainingQuantity() const noexcept { return _remainingQuantity; }
  [[nodiscard]] bool isFilled() const noexcept { return GetRemainingQuantity() == 0; }
private:
  OrderType _orderType{};
  OrderId _orderId{};
  Side _side{};
  Price _price{};
  Quantity _initialQuantity{};
  Quantity _remainingQuantity{};
};
using OrderPointer = std::shared_ptr<Order>;
}
