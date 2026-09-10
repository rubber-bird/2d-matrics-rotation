# BMCC Research - 2d matrics rotation and sinogram

### Build and run

```sh
cmake -B build
cmake --build build
./build/2DRotation
```
cmake -B build && cmake --build build && ./build/2DRotation


Phantom 1 - MSE results
ButterworthFilter - 3096.82
Cosine Filter - 3141.09
HammingFilter - 3244.4
HannFilter - 3279.45
GaussianFilter - 3321.94
SheppLoganFilter - 3512.7
Ramp filter - 4273.2


TODO:
- Use other metrics.
- Use other kind of computation:

Reconstruction, on for each pixel to find which part(s) of the sinogram.
Make a reconstruction without the rotation, but with inverse mapping of
Reconstruction to sinogram. For each R pixel, there should be corresponding
pixel in sinogram.
