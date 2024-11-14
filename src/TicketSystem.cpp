#include "TicketSystem.hpp"

// 計算單筆訂單的票價
int CheckTicketPrice(const Order& ticket) {
    if (ticket.quantity <= 0) {
        throw std::invalid_argument("Quantity must be greater than 0.");
    }

    int pricePerTicket = 0;

    // 根據票類型設定價格
    switch (ticket.type) {
        case TicketType::Adult:
            pricePerTicket = 350;
            break;
        case TicketType::Child:
            pricePerTicket = 280;
            break;
        case TicketType::Elder:
            pricePerTicket = 240;
            break;
        default:
            throw std::invalid_argument("Invalid ticket type.");
    }

    // 計算總價格
    int totalPrice = ticket.quantity * pricePerTicket;

    // 若購買數量 >= 10，打八折
    if (ticket.quantity >= 10) {
        totalPrice = static_cast<int>(totalPrice * 0.8);
    }

    return totalPrice;
}

// 計算今日所有訂單的總銷售金額
int CheckTodaySales(std::vector<Order> tickets) {
    int totalSales = 0;

    for (const auto& ticket : tickets) {
        totalSales += CheckTicketPrice(ticket); // 調用 CheckTicketPrice
    }

    return totalSales;
}

// 計算今日所有訂單的總票數
int CheckTodayTicketSales(std::vector<Order> tickets) {
    int totalTickets = 0;

    for (const auto& ticket : tickets) {
        if (ticket.quantity <= 0) {
            throw std::invalid_argument("Invalid quantity in an order.");
        }
        totalTickets += ticket.quantity;
    }

    return totalTickets;
}

// 計算特定類別的票的總銷售金額
int CheckSpecificTicketSales(TicketType type, std::vector<Order> tickets) {
    int totalSales = 0;

    for (const auto& ticket : tickets) {
        if (ticket.type == type) {
            totalSales += CheckTicketPrice(ticket); // 只計算指定類別的票
        }
    }

    return totalSales;
}

// 計算特定索引訂單的票價
int CheckSpecificOrdersTicketPrice(int idx, std::vector<Order> tickets) {
    // 確保索引合法
    if (idx < 0 || static_cast<size_t>(idx) >= tickets.size()) {
        throw std::invalid_argument("Index out of range.");
    }

    return CheckTicketPrice(tickets[idx]); // 返回指定索引訂單的票價
}
