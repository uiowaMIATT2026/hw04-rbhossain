#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCurvatureAnisotropicDiffusionImageFilter.h"
#include "itkCastImageFilter.h"

#include "CurvatureADCLP.h"

int main(int argc, char* argv[])
{
  PARSE_ARGS;

  using ShortImageType = itk::Image<short, 3>;
  using FloatImageType = itk::Image<float, 3>;

  // Read input
  auto reader = itk::ImageFileReader<ShortImageType>::New();
  reader->SetFileName(inputVolume);

  // Cast short to float 
  auto castIn = itk::CastImageFilter<ShortImageType, FloatImageType>::New();
  castIn->SetInput(reader->GetOutput());

  // Curvature Anisotropic Diffusion filter
  using FilterType = itk::CurvatureAnisotropicDiffusionImageFilter<FloatImageType, FloatImageType>;
  auto filter = FilterType::New();
  filter->SetInput(castIn->GetOutput());
  filter->SetConductanceParameter(conductance);
  filter->SetTimeStep(timeStep);
  filter->SetNumberOfIterations(iterations);

  // Cast float to short for output
  auto castOut = itk::CastImageFilter<FloatImageType, ShortImageType>::New();
  castOut->SetInput(filter->GetOutput());

  // Write output
  auto writer = itk::ImageFileWriter<ShortImageType>::New();
  writer->SetFileName(outputVolume);
  writer->SetInput(castOut->GetOutput());

  try
  {
    writer->Update();
  }
  catch(const itk::ExceptionObject& err)
  {
    std::cerr << "Error: " << err << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
