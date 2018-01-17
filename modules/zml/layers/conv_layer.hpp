#ifndef _ZML_CONV_LAYER_HPP
#define _ZML_CONV_LAYER_HPP

#include <zml/layer.hpp>

namespace z {

template <typename T>
class ConvolutionLayer : public Layer<T> {
    using container_type = Tensor<T>;
public:
    ConvolutionLayer() = default;
    explicit ConvolutionLayer(const LayerParameter&param): param_(param), conv_param_(param.conv_param()) { }
    ConvolutionLayer(const ConvolutionLayer&) = delete;
    ConvolutionLayer&operator=(const ConvolutionLayer&) = delete;
    virtual ~ConvolutionLayer() = default;

    inline LayerParameter parameter() const { return param_; }

    virtual void setup(const vector<container_type*>&input, const vector<container_type*>&output);

    virtual void ForwardCPU(const vector<container_type*>& input, const vector<container_type*>& output);
    virtual void BackwardCPU(const vector<container_type*>& input, const vector<container_type*>& output);

#ifdef USE_CUDA
    virtual void ForwardGPU(const vector<container_type*>& input, const vector<container_type*>& output);
    virtual void BackwardGPU(const vector<container_type*>& input, const vector<container_type*>& output);
#endif //! USE_CUDA

private:
    LayerParameter param_;
    ConvolutionParameter conv_param_;
    
    shared_ptr<Tensor<T>> kernel_;
    shared_ptr<Tensor<T>> bias_;
    Tensor<T> biaser_;
};


}

#endif //! _ZML_CONV_LAYER_HPP
