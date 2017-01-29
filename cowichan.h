#ifndef _BENCHMARK_COWICHAN_
#define _BENCHMARK_COWICHAN_

#include <vector>

/** @namespace cowichan
 * The chained implementation of these toys executes in the order shown below. Because of choices in steps 1 and 3,
 * there are four possible chained sequences.
 * 01. An integer matrix I with r rows and c columns is created either by using the Mandelbrot Set algorithm (mandel) or
 *     by filling locations with random values (randmat).
 * 02. The integer matrix I is shuffled in both dimensions (shuffle).
 * 03. Either invasion percolation (invperc) or histogram thresholding (thresh) is used to generate a Boolean mask B
 *     from I in which the (minimum) percentage of True locations is P. Like I, B has r rows and c columns.
 * 04. The Game of Life (life) is simulated for G generations, using B as an initial configuration. This step overwrites
 *     the Boolean matrix B.
 * 05. A vector of L (m,x,y) points is created using the integer matrix I and the Boolean matrix B.
 * 06. A series of convex hulls (hull) are obtained from the points produced above.
 * 07. The coordinates of the points from the previous step are normalized (norm).
 * 08. An L×L matrix A and an L-vector V are created using the normalized point locations from the previous step (outer).
 * 09. The matrix equation AX=V is solved using Gaussian elimination (gauss) and successive over-relaxation (sor) to
 *     generate two solution vectors Xgauss and Xsor. These two toys should execute concurrently if possible.
 * 10. The checking vectors Vgauss=AXgauss and Vsor=AXsor are calculated (product). These two toys should execute
 *     concurrently if possible.
 * 11. The norm-1 distance between Vgauss and Vsor is calculated (vecdiff). This measures the agreement between the
 *     solutions found by the two methods.
 */
namespace cowichan {

    /**
     * @brief This module solves a matrix equation AX=V for a dense, symmetric, diagonally dominant matrix A and an
     *        arbitrary vector non-zero V using explicit reduction. Input matrices are required to be symmetric and
     *        diagonally dominant in order to guarantee that there is a well-formed solution to the equation.
     * @param matrix The real matrix A.
     * @param target The real vector V.
     * @return A real vector containing the solution X.
     */
    std::vector<float> gauss(float **matrix, float *target);

    /**
     * @brief Given a set of (x,y) points, this toy finds those that lie on the convex hull, removes them, then finds
     *        the convex hull of the remainder. This process continues until no points are left. The output is a list
     *        of points in the order in which they were removed, i.e., the first section of the list is the points from
     *        the outermost convex hull, the second section is the points that lay on the next hull, and so on.
     * @param original The vector of input points.
     * @return The vector of output points (a permutation of the input).
     */
    std::vector<float> hull(float *original);

    /**
     * @brief Invasion percolation models the displacement of one fluid (such as oil) by another (such as water) in
     *        fractured rock. In two dimensions, this can be simulated by generating an N×N grid of random numbers in
     *        the range [1..R], and then marking the center cell of the grid as filled. In each iteration, one examines
     *        the four orthogonal neighbors of all filled cells, chooses the one with the lowest value (i.e., the one
     *        with the least resistance to filling), and fills it in.
     *
     *        Filling begins at the central cell of the matrix (rounding down for even-sized axes). The simulation
     *        continues until some fixed percentage of cells have been filled, or until some other condition (such as
     *        the presence of trapped regions) is achieved. The fractal structure of the filled and unfilled regions is
     *        then examined to determine how much oil could be recovered.
     *
     *        The naive way to implement this is to repeatedly scan the array. A much faster technique is to maintain a
     *        priority queue of unfilled cells which are neighbors of filled cells. This latter technique is similar to
     *        the list-based methods used in some cellular automaton programs, and is very difficult to parallelize
     *        effectively.
     * @param matrix An integer matrix.
     * @param nfill The number of points to fill.
     * @return A Boolean matrix filled with True (showing a filled cell) or False (showing an unfilled cell).
    */
    std::vector<std::vector<bool>> invperc(int *matrix, int nfill);

    /**
     * @brief This module simulates the evolution of Conway's Game of Life, a two-dimensional cellular automaton. At
     *        each time step, this module must count the number of live (True) cells in the 8-neighborhood of each cell
     *        using circular boundary conditions. If a cell has 3 live neighbors, or has 2 live neighbors and is already
     *        alive, it is alive in the next generation. In any other situation, the cell becomes, or stays, dead.
     * @param matrix A Boolean matrix representing the Life world.
     * @param numgen The number of generations to simulate.
     * @return A Boolean matrix representing the world after simulation.
     */
    std::vector<std::vector<bool>> life(bool **matrix, int numgen);

    /**
     * @brief This module generates the Mandelbrot Set for a specified region of the complex plane. Given initial
     *        coordinates (\f$x_0, y_0\f$), the Mandelbrot Set is generated by iterating the equation:
     *        \f[x' = x^{2} — y^{2} + y_{0}\f]
     *        \f[y' = 2xy + x_{0}\f]
     *	      until either an iteration limit is reached, or the values diverge. The iteration limit used in this
     *	      module is 150 steps; divergence occurs when \f$x^2 + y^2\f$ becomes 2.0 or greater. The integer value of
     *	      each element of the matrix is the number of iterations done. The values produced should depend only on
     *	      the size of the matrix and the seed, not on the number of processors or threads used.
     * @param nrows The number of rows in the output matrix.
     * @param ncols The number of columns in the output matrix.
     * @param x0 The real coordinates of the lower-left corner of the region to be generated.
     * @param y0 The real coordinates of the lower-left corner of the region to be generated.
     * @param dx The extent of the region to be generated.
     * @param dy The extent of the region to be generated.
     * @return An integer matrix containing the iteration count at each point in the region.
     */
    std::vector<std::vector<int>> mandel(int nrows, int ncols, float x0, float y0, float dx, float dy);

    /**
     * @brief This module fills a matrix with pseudo-random integers. The values produced must depend only on the size
     *        of the matrix and the seed, not on the number of processors or threads used.
     * @param nrwos The number of rows in the output matrix.
     * @param ncols the number of columns in the output matrix.
     * @param s The random number generation seed.
     * @return An integer matrix filled with random values.
     */
    std::vector<std::vector<int>> randmat(int nrows, int ncols, int s);

    /**
     * @brief This module divides the values in a rectangular two-dimensional integer matrix into two halves along one
     *        axis, shuffles them, and then repeats this operation along the other axis. Values in odd-numbered
     *        locations are collected at the low end of each row or column, while values in even-numbered locations are
     *        moved to the high end.
     * @param matrix An integer matrix.
     * @return An integer matrix containing shuffled values.
     */
    std::vector<std::vector<int>> shuffle(std::vector<std::vector<int>> matrix);

    /**
     * @brief This module performs histogram thresholding on an image. Given an integer image I and a target percentage
     *        p, it constructs a binary image B such that Bi,j is set if no more than p percent of the pixels in I are
     *        brighter than Ii,j. The general idea is that an image's histogram should have two peaks, one centered
     *        around the average foreground intensity, and one centered around the average background intensity. This
     *        program attempts to set a threshold between the two peaks in the histogram and select the pixels above the
     *        threshold.
     * @param matrix The integer matrix to be thresholded.
     * @param percent The minimum percentage of cells to retain.
     * @return A Boolean matrix whose values are True where the value of a cell in the input image is above the
     *         threshold, and False otherwise.
     */
    std::vector<std::vector<bool>> thresh(std::vector<std::vector<int>> matrix, int percent);
}

#endif // _BENCHMARK_COWICHAN_