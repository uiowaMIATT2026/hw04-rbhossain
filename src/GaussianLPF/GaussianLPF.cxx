#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRecursiveGaussianImageFilter.h"
#include "itkCastImageFilter.h"

#include "GaussianLPFCLP.h"

int main(int argc, char* argv[])
{
  PARSE_ARGS;

  using PixelType = short;
  using RealPixelType = float;
  using ImageType = itk::Image<PixelType, 3>;
  using RealImageType = itk::Image<RealPixelType, 3>;
  using GaussianType = itk::RecursiveGaussianImageFilter<RealImageType, RealImageType>;

  // Read input
  auto reader = itk::ImageFileReader<ImageType>::New();
  reader->SetFileName(inputVolume);

  // Cast short to float for Gaussian processing
  auto castIn = itk::CastImageFilter<ImageType, RealImageType>::New();
  castIn->SetInput(reader->GetOutput());

  // Apply Gaussian in X, Y, Z directions separately
  auto gaussX = GaussianType::New();
  auto gaussY = GaussianType::New();
  auto gaussZ = GaussianType::New();

  gaussX->SetDirection(0); // X
  gaussY->SetDirection(1); // Y
  gaussZ->SetDirection(2); // Z

  gaussX->SetSigma(sigma);
  gaussY->SetSigma(sigma);
  gaussZ->SetSigma(sigma);

  // Add them together
  gaussX->SetInput(castIn->GetOutput());
  gaussY->SetInput(gaussX->GetOutput());
  gaussZ->SetInput(gaussY->GetOutput());

  // Cast float to short for output
  auto castOut = itk::CastImageFilter<RealImageType, ImageType>::New();
  castOut->SetInput(gaussZ->GetOutput());

  // Write output
  auto writer = itk::ImageFileWriter<ImageType>::New();
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
