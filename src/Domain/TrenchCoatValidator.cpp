//
// Created by Alex on 02.05.2023.
//

#include "../../include/Domain/TrenchCoatValidator.h"

#include <utility>

TrenchCoatException::TrenchCoatException(std::vector<std::string> new_message_errors) : message_errors{
        std::move(new_message_errors)}
{}

std::vector<std::string> TrenchCoatException::getErrors() const
{
    return this->message_errors;
}

void TrenchCoatValidator::validateTrenchCoatData(const TrenchCoat &trench_coat_to_validate)
{
    std::vector<std::string> errors;

    // Size validation
    std::string clothing_size = trench_coat_to_validate.getSize();
    if (clothing_size.empty())
        errors.push_back("Clothing size field empty. Please provide a size that is non-empty.\n");

    std::transform(clothing_size.begin(), clothing_size.end(), clothing_size.begin(), [](unsigned char character)
    { return std::tolower(character); });
    std::vector<std::string> valid_sizes = {"xs", "s", "m", "l", "xl", "xxl", "3xl"};
    bool is_valid_size = std::any_of(valid_sizes.begin(), valid_sizes.end(), [&](const std::string &available_size)
    { return available_size == clothing_size; });
    if (!is_valid_size)
        errors.push_back("Size does not exist. Please provide a size between XS and 3XL.\n");


    if (trench_coat_to_validate.getColour().empty())
        errors.push_back("Colour field empty. Please provide a colour that is non-empty.\n");

    if (trench_coat_to_validate.getPrice() < 0)
        errors.push_back("Price must be positive. Please provide a price that is positive.\n");

    if (trench_coat_to_validate.getQuantity() < 0)
        errors.push_back("Quantity must be positive. Please provide a quantity that is positive.\n");

    auto position_of_www = trench_coat_to_validate.getPhotoLink().find("www");
    auto position_of_http = trench_coat_to_validate.getPhotoLink().find("http");
    if (position_of_www != 0 && position_of_http != 0)
        errors.push_back("The website link must start with either \"www\" or \"http\". Please provide a valid link.\n");

    if (errors.size() > 0)
        throw TrenchCoatException(errors);
}

std::ostream& operator<<(std::ostream &os, const TrenchCoatException &exception_to_print)
{
    const std::vector<std::string> message_errors_to_print = exception_to_print.getErrors();
    for (const auto message : message_errors_to_print)
        os << message;
    return os;
}
