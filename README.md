# TradeEnergyPro (Using Linked List Implementation)

## Overview
TradeEnergyPro is an Energy Trading Record Management System designed for smart grid environments. It enables accurate recording, tracking, and analysis of energy trading transactions between sellers and buyers to optimize operations and manage financial records.

## Transaction Attributes
- **Transaction ID**: Unique identifier for each transaction.
- **Buyer ID**: Unique ID of the energy buyer.
- **Seller ID**: Unique ID of the energy seller (reference to seller node).
- **Amount of Energy (kWh)**: Energy traded in kilowatt-hours.
- **Price per kWh**: Price at which energy is traded.
- **Timestamp**: Date and time of the transaction.

## Seller Attributes
- **Seller ID**
- **Energy rate per kWh (below 300 kWh)**
- **Energy rate per kWh (above 300 kWh)**
- **Regular buyers**: Buyers with more than five transactions (stored as a linked list of Buyer IDs).

## Functional Requirements
- **Add New Transactions**: Automatically applies the correct seller rate.
- **Display All Transactions**: Lists all stored transactions.
- **Transaction Lists**:
  - For each seller
  - For each buyer
- **Filter Transactions by Time Period**.
- **Calculate Seller Revenue**: Total revenue for a specific seller.
- **Find Largest Transaction**: Display transaction with the highest energy traded.
- **Sorting Features**:
  - Transactions by energy amount.
  - Buyers by energy purchased.
  - Seller/Buyer pairs by transaction count.
- **Update Transaction Details**: Modify amount or price per kWh.

This project efficiently manages energy trading data using linked lists for optimized storage and retrieval.

