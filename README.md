# TradeEnergyPro(Using Linked List Implementation
Energy Trading Record Management System for a Smart Grid:
The goal is to develop a software program that manages energy trading transactions in a smart grid
environment. Energy trading transactions occur when energy producers (sellers) sell energy to consumers
(buyers) at specified rates. These transactions need to be accurately recorded, tracked, and analyzed to optimize
energy trading operations, manage financial records, and enable efficient trading management within the grid.
The program will provide functionalities to handle energy trading transactions, each of which is represented by
the following attributes:
Transaction Attributes:
>Transaction ID: A unique identifier for each transaction.
> Buyer ID: The unique ID of the entity buying energy.
> Seller ID: The unique ID of the entity selling energy. (Reference to seller Node)
> Amount of Energy (kWh): The amount of energy traded in kilowatt-hours.
> Price per kWh: The price at which the energy is traded per kilowatt-hour.
> Timestamp: The date and time when the transaction occurred.

The sellers sell energy at two rates. If the Amount of energy is greater than 300kWh, a different rate is applied.
Seller Attributes:
> Seller ID
>Energy rate per kWh below 300
> Energy rate per kWh above 300
> List of regular buyers. (LL of buyer IDs) – buyers with more than 5 transactions should be added to this
list.
Functional Requirements
The program should include the following features:
1. Add New Transactions: Users should be able to input new energy trading transactions with all the
specified attributes (Transaction ID, Buyer ID, Seller ID, Amount of Energy, Price per kWh,
Timestamp). The transactions should be stored in the system. The price point applied to the transaction
should be automatically added based on the rate in seller attribute.
2. Display All Transactions: Users should be able to view all the transactions stored in the system. Each
transaction should be clearly displayed, including all its attributes.
3. Create a list of transactions for every seller.
4. Create a list of transactions for every buyer.
5. Given a time period, list all transactions that took place in that period.
6. Calculate Total Revenue by Seller: The program should allow users to query the total revenue generated
by a specific seller based on their Seller ID. Revenue should be calculated as the sum of the products of
energy amounts and prices per kWh for all transactions involving that seller.
7. Find and Display the Transaction with the Highest Energy Amount: The program should allow users to
search for and display the transaction with the highest amount of energy traded (kWh). This will help
identify the largest trading events. Sort the transactions based on amount of energy traded.
8. Sort the list of buyers based on the energy bought.
9. Sort all seller/buyer pairs in decreasing order of the number of transactions between them.
10. Update the details of an existing transaction. For example, users may change the amount of energy or
the price per kWh for a given transaction.
