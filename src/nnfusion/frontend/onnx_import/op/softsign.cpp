//*****************************************************************************
// Copyright 2017-2020 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

//----------------------------------------------------------------------------------------------
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  Licensed under the MIT License. See License.txt in the project root for license information.
//----------------------------------------------------------------------------------------------

#include <memory>
#include <vector>

#include "ngraph/shape.hpp"
#include "nnfusion/core/operators/abs.hpp"
#include "nnfusion/core/operators/add.hpp"
#include "nnfusion/core/operators/constant.hpp"
#include "nnfusion/core/operators/divide.hpp"

#include "utils/broadcasting.hpp"

#include "softsign.hpp"

namespace ngraph
{
    namespace onnx_import
    {
        namespace op
        {
            namespace set_1
            {
                NodeVector softsign(const Node& node)
                {
                    auto data = node.get_ng_inputs().at(0);

                    std::shared_ptr<ngraph::Node> one_node = std::make_shared<ngraph::op::Constant>(
                        data->get_element_type(), Shape{}, std::vector<double>{1});
                    one_node = make_broadcast_node(one_node, data->get_shape());

                    return {data / (std::make_shared<ngraph::op::Abs>(data) + one_node)};
                }

            } // namespace set_1

        } //namespace op

    } // namespace onnx_import

} // namespace ngraph
