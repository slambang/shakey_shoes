//=======================================================================
/** @file CoreFrequencyDomainFeatures.cpp
 *  @brief Implementations of common frequency domain audio features
 *  @author Adam Stark
 *  @copyright Copyright (C) 2013  Adam Stark
 *
 * This file is part of the 'Gist' audio analysis library
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//=======================================================================


#include "CoreFrequencyDomainFeatures.h"

//===========================================================
template <class T>
CoreFrequencyDomainFeatures<T>::CoreFrequencyDomainFeatures()
{
    
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralCentroid(std::vector<T> magnitudeSpectrum)
{
    // to hold sum of amplitudes
    T sumAmplitudes = 0.0;
    
    // to hold sum of weighted amplitudes
    T sumWeightedAmplitudes = 0.0;
    
    // for each bin in the first half of the magnitude spectrum
    for (int i = 0;i < magnitudeSpectrum.size();i++)
    {
        // sum amplitudes
        sumAmplitudes += magnitudeSpectrum[i];
        
        // sum amplitudes weighted by the bin number
        sumWeightedAmplitudes += magnitudeSpectrum[i]*i;
    }
    
    // if the sum of amplitudes is larger than zero (it should be if the buffer wasn't
    // all zeros)
    if (sumAmplitudes > 0)
    {
        // the spectral centroid is the sum of weighted amplitudes divided by the sum of amplitdues
        return sumWeightedAmplitudes / sumAmplitudes;
    }
    else // to be safe just return zero
    {
        return 0.0;
    }
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralFlatness(std::vector<T> magnitudeSpectrum)
{
    double sumVal = 0.0;
    double logSumVal = 0.0;
    double N = (double) magnitudeSpectrum.size();
    
    T flatness;
    
    for (int i = 0;i < magnitudeSpectrum.size();i++)
    {
        // add one to stop zero values making it always zero
        double v = (double) (1+magnitudeSpectrum[i]);
        
        sumVal += v;
        logSumVal += log(v);
    }
    
    sumVal = sumVal / N;
    logSumVal = logSumVal / N;
    
    if (sumVal > 0)
    {
        flatness = (T) (exp(logSumVal) / sumVal);
    }
    else
    {
        flatness = 0.0;
    }
    
    return flatness;
}

//===========================================================
template <class T>
T CoreFrequencyDomainFeatures<T>::spectralCrest(std::vector<T> magnitudeSpectrum)
{
    T sumVal = 0.0;
    T maxVal = 0.0;
    T N = (T) magnitudeSpectrum.size();
    
    for (int i = 0;i < magnitudeSpectrum.size();i++)
    {
        T v = magnitudeSpectrum[i]*magnitudeSpectrum[i];
        sumVal += v;
        
        if (v > maxVal)
        {
            maxVal = v;
        }
    }
      
    T spectralCrest;
    
    if (sumVal > 0)
    {
        T meanVal = sumVal / N;
        
        spectralCrest = maxVal / meanVal;
    }
    else
    {
        // this is a ratio so we return 1.0 if the buffer is just zeros
        spectralCrest = 1.0;
    }
    
    return spectralCrest;
}

//===========================================================
template class CoreFrequencyDomainFeatures<float>;
template class CoreFrequencyDomainFeatures<double>;
