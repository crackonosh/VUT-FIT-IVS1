//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

TEST(Matrix, Initialization)
{
  Matrix m1;
  ASSERT_TRUE(m1.get(0, 0) == 0);
  ASSERT_FALSE(m1.get(0, 0) == 1);

  Matrix m2(3, 3);
  ASSERT_TRUE(m2.get(0, 0) == 0);
  ASSERT_TRUE(m2.get(2, 2) == 0);
  ASSERT_FALSE(m2.get(1, 1) == 3);
}

TEST(Matrix, SetOneValue)
{
  Matrix m1;
  ASSERT_TRUE(m1.get(0, 0) == 0);
  ASSERT_TRUE(m1.set(0, 0, 5));

  Matrix m2(3, 3);
  ASSERT_TRUE(m2.set(2, 2, 10));
}

TEST(Matrix, SetMultipleValues)
{
  Matrix m1(3,3);

  std::vector<std::vector<double> > val1{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
  ASSERT_TRUE(m1.set(val1));
}

TEST(Matrix, GetValues)
{
  Matrix m1(3, 3);
  std::vector<std::vector<double> > val1{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
  ASSERT_TRUE(m1.set(val1));
  ASSERT_TRUE(m1.get(0, 1) == 1);
  ASSERT_TRUE(m1.get(1, 1) == 4);
  ASSERT_TRUE(m1.get(2, 1) == 7);
}

TEST(Matrix, EqualMatrices)
{
  Matrix m1(3, 4);
  Matrix m2(3, 4);
  Matrix m3(3, 4);
  m3.set(0, 0, 35);

  ASSERT_TRUE(m1.operator==(m2));
  ASSERT_FALSE(m1.operator==(m3));
}

TEST(Matrix, AddingMatrices)
{
  Matrix m1(2, 2);
  Matrix m2(2, 2);

  std::vector<std::vector<double> > val1{{2, 4}, {4, 2}};
  std::vector<std::vector<double> > val2{{1, 1}, {1, 1}};

  ASSERT_TRUE(m1.set(val1));
  ASSERT_TRUE(m2.set(val2));
  Matrix m3 = m1.operator+(m2);

  ASSERT_TRUE(m3.get(0, 0) == 3);
  ASSERT_TRUE(m3.get(1, 0) == 5);
}

TEST(Matrix, MultiplyMatrices)
{

  Matrix m1(2, 2);
  Matrix m2(2, 2);

  std::vector<std::vector<double> > val1{{2, 4}, {4, 2}};
  std::vector<std::vector<double> > val2{{2, 3}, {4, 5}};

  ASSERT_TRUE(m1.set(val1));
  ASSERT_TRUE(m2.set(val2));
  Matrix m3 = m1.operator*(m2);
  Matrix m4 = m2.operator*(m1);
  
  ASSERT_TRUE(m3.get(0, 0) == 20);
  ASSERT_TRUE(m3.get(0, 1) == 26);
  ASSERT_TRUE(m3.get(1, 0) == 16);
  ASSERT_TRUE(m3.get(1, 1) == 22);

  ASSERT_TRUE(m3.get(1, 1) != m4.get(1, 1));
}

TEST(Matrix, MultiplyMatrixByConstant)
{
  Matrix m1(2, 2);
  Matrix m2(3, 3);
  std::vector<std::vector<double> > val1{{2, 3}, {4, 5}};
  std::vector<std::vector<double> > val2{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  ASSERT_TRUE(m1.set(val1));
  ASSERT_TRUE(m2.set(val2));

  Matrix m3 = m1.operator*(2);
  Matrix m4 = m2.operator*(3);

  ASSERT_TRUE(m3.get(0, 0) == 4);
  ASSERT_TRUE(m3.get(0, 1) == 6);
  ASSERT_TRUE(m3.get(1, 0) == 8);
  ASSERT_TRUE(m3.get(1, 1) == 10);

  ASSERT_TRUE(m4.get(0, 0) == 3);
  ASSERT_TRUE(m4.get(1, 1) == 15);
  ASSERT_TRUE(m4.get(2, 2) == 27);
}

TEST(Matrix, EquationSolving)
{
  Matrix m1(3, 3);
  Matrix m2(2, 2);
  std::vector<std::vector<double> > val1{{2, 3, 7}, {3, 8, 1}, {0, 3, 3}};
  std::vector<double> right1{47, 50, 27};
  std::vector<std::vector<double> > val2{{4, 3}, {2, 1}};
  std::vector<double> right2{6, 4};

  ASSERT_TRUE(m1.set(val1));
  ASSERT_TRUE(m2.set(val2));

  std::vector<double> result1 = m1.solveEquation(right1);
  std::vector<double> result2 = m2.solveEquation(right2);

  ASSERT_TRUE(result1[0] == 2);
  ASSERT_TRUE(result1[1] == 5);
  ASSERT_TRUE(result1[2] == 4);

  ASSERT_TRUE(result2[0] == 3);
  ASSERT_TRUE(result2[1] == -2);
}

TEST(Matrix, Transpose)
{
  Matrix m1(2, 2);
  Matrix m2(3, 3);
  std::vector<std::vector<double> > val1{{1, 2}, {3, 4}};
  std::vector<std::vector<double> > val2{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  ASSERT_TRUE(m1.set(val1));
  ASSERT_TRUE(m2.set(val2));

  Matrix m3 = m1.transpose();
  Matrix m4 = m2.transpose();

  ASSERT_TRUE(m1.get(0, 1) == 2);
  ASSERT_TRUE(m3.get(0, 1) == 3);
  
  ASSERT_TRUE(m2.get(0, 1) == 2);
  ASSERT_TRUE(m2.get(2, 1) == 8);
  ASSERT_TRUE(m4.get(0, 1) == 4);
  ASSERT_TRUE(m4.get(2, 1) == 6);
}

TEST(Matrix, Inverse)
{
  Matrix m1(2, 2);
  Matrix m2(3, 3);
  std::vector<std::vector<double> > val1{{1, 2}, {3, 4}};
  std::vector<std::vector<double> > val2{{9, 9, 9}, {4, 5, 6}, {3, 3, 9}};
  
  ASSERT_TRUE(m1.set(val1));
  ASSERT_TRUE(m2.set(val2));

  Matrix m3 = m1.inverse();
  Matrix m4 = m2.inverse();

  ASSERT_TRUE(m3.get(0, 0) == -2);
  ASSERT_TRUE(m3.get(0, 1) == 1);
  ASSERT_TRUE(m3.get(1, 0) == 1.5);
  ASSERT_TRUE(m3.get(1, 1) == -0.5);

  ASSERT_TRUE(m4.get(0, 1) == -1);
  ASSERT_TRUE(m4.get(1, 1) == 1);
  ASSERT_TRUE(m4.get(2, 1) == 0);
}
/*** Konec souboru white_box_tests.cpp ***/
