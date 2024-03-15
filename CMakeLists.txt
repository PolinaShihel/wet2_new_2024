cmake_minimum_required(VERSION 3.25)
project(wet2_new_2024)

set(CMAKE_CXX_STANDARD 17)

add_executable(wet2_new_2024 AVL_tree.h Contestant.cpp hashTable.h main24a2.cpp olympics24a2.cpp
        RankNode.h RankTree.h StrCond.cpp Team.cpp
        ContestantStr.cpp
        ContestantStr.h
        ContestantEntry.cpp
        ContestantEntry.h
        wet2util.h
        BasicFuncTester.cpp
)
