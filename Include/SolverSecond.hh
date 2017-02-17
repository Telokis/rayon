#ifndef RAYON_SOLVER_SECOND_HH_
#define RAYON_SOLVER_SECOND_HH_

#include "Tools/Helpers.hh"

/**
 * @brief This namespace is used to store
 * equation solvers.
 */
namespace Rayon
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
    bool        Second(Float_t* results,
                       Float_t a, Float_t b, Float_t c);

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
    bool        Second(Float_t* results,
                       Float_t* args);
} // namespace Solver
} // namespace Tools
} // namespace Rayon

#endif // RAYON_SOLVER_SECOND_HH_
