# GaussianLPF

## Test Image
I have used KmeansTest_T1UCharRaw.nii.gz,
a 3D T1-weighted brain MRI image. Collected from the
ITK Example directory.

## sigma = 0.5
At sigma = 0.5, the filtered image is visually identical to the original.
The Gaussian kernel is very narrow, so only immediately neighboring voxels
are averaged together. I can still see the sharp edges between gray and white
matter, and the boundaries are all fully preserved.

## sigma = 2.5
At sigma = 2.5, the image becomes noticeably blurry. The fine structural
details of the brain are no longer clearly visible. The boundaries between 
gray matter, white matter, and CSF become indistinct. The overall image appears
washed out compared to the original. Which indicats loss of spatial resolution.

## sigma = 5.0
At sigma = 5.0, the image is severely blurred.This is how I see things without 
glasses. All fine anatomical detail is lost. Only the gross outline of the
brain and the largest structures are visible.
