/** plf_list_size_test.cpp
 * Short description here.
 *
 * Copyright © 2020 Gene Harvey
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <plf_list.h>
#include <list>

#define PRINT_SIZE(...) \
char (*__fail)(void)[sizeof (__VA_ARGS__)] = 1;

PRINT_SIZE(plf::list<int>::group_vector)
PRINT_SIZE(plf::list<int>::group_vector::last_endpoint_group)
PRINT_SIZE(plf::list<int>::group_vector::block_pointer)
PRINT_SIZE(plf::list<int>::group_vector::last_searched_group)
PRINT_SIZE(plf::list<int>::group_vector::size)
PRINT_SIZE(plf::list<int>::group_vector::element_allocator_pair)
PRINT_SIZE(plf::list<int>::group_vector::group_allocator_pair)

PRINT_SIZE(plf::list<int>::end_node)
PRINT_SIZE(plf::list<int>::last_endpoint)
PRINT_SIZE(plf::list<int>::node_pointer_allocator_pair)
PRINT_SIZE(plf::list<int>::node_allocator_pair)
PRINT_SIZE(plf::list<int>)

PRINT_SIZE(std::__list_imp<int, std::allocator<int>>)


int main (void)
{
  plf::list<int> x;
  plf::list<int>::iterator it = x.begin ();
  plf::list<int>::reverse_iterator rit (it);
  plf::list<int>::const_reverse_iterator crit (it);

  plf::list<int>::const_iterator cit = x.cbegin ();
  plf::list<int>::reverse_iterator rit1 (cit);
  plf::list<int>::const_reverse_iterator crit1 (cit);

  return 0;
}
