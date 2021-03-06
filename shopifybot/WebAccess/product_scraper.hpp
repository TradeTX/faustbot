//
// Created by Evan Kirkiles on 7/14/18.
//

#ifndef SHOPIFY_BOT_PRODUCT_SCRAPER_HPP
#define SHOPIFY_BOT_PRODUCT_SCRAPER_HPP

// cURL include
#include <curl/curl.h>

// Other includes
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iterator>

#include "constants.hpp"

// Struct that contains a model's colors and size ID's
struct Product {

    std::string title;
    std::string color;

    // Usage: sizes[size] returns the ID for the model of that product
    std::unordered_map<std::string, std::string> sizes;

    // Function to return the id for a given size of the product
    std::string getID(std::string size) {
        // Remove whitespace from the size string
        size.erase(std::remove_if(size.begin(), size.end(), isspace), size.end());
        for (auto i = sizes.begin(); i != sizes.end(); ++i) {
            std::string format = i.operator*().first;
            format.erase(std::remove_if(format.begin(), format.end(), isspace), format.end());
            unsigned long position = format.find(size);
            if (position != std::string::npos &&
                format.substr(position + size.length(), 2) != ".5" &&
                format.substr(position + size.length(), 2) != "-5") {
                // In the case of S,M,L sizes, must check for a preceding 'X'
                if (position != 0 && format.substr(position - 1, 1) == "X") { continue; }
                return i.operator*().second;
            }
            std::replace(format.begin(), format.end(), '-', '.');
            position = format.find(size);
            if (position != std::string::npos &&
                format.substr(position + size.length(), 2) != ".5" &&
                format.substr(position + size.length(), 2) != "-5") {
                    return i.operator*().second;
            }
        }
        // Shouldn't get here if the size exists
        if (color.empty()) {
            throw std::runtime_error("Color or size not found.");
        }
        throw std::runtime_error("Size unavailable.");
    }
};

// Class to interface with the website given
class ShopifyWebsiteHandler {
public:

    // Instance source variable
    const URLAndMethod sourceURL;
    // ID for this instance of the ShopifyWebHandler, used in naming the files
    const std::string taskID;

    // Constructor that initializes the handler with the given URL
    explicit ShopifyWebsiteHandler(const URLAndMethod& url, const std::string& taskID);

    // Function that at the moment prints out the different models it scrapes from the website at given collection
    void getAllModels(const std::string& collection, bool availabilityFiltering = true,
            const std::string& bonusparams="?limit=25");

    // Function that scrapes all the variants for a product on a given product page. This revolves around the existence
    // of the Shopify 'handle":"' string which contains all variant information for submitting to cart.
    void getAllModelsProductPage(const std::string& extension, bool availabilityFiltering = true);

    // Function that returns the product id from the product's page (the one that has a BUY NOW button)
    // To specify color, they are indexed from the top: highest is 0, then 1, then 2, etc.
    std::string getVariantIDFrom(const std::string& addToURL, const std::string& size, std::string color = "");

    // Function that returns the first product it finds that contains any of the given keywords (title and color).
    // NOTE: Keywords are not case sensitive.
    Product lookForKeywords(const std::string& collection, const std::vector<std::string>& keywords,
                            const std::vector<std::string>& colorKeywords = {""}, const std::string& numresults="25");

    // Function that returns a specific number based on the status of the product.
    // 0: Product available.
    // 1: Product not in stock.
    // 2: Some other error with pulling webpage.
    int productAvailable(const std::string& variantID);

    // Function that scrapes the cart page of Shopify for a product's variant name and size
    // Return format: title, size, imageURL
    std::tuple<std::string, std::string, std::string> getNameSizeImage(const std::string& variantID);

private:
    // Perform a cURL download to get the body of a page
    void performCURL(const std::string& URL);
};


#endif //SHOPIFY_BOT_PRODUCT_SCRAPER_HPP
