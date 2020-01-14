#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "InventoryItem.h"
#include "ItemDatabase.h"

/* Rocket League Inventory API
by Ridas Jagelavicius */

class Inventory{
  public:
    // Default ctor
    Inventory();

    // Custom ctor
    Inventory(std::string path_to_database);

    // Custom ctor
    Inventory(std::vector<InventoryItem> items, std::string path_to_database);

    // Returns the total estimated key value (lower bound) of inventory  
    int GetInventoryWorth();

    // Adds an item to the inventory
    // Increases quantity by 1 if item exists
    void AddItem(const InventoryItem & item);

    // Removes an item from the inventory if it exists
    // Decreases quantity by 1 if item exists
    void RemoveItem(const InventoryItem& itemToRemove);

    // Updates the price of an item if it exists
    void UpdateItemPrice(const InventoryItem& itemToUpdate, std::string newPrice);

    // Returns an easy-to-read list of items
    // In the following format:
    // [Color] [Certification] ItemName (Quantity) LowerPrice-UpperPrice k
    std::string PrettyPrint() const;

    // Returns a list of items with lower bound prices
    // In the following format:
    // H: LowerPrice k
    // W: [Color] [Certification] ItemName
    std::string PrintBuyingList() const;

    // Returns a list of items with upper bound prices listed
    // In the following format:
    // H: [Color] [Certification] ItemName
    // W: UpperPrice k or offer
    std::string PrintSellingList() const;

    // Return all items
    std::vector<InventoryItem> GetItems();

    // Creates a "saved" folder and stores an inventory for faster retrieval
    // Returns whether or not the process was successful
    bool WriteInvToFile();

    // Reads in and populates an inventory from saved/inventory.txt
    // Returns whether or not the process could be completed successfully
    bool ReadInvFromFile();

  private:
    ItemDatabase database_;
    std::vector<InventoryItem> items_; // List of current inventory items
    std::unordered_map<std::string,std::vector<InventoryItem>> typeMap_; // Maps a type (Topper, Antenna) to a vector of that type
    std::vector<InventoryItem>::iterator FindItem(const InventoryItem& item); // Returns an iterator to the passed item or the end if not found
};