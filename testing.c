//
// Created by tommy on 3/24/2019.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"

int main(void)
{
    Movie* tree = NULL;
    tree = Insert(tree, "abcd", "title1", "genre1", "year1", "time1");
    tree = Insert(tree, "abc", "title2", "genre2", "year2", "time2");
    tree = Insert(tree, "abcde", "title3", "genre3", "year3", "time3");
    tree = Insert(tree, "a", "title4", "genre4", "year4", "time4");
    tree = Insert(tree, "abcd", "title5", "genre5", "year5", "time5");
    tree = Insert(tree, "abcvycd", "title6", "genre6", "year6", "time6");
    tree = Insert(tree, "kdjbchcabcd", "title7", "genre7", "year7", "time7");
    tree = Insert(tree, "kabcd", "title8", "genre8", "year8", "time8");
    tree = Insert(tree, "azbcd", "title9", "genre9", "year9", "time9");
    tree = Insert(tree, "azzcd", "title10", "genre10", "year10", "time10");
    tree = Insert(tree, "zabcd", "title11", "genre11", "year11", "time11");
    tree = Insert(tree, "bcd", "title12", "genre12", "year12", "time12");
    tree = Insert(tree, "bcda", "title13", "genre13", "year13", "time13");
    tree = Insert(tree, "bcdj", "title14", "genre14", "year14", "time14");
    tree = Insert(tree, "lmo", "title15", "genre15", "year15", "time15");
    tree = Insert(tree, "md", "title16", "genre16", "year16", "time16");
    tree = Insert(tree, "z", "title17", "genre17", "year17", "time17");
    tree = Insert(tree, "ma", "title18", "genre18", "year18", "time18");

    PrintInOrder(tree);

    return 0;
}
