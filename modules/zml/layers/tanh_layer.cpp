#include <glog/logging.h>
#include "tanh_layer.hpp"

namespace z {
template<typename T>
void TanhLayer<T>::setup(const vector<container_type *> &input,
                         const vector<container_type *> &output)
{
    LOG(INFO) << "Setting up " << param_.name();
    LOG(INFO) << "input  #0: "  << input[0]->shape();

    output[0]->reshape(input[0]->shape());
    LOG(INFO) << "output #0: "  << output[0]->shape();
}

template<typename T>
void TanhLayer<T>::ForwardCPU(const vector<container_type *> &input,
                              const vector<container_type *> &output)
{
    auto input_data = input[0]->data();
    auto count = input[0]->count();
    auto output_data = output[0]->data();

    for(auto i = 0; i < count; ++i) {
        output_data[i] = std::tanh(input_data[i]);
    }
}

template<typename T>
void TanhLayer<T>::BackwardCPU(const vector<container_type *> &input,
                               const vector<container_type *> &output)
{
    auto count = input[0]->count();
    auto output_data = output[0]->data();
    auto input_diff = input[0]->diff();
    auto output_diff = output[0]->diff();

    for(auto i = 0; i < count; ++i) {
        auto tx = output_data[i];
        input_diff[i] = output_diff[i] *(1 - tx * tx);
    }
}

template class TanhLayer<float>;
template class TanhLayer<double>;

}