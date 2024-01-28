#ifndef A6_915_MINDRILA_MIHAIL_1_TEST_EVERYTHING_H
#define A6_915_MINDRILA_MIHAIL_1_TEST_EVERYTHING_H

#endif //A6_915_MINDRILA_MIHAIL_1_TEST_EVERYTHING_H

#pragma once

void testIdGenerator();

void testTrenchCoat();

void testAdministratorTrenchCoatService();

void testUserTrenchCoatService();

void testTrenchCoatRepository();

void testTrenchCoatRepositoryException();

void testAdminTrenchCoatServiceException();


void Add_ValidInput_UniqueTrenchCoat_AdministratorServiceTest();

void Add_InvalidInput_AlreadyExistingTrenchCoat_AdminTrenchCoatServiceException_AdministratorServiceTest();

void Remove_ValidInput_ExistingTrenchCoat_AdministratorServiceTest();

void Remove_InvalidInput_NonExistingTrenchCoat_AdminTrenchCoatServiceException_AdministratorServiceTest();