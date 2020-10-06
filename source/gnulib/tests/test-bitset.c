/* Test of bitset.
   Copyright (C) 2018-2019 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <config.h>

#include "bitset.h"

#include "macros.h"

#define RANDOM(n) (rand () % (n))

static
void assert_bitset_equal (bitset bs1, bitset bs2)
{
  debug_bitset (bs1);
  debug_bitset (bs2);
  ASSERT (bitset_size (bs1) == bitset_size (bs2));
  for (bitset_bindex i = 0; i < bitset_size (bs1); ++i)
    ASSERT (bitset_test (bs1, i) == bitset_test (bs2, i));
}

void bitset_random (bitset bs)
{
  for (bitset_bindex i = 0; i < bitset_size (bs); ++i)
    bitset_set (bs, RANDOM (2));
}

void compare (enum bitset_attr a, enum bitset_attr b)
{
  const int nbits = RANDOM (256);

  bitset asrc0 = bitset_create (nbits, a);
  bitset_random (asrc0);
  bitset asrc1 = bitset_create (nbits, a);
  bitset_random (asrc1);
  bitset asrc2 = bitset_create (nbits, a);
  bitset_random (asrc2);
  bitset asrc3 = bitset_create (nbits, a);
  bitset_random (asrc3);
  bitset adst = bitset_create (nbits, a);

  bitset bsrc0 = bitset_create (nbits, b);
  bitset_copy (bsrc0, asrc0);
  bitset bsrc1 = bitset_create (nbits, b);
  bitset_copy (bsrc1, asrc1);
  bitset bsrc2 = bitset_create (nbits, b);
  bitset_copy (bsrc2, asrc2);
  bitset bsrc3 = bitset_create (nbits, b);
  bitset_copy (bsrc3, asrc3);
  bitset bdst = bitset_create (nbits, b);

  bitset_not (adst, asrc0);
  bitset_not (bdst, bsrc0);
  assert_bitset_equal (adst, bdst);

  bitset_and (adst, asrc0, asrc1);
  bitset_and (bdst, bsrc0, bsrc1);
  assert_bitset_equal (adst, bdst);
  ASSERT (bitset_and_cmp (adst, asrc0, asrc1)
          == bitset_and_cmp (bdst, bsrc0, bsrc1));
  assert_bitset_equal (adst, bdst);

  bitset_andn (adst, asrc0, asrc1);
  bitset_andn (bdst, bsrc0, bsrc1);
  assert_bitset_equal (adst, bdst);
  ASSERT (bitset_andn_cmp (adst, asrc0, asrc1)
          == bitset_andn_cmp (bdst, bsrc0, bsrc1));
  assert_bitset_equal (adst, bdst);

  bitset_or (adst, asrc0, asrc1);
  bitset_or (bdst, bsrc0, bsrc1);
  assert_bitset_equal (adst, bdst);
  ASSERT (bitset_or_cmp (adst, asrc0, asrc1)
          == bitset_or_cmp (bdst, bsrc0, bsrc1));
  assert_bitset_equal (adst, bdst);

  bitset_xor (adst, asrc0, asrc1);
  bitset_xor (bdst, bsrc0, bsrc1);
  assert_bitset_equal (adst, bdst);
  ASSERT (bitset_xor_cmp (adst, asrc0, asrc1)
          == bitset_xor_cmp (bdst, bsrc0, bsrc1));
  assert_bitset_equal (adst, bdst);

  bitset_and_or (adst, asrc0, asrc1, asrc2);
  bitset_and_or (bdst, bsrc0, bsrc1, bsrc2);
  assert_bitset_equal (adst, bdst);
  ASSERT (bitset_and_or_cmp (adst, asrc0, asrc1, asrc2)
          == bitset_and_or_cmp (bdst, bsrc0, bsrc1, bsrc2));
  assert_bitset_equal (adst, bdst);

  bitset_andn_or (adst, asrc0, asrc1, asrc2);
  bitset_andn_or (bdst, bsrc0, bsrc1, bsrc2);
  assert_bitset_equal (adst, bdst);
  ASSERT (bitset_andn_or_cmp (adst, asrc0, asrc1, asrc2)
          == bitset_andn_or_cmp (bdst, bsrc0, bsrc1, bsrc2));
  assert_bitset_equal (adst, bdst);

  bitset_or_and (adst, asrc0, asrc1, asrc2);
  bitset_or_and (bdst, bsrc0, bsrc1, bsrc2);
  assert_bitset_equal (adst, bdst);
  ASSERT (bitset_or_and_cmp (adst, asrc0, asrc1, asrc2)
          == bitset_or_and_cmp (bdst, bsrc0, bsrc1, bsrc2));
  assert_bitset_equal (adst, bdst);
}

void check_attributes (enum bitset_attr attr)
{
  enum { nbits = 32 };

  bitset bs0 = bitset_create (nbits, attr);
  ASSERT (bitset_size (bs0) == 32);
  ASSERT (bitset_count (bs0) == 0);
  ASSERT (bitset_empty_p (bs0));

  bitset bs1 = bitset_create (nbits, attr);
  bitset_set (bs1, 1);
  bitset_set (bs1, 3);
  bitset_set (bs1, 5);
  ASSERT (bitset_count (bs1) == 3);
  ASSERT (!bitset_empty_p (bs1));

  bitset bs2 = bitset_create (nbits, attr);
  bitset_set (bs2, 0);
  bitset_set (bs2, 2);
  bitset_set (bs2, 4);

  /* disjoint_p */
  ASSERT (bitset_disjoint_p (bs1, bs2));

  /* and */
  bitset bs = bitset_create (nbits, attr);
  bitset_and (bs, bs1, bs2);
  ASSERT (bitset_count (bs) == 0);

  /* or */
  bitset_or (bs, bs1, bs2);
  ASSERT (bitset_count (bs) == 6);
}

int main (void)
{
  check_attributes (BITSET_FIXED);
  check_attributes (BITSET_VARIABLE);
  check_attributes (BITSET_DENSE);
  check_attributes (BITSET_SPARSE);
  check_attributes (BITSET_FRUGAL);
  check_attributes (BITSET_GREEDY);

  compare (BITSET_FIXED, BITSET_FIXED);
  compare (BITSET_FIXED, BITSET_VARIABLE);
  compare (BITSET_FIXED, BITSET_DENSE);
  compare (BITSET_FIXED, BITSET_SPARSE);
  compare (BITSET_FIXED, BITSET_FRUGAL);
  compare (BITSET_FIXED, BITSET_GREEDY);
  return 0;
}
