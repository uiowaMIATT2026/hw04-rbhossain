# DOG

## Test Image
I have used KmeansTest_T1UCharRaw.nii.gz,
a 3D T1-weighted brain MRI image. Collected from the
ITK Example directory.

## sigma1=1.0, sigma2=2.0 (small sigmas, small difference)
With small sigma values, the DOG filter produces a highly detailed
edge map. A large number of fine edges can be seen. The output has 
many thin bright white lines and a gray background.

## sigma1=2.5, sigma2=3.5 (medium sigmas, small difference)
At medium sigma values, the filter becomes less sensitive to fine
details and responds more strongly to prominent edges. Small
noisy edges disappear while major anatomical boundaries such as
the boundary between gray matter and white matter remain visible.

## sigma1=3.0, sigma2=6.0 (large sigmas, large difference)
With large sigma values and a larger difference between them, the
filter only responds to the most prominent edges in
the image (the boundary of skull). Internal brain structures almost 
completely disappear.
