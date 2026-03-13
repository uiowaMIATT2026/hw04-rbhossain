# CurvatureAD 

## Test Image
I have used KmeansTest_T1UCharRaw.nii.gz, a 3D T1-weighted brain 
MRI image. Collected from the ITK Example directory.

## Effect of Conductance (timeStep=0.05, iterations=5)
- conductance=1.0: Mild smoothing compared to the original.
  The image is slightly softer than the original but edges between
  brain tissues remain clearly visible.
- conductance=2.0: Increased smoothing in uniform regions while
  major anatomical boundaries remain well defined. The gray/white
  matter interface is still clearly distinguishable.
- conductance=5.0: More aggressive smoothing across the image.
  Fine structural details begin to fade but prominent edges such
  as the brain boundary and major tissue interfaces are preserved
  due to the curvature-based stopping function.

## Effect of Time Step (conductance=1.0, iterations=5)
- timeStep=0.01: Very minimal smoothing, almost identical to original.
  Very small timestep means very little diffusion per iteration.
- timeStep=0.03: Slightly more smoothing than 0.01, still very
  close to original with all edges intact.
- timeStep=0.05: Stable smoothing with good edge preservation.
- timeStep=0.1 and 0.125: ITK warns these values may introduce
  instability for CurvatureAD in 3D. The safe maximum for
  CurvatureAD is 0.0625 in 3D images.

## Effect of Iterations (conductance=1.0, timeStep=0.05)
- iterations=5 : Mild smoothing, very close to original.
- iterations=10: Moderate smoothing. Fine details begin to
  soften but major boundaries between gray matter, white matter,
  and CSF are clearly visible.
- iterations=20: Noticeable smoothing throughout the image. The
  curvature-based approach preserves edges better than Gaussian
  at equivalent smoothing levels, keeping anatomical boundaries
  sharp even after 20 iterations.

## Comparison with GradientAD
CurvatureAD produces smoother results overall compared to GradientAD
with the same parameters. CurvatureAD is better at smoothing curved
surfaces while GradientAD is more sensitive to gradient magnitude.

## Recommended Parameters
conductance=2.0, timeStep=0.05, iterations=10 achieves good noise
reduction while preserving anatomically important edges. The safe
timeStep limit for CurvatureAD in 3D is 0.0625.
