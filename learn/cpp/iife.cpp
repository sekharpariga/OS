#include <chrono>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

std::string to_string(const int i)
{
  std::stringstream ss;
  ss << i;
  return ss.str();
}

std::vector<std::vector<std::string>> classic(const int num_vecs, const int vec_size)
{
  std::vector<std::vector<std::string>> retval;

  for (int i = 0; i < num_vecs; ++i)
  {
    std::vector<std::string> nextvec(vec_size);
    for (int j = 0; j < vec_size; ++j)
    {
      nextvec[j] = "Some string that's a little bit longer than a short string ";
      // plus whatever else needs to happen
    }
    retval.push_back(nextvec);
    // do some other house keeping here
  }

  return retval;
}

std::vector<std::vector<std::string>> moved(const int num_vecs, const int vec_size)
{
  std::vector<std::vector<std::string>> retval;

  for (int i = 0; i < num_vecs; ++i)
  {
    std::vector<std::string> nextvec(vec_size);
    for (int j = 0; j < vec_size; ++j)
    {
      nextvec[j] = "Some string that's a little bit longer than a short string ";
      // plus whatever else needs to happen
    }
    retval.push_back(std::move(nextvec)); // this version requires extra bookkeeping to get the performance
    // do some other house keeping here
    // but we might be tempted to use nextvec, which is now is some unknown state
  }

  return retval;
}

std::vector<std::string> build_vector(const int vec_size)
{
  std::vector<std::string> nextvec(vec_size);
  for (int j = 0; j < vec_size; ++j)
  {
    nextvec[j] = "Some string that's a little bit longer than a short string ";
    // plus whatever else needs to happen
  }
  return nextvec;
}

std::vector<std::vector<std::string>> function_call(const int num_vecs, const int vec_size)
{
  std::vector<std::vector<std::string>> retval;

  for (int i = 0; i < num_vecs; ++i)
  {
    retval.push_back(build_vector(vec_size));
  }

  return retval;
}
std::vector<std::vector<std::string>> iife(const int num_vecs, const int vec_size)
{
  std::vector<std::vector<std::string>> retval;

  for (int i = 0; i < num_vecs; ++i)
  {
    retval.push_back([vec_size](){
          std::vector<std::string> nextvec(vec_size);
          for (int j = 0; j < vec_size; ++j)
          {
            nextvec[j] = "Some string that's a little bit longer than a short string ";
            // plus whatever else needs to happen
          }
          return nextvec;
        }());
    // no extra bookkeeping
    // no temptation to use the moved value
    // no pollution of the local namespace with a 'bad' variable
  }

  return retval;
}

std::vector<std::vector<std::string>> smarter(const int num_vecs, const int vec_size)
{
  return std::vector<std::vector<std::string>>(num_vecs, std::vector<std::string>(vec_size, "Some string that's a little bit longer than a short string "));
}



int main()
{
  const int num_vecs = 7;
  const int vec_size = 10000000;

  auto start_time = std::chrono::steady_clock::now();
  classic(num_vecs, vec_size);
  auto classic_time = std::chrono::steady_clock::now();
  moved(num_vecs, vec_size);
  auto moved_time = std::chrono::steady_clock::now();
  function_call(num_vecs, vec_size);
  auto function_time = std::chrono::steady_clock::now();
  iife(num_vecs, vec_size);
  auto iife_time = std::chrono::steady_clock::now();
  smarter(num_vecs, vec_size);
  auto smarter_time = std::chrono::steady_clock::now();

  std::cout << "Classic:  " << std::chrono::duration_cast<std::chrono::microseconds>(classic_time - start_time).count() << "us\n";
  std::cout << "Moved:    " << std::chrono::duration_cast<std::chrono::microseconds>(moved_time - classic_time).count() << "us\n";
  std::cout << "Function: " << std::chrono::duration_cast<std::chrono::microseconds>(function_time - moved_time).count() << "us\n";
  std::cout << "IIFE:     " << std::chrono::duration_cast<std::chrono::microseconds>(iife_time - function_time).count() << "us\n";
  std::cout << "Smarter:  " << std::chrono::duration_cast<std::chrono::microseconds>(smarter_time - iife_time).count() << "us\n";

}