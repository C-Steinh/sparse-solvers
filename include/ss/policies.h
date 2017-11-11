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

#include "ss/ndspan.h"
#include <kernelpp/types.h>

namespace ss
{
    struct homotopy_report
    {
        /* the number of iterations performed. */
        std::uint32_t iter;

        /* the solution error */
        double solution_error;
    };

    /* make std::variant happy */
    inline bool operator== (const homotopy_report&, const homotopy_report&) { return false; }

    /* A solver policy which implements the homotopy method */
    struct homotopy_policy
    {
        using report_type = homotopy_report;
        
        template <typename T> using state_type = const ndspan<T, 2>;
        
        kernelpp::maybe<homotopy_report> run(
            state_type<float>&, const ndspan<float>, float, std::uint32_t, ndspan<float>);

        kernelpp::maybe<homotopy_report> run(
            state_type<double>&, const ndspan<double>, double, std::uint32_t, ndspan<double>);

        homotopy_policy();
        homotopy_policy(homotopy_policy&&);

        ~homotopy_policy();
    };
}