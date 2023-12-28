#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "puzzle_solver.hpp"

TEST_CASE( "Test-0", "[PuzzleSolver]" ) {

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("012345678"));
  REQUIRE(puzzle2.fromString("012345678"));
    
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 0);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 0);
  }
}

TEST_CASE( "Test-1", "[PuzzleSolver]" ) {

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("012345678"));
  REQUIRE(puzzle2.fromString("012345687"));
    
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 1);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 1);
  }
}

TEST_CASE( "Test-2", "[PuzzleSolver]" ) {

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("012345678"));
  REQUIRE(puzzle2.fromString("012345867"));
    
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 2);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 2);
  }
}

TEST_CASE( "Test-20", "[PuzzleSolver]" ) {

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("012345678"));
  REQUIRE(puzzle2.fromString("630781254"));
    
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 20);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 20);
  }
}

TEST_CASE( "Test-22", "[PuzzleSolver]" ) {

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("085741362"));
  REQUIRE(puzzle2.fromString("401836275"));
    
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 22);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 22);
  }
}

TEST_CASE( "Test-23", "[PuzzleSolver]" ) {

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("012345678"));
  REQUIRE(puzzle2.fromString("427568031"));
    
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 23);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 23);
  }
}

TEST_CASE( "Test-26", "[PuzzleSolver]" ) {

  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("012345678"));
  REQUIRE(puzzle2.fromString("524760318"));
    
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 26);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    bool found;
    std::size_t solution_cost;
    std::tie(found, solution_cost) = solver.search();
    
    REQUIRE(found);
    REQUIRE(solution_cost == 26);
  }
}

