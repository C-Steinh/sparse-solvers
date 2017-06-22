/*  Copyright 2017 International Business Machines Corporation

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.  */

#include <kernelpp/kernel_invoke.h>

#include "ss/ss.h"
#include "solvers/homotopy.h"
#include "linalg/common.h"
#include "blas_wrapper.h"

namespace ss
{
    /* Homotopy solver ----------------------------------------------------- */

    struct homotopy::state {};

    homotopy::homotopy() : m{ nullptr } {}
    homotopy::~homotopy() = default;

    kernelpp::maybe<ss::homotopy_report> homotopy::solve(
        const ndspan<float, 2> A,
        const ndspan<float>    y,
              float            tolerance,
              uint32_t         max_iterations,
              ndspan<float>    x)
    {
        return kernelpp::run<solve_homotopy>(A, y, tolerance, max_iterations, x);
    }

    /* Utils --------------------------------------------------------------- */

    void reconstruct_signal(
        const ndspan<float, 2> A, const ndspan<float> x, ndspan<float> y)
    {
        assert (dim<1>(A) == x.size()
            &&  dim<0>(A) == y.size());

        size_t m = dim<0>(A), n = dim<1>(A);

        blas::xgemv(CblasRowMajor, CblasNoTrans, m, n, 1.0,
            A.cbegin(), n,
            x.cbegin(), 1, 0.0,
            y.begin(), 1);
    }
}