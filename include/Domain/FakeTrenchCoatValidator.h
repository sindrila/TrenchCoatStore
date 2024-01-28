//
// Created by Alex on 18.05.2023.
//
#pragma once

#ifndef A89_915_MINDRILA_MIHAIL_FAKETRENCHCOATVALIDATOR_H
#define A89_915_MINDRILA_MIHAIL_FAKETRENCHCOATVALIDATOR_H

#include "TrenchCoatValidator.h"

class FakeTrenchCoatValidator : public TrenchCoatValidator
{
public:
    FakeTrenchCoatValidator() = default;
    bool throwsTrenchCoatException;
    void validateTrenchCoatData(const TrenchCoat &trench_coat_to_validate) override;
};


#endif //A89_915_MINDRILA_MIHAIL_FAKETRENCHCOATVALIDATOR_H
