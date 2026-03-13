#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkRecursiveGaussianImageFilter.h"
#include "itkSubtractImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkCastImageFilter.h"

#include "DOGCLP.h"

// Apply Gaussian in X, Y, Z directions
itk::Image<float, 3>::Pointer
applyGaussian(itk::Image<float, 3>::Pointer input, double sigma)
{
  using ImageType = itk::Image<float, 3>;
  using GaussianType = itk::RecursiveGaussianImageFilter<ImageType, ImageType>;

  auto gx = GaussianType::New(); gx->SetDirection(0); gx->SetSigma(sigma);
  auto gy = GaussianType::New(); gy->SetDirection(1); gy->SetSigma(sigma);
  auto gz = GaussianType::New(); gz->SetDirection(2); gz->SetSigma(sigma);

  gx->SetInput(input);
  gy->SetInput(gx->GetOutput());
  gz->SetInput(gy->GetOutput());
  gz->Update();
  return gz->GetOutput();
}

int main(int argc, char* argv[])
{
  PARSE_ARGS;

  if(sigma1 == sigma2)
  {
    std::cerr << "Error: sigma1 must not equal sigma2" << std::endl;
    return EXIT_FAILURE;
  }

  using ShortImageType = itk::Image<short, 3>;
  using FloatImageType = itk::Image<float, 3>;
  using UCharImageType = itk::Image<unsigned char, 3>;

  // Read input
  auto reader = itk::ImageFileReader<ShortImageType>::New();
  reader->SetFileName(inputVolume);

  // Cast to float
  auto castIn = itk::CastImageFilter<ShortImageType, FloatImageType>::New();
  castIn->SetInput(reader->GetOutput());
  castIn->Update();

  // Apply two Gaussians with different sigmas
  auto g1 = applyGaussian(castIn->GetOutput(), sigma1);
  auto g2 = applyGaussian(castIn->GetOutput(), sigma2);

  // Subtract: DOG = G_sigma1(f) - G_sigma2(f)
  auto subtract = itk::SubtractImageFilter<FloatImageType>::New();
  subtract->SetInput1(g1);
  subtract->SetInput2(g2);

  // Rescale to [0, 255]
  auto rescale = itk::RescaleIntensityImageFilter<FloatImageType, FloatImageType>::New();
  rescale->SetInput(subtract->GetOutput());
  rescale->SetOutputMinimum(0.0f);
  rescale->SetOutputMaximum(255.0f);

  // Cast to unsigned char
  auto castOut = itk::CastImageFilter<FloatImageType, UCharImageType>::New();
  castOut->SetInput(rescale->GetOutput());

  // Write output
  auto writer = itk::ImageFileWriter<UCharImageType>::New();
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
