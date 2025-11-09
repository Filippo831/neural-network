# neural network from scatch
trying to build a neural network using c from scratch


# TODO
## MUST
- [x] insert type of layer into the layer type, figure out what return type to use. Probably it's a good idea to make error struct common between all activation functions to avoid issues
- [x] make the forward propagation function
    - [x] weights calculation
    - [x] add biases calculation
    - [x] fix all the functions
- [x] make the backpropagation function
    - [x] adjust the weights values
    - [x] adjust the biases values
- [ ] create the convolutional type of layer
- [ ] make the neural network easily configurable
- [ ] fix the way you add new layers because it's quite stupid at the moment. Make it less redundant. Maybe without a number of layer as a contraint but with an expandable vectore that can be modified dynamically

**MAYBE**
- [ ] insert the type of activation function inside the layer struct to change it dynamically

# DOCUMENTATION

## Layer Types implemented
### classic
- dot product between weights and input
- sum biases
- sigmoid to flatten values

## Activation functions implemented
- sigmoid




