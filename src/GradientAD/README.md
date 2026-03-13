# GradientAD

## Test Image
I have used KmeansTest_T1UCharRaw.nii.gz, a 3D T1-weighted brain 
MRI image. Collected from the ITK Example directory.

## Effect of Conductance (timeStep=0.05, iterations=5)
- conductance=1.0: The image appears very similar to the
  original with minimal smoothing. Edges between gray matter, white
  matter, and CSF are sharp and well preserved.
- conductance=2.0: Slightly more smoothing while major
  anatomical boundaries remain clearly defined. Minor noise is reduced
  without significant loss of edge detail.
- conductance=5.0: More aggressive smoothing occurs in uniform regions
  while edges are still reasonably preserved. Higher conductance allows
  more diffusion across boundaries, but the anisotropic nature of the
  filter still protects the strongest edges.

## Effect of Time Step (conductance=1.0, iterations=5)
- timeStep=0.05: Stable and minimal smoothing.
- timeStep=0.1: Slightly more smoothing per iteration, similar effect
  to increasing iterations. Image remains stable and edges are preserved.
- timeStep=0.125: More smoothing visible while edges remain intact.
  This is near the stability limit for 3D images and values higher than 
  this gave warning.

## Effect of Iterations (conductance=1.0, timeStep=0.05)
- iterations=5: Minimal smoothing, very close to original.
- iterations=10: Moderate smoothing, fine details begin to fade slightly
  but major anatomical boundaries remain clearly visible.
- iterations=20: Noticeable smoothing of fine structures while the
  prominent edges such as the brain boundary and major tissue interfaces
  are still well preserved. 

## Recommended Parameters
conductance=2.0, timeStep=0.05, iterations=10 provides the best balance
between noise reduction and edge preservation. 
