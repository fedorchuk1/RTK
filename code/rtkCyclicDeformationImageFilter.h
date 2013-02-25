/*=========================================================================
 *
 *  Copyright RTK Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef __rtkCyclicDeformationImageFilter_h
#define __rtkCyclicDeformationImageFilter_h

#include "rtkConfiguration.h"
#include <itkImageToImageFilter.h>

namespace rtk
{

/** \class CyclicDeformationImageFilter
 * \brief Return 3D deformation vector field according to input 4D vector field,
 * phase signal and frame number.
 *
 * The 4D deformation vector field (DVF) describes the deformation along one cycle.
 * The phase signal is passed via a file name pointing to a text file with one
 * value per line. It must be in the inteval [0,1), 0 meaning frame 0 of the 4D
 * DVF, 0.5 the middle frame (if the number of frames of the 4D DVF is odd), etc.
 * The frame number is the value of the signal for which we wish to obtain the
 * resulting 3D DVF. Linear interpolation is used to compute that DVF.
 * This cyclic deformation model has been described in [Rit et al, TMI, 2009] and
 * [Rit et al, Med Phys, 2009].
 *
 * \author Simon Rit
 *
 * \ingroup ImageToImageFilter
 */
template <class TOutputImage>
class ITK_EXPORT CyclicDeformationImageFilter:
  public itk::ImageToImageFilter<itk::Image<typename TOutputImage::PixelType,
                                            TOutputImage::ImageDimension+1>,
                                 TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef CyclicDeformationImageFilter                                                 Self;
  typedef itk::Image<typename TOutputImage::PixelType, TOutputImage::ImageDimension+1> InputImageType;
  typedef TOutputImage                                                                 OutputImageType;
  typedef itk::ImageToImageFilter<InputImageType, OutputImageType>                     Superclass;
  typedef itk::SmartPointer<Self>                                                      Pointer;
  typedef itk::SmartPointer<const Self>                                                ConstPointer;
  typedef typename OutputImageType::RegionType                                         OutputImageRegionType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(CyclicDeformationImageFilter, itk::ImageToImageFilter);

  /** Get / Set the signal file name relating each frame to a phase position.
      The signal file is a text file containing one line per frame. */
  itkGetMacro(SignalFilename, std::string);
  virtual void SetSignalFilename (const std::string _arg);

  /** Get / Set the frame number. The number is used to lookup in the signal file
   * which phase value should be used to interpolate. */
  itkGetMacro(Frame, unsigned int);
  itkSetMacro(Frame, unsigned int);

protected:
  CyclicDeformationImageFilter() {}
  virtual ~CyclicDeformationImageFilter() {}

  virtual void GenerateOutputInformation();
  virtual void GenerateInputRequestedRegion();
  virtual void BeforeThreadedGenerateData();
  virtual void ThreadedGenerateData( const OutputImageRegionType& outputRegionForThread,
                                     ThreadIdType threadId );


private:
  CyclicDeformationImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&);            //purposely not implemented

  unsigned int m_Frame;

  std::string         m_SignalFilename;
  std::vector<double> m_Signal;

  // Linear interpolation position and weights
  unsigned int m_FrameInf;
  unsigned int m_FrameSup;
  double       m_WeightInf;
  double       m_WeightSup;
};

} // end namespace rtk

#ifndef ITK_MANUAL_INSTANTIATION
#include "rtkCyclicDeformationImageFilter.txx"
#endif

#endif
