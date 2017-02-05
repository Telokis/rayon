#include "SolverSecond.hh"

namespace RayOn
{
  namespace Tools
  {
    namespace Solver
    {
      /**
       * @brief   Equation solver for second degree polynomial.
       * @param[out]  results   Will contain the two solutions.
       * @param[in]   a         Equation's first coefficient.
       * @param[in]   b         Equation's second coefficient.
       * @param[in]   c         Equation's third coefficient.
       * @return  True if the equation has one or two solutions.
       *          false otherwise.
       */
      bool    Second(Float_t* results,
                     Float_t a, Float_t b, Float_t c)
      {
        using std::sqrt;

        Float_t  delta = Pow2(b) - 4.0 * a * c;
        Float_t  sqrtDelta;

        if (delta < 0)
          return false;
        if (!results)
          return true;

        sqrtDelta = sqrt(delta);
        results[1] = 2.0 * a;
        results[0] = (-b - sqrtDelta) / results[1];
        results[1] = (-b + sqrtDelta) / results[1];
        return true;
      }

      /**
       * @brief   Equation solver for second degree polynomial.
       * @param[out]  results Will contain the two solutions.
       * @param[in]   args    Equation's coefficients.
       *                      args[0] --> a
       *                      args[1] --> b
       *                      args[2] --> c
       * @return  True if the equation has one or two solutions.
       *          false otherwise.
       */
      bool    Second(Float_t* results,
                     Float_t* args)
      {
        return Second(results, args[0], args[1], args[2]);
      }

    } // namespace Solver
  } // namespace Tools
} // namespace RayOn