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
#pragma once

#include "linalg/common.h"

#include <memory>
#include <xtensor/xview.hpp>
#include <xtensor/xio.hpp>

namespace ss
{
    template <typename T>
    void l1(ndspan<T, 2> A)
    {
        xt::xtensor<T, 1> sums = xt::sum(xt::abs(A), {0});
        view(A) /= sums;
    }

    template <typename T>
    void l1(ndspan<T, 1> x)
    {
        T sum = xt::sum(xt::abs(x))();
        view(x) /= sum;
    }
}