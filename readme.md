# neural network from scatch
trying to build a neural network using c from scratch


# TODO
## MUST
- [x] insert type of layer into the layer type, figure out what return type to use. Probably it's a good idea to make error struct common between all activation functions to avoid issues
- [ ] make the forward propagation function
    - [x] weights calculation
    - [ ] add biases calculation
- [ ] make the backpropagation function
    - [ ] adjust the weights values
    - [ ] adjust the biases values
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




### note
I made the math functions wrong so attaching an array created inside the function to the array inside the struct of the Matrix, i have to do something to make sure that this lives for longer like allocating it in the heap and free it only when needed otherwise it ruins everything. This bug is present both in the multiplication function and in the sum function.

