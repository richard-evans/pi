//------------------------------------------------------------------------------
//
//               (c) R F L Evans 2025 All Rights Reserved.
//
//------------------------------------------------------------------------------
//
// C++ standard library headers
#include <cmath>
#include <cstdint>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
//#include <string>
//#include <sstream>
//#include <vector>

//----------------------------------------------------------
// simple wrapper class for rng
//----------------------------------------------------------
class rng{

   // std::random variables (internal to class)
   std::mt19937 mt; // mersenne twister
   std::uniform_real_distribution<double> dist;

public:

   // seed rng
   void seed(unsigned int random_seed){
      dist = std::uniform_real_distribution<double>(0.0,1.0); // uniform distribution [0:1)
      std::mt19937::result_type mt_seed = random_seed;
      mt.seed(mt_seed);
   }

   // generate a uniform random number between 0 and 1
   double grnd() {
      return dist(mt);
   }

};

//----------------------------------------------------------
// simple class for performing code timing
//----------------------------------------------------------
class vtimer_t{

private:
   std::chrono::high_resolution_clock::time_point start_time;
   std::chrono::high_resolution_clock::time_point end_time;

public:
   // start the timer
   void start(){
      start_time = std::chrono::high_resolution_clock::now();
   }

   // start the timer
   void stop(){
      end_time = std::chrono::high_resolution_clock::now();
   }

   // get the elapsed time in milliseconds
   double elapsed_time(){

      // work out elapsed time
      return 1.e-9*double(std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count());

   }
};

//------------------------------------------------------------------------------
//  Program to estimate the value of PI using Monte Carlo
//------------------------------------------------------------------------------
int main(int argument_count, char *argument_values[]){

   // Initialise array of random number generators (one per thread)
   rng random_generator;

   // seed random generator
   random_generator.seed(37852727);

   uint64_t in_count = 0; // total number of darts landing inside the circle

   // set number of darts
   const uint64_t num_darts = 1000000;

   // initialise timer
   vtimer_t timer;
   timer.start();

   // throw darts
   for( int d=0; d<num_darts; ++d){

      // generate random x and y positions
      const double x = random_generator.grnd();
      const double y = random_generator.grnd();

      // calculate radius squared
      const double radius_sq = x*x + y*y;

      // check if coordinates are inside circle of radius 1 and increment counter
      if(radius_sq <= 1.0) in_count++;

   }

   // stop the timer
   timer.stop();

   // print calculated value of pi and error to screen
   const double calculated_pi = 4.0*double(in_count)/double(num_darts);

   std::cout << std::setprecision(15) << "Estimated value of pi is " << calculated_pi << std::setprecision(6) << " with a fractional error of " << fabs(calculated_pi-M_PI)*100.0/M_PI << " %" << std::endl;
   std::cout << "Time for calculation: " << timer.elapsed_time() << std::endl;

}
