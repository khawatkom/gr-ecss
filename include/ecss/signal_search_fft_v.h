/* -*- c++ -*- */
/*
 * Copyright 2018 Antonio Miraglia - ISISpace.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_ECSS_SIGNAL_SEARCH_FFT_V_H
#define INCLUDED_ECSS_SIGNAL_SEARCH_FFT_V_H

#include <ecss/api.h>
#include <gnuradio/block.h>

namespace gr
{
  namespace ecss
  {

    /*!
     * \brief Signal Search with FFT Algorithm evaluation.
     *
     * \ingroup ecss
     *
     * \details This block uses an FFT Algorithm to analyze the input 
     * signal.
     * An SNR estimation is performed on input. In addition, also a decimation on input is performed.
     */
    class ECSS_API signal_search_fft_v : virtual public gr::block
    {
      public:
          /*!
        * \brief Return a shared_ptr to a new instance of ecss::signal_search_fft_v.
        */
        typedef boost::shared_ptr<signal_search_fft_v> sptr;

        /*!
            * \brief Signal Search with Goertzel Algorithm evaluation.
            *
            * \param samp_rate Sampling rate of signal;
            * \param fftsize size of fft performed for SNR evaluation;
            * \param decimation decimation of input before fft evaluation;
            * \param wintype windows type for fft evaluation;
            * \param enable if disabeld, the block becomes transparent;
            * \param average if average (with IIR Filters) at the output of FFT is applied or not
            * \param freq_central this is the centre of the bandwidth where the signal is searched, 
            * it must be an integer multiple of the sampling frequency (samp rate).
            * \param bandwidth value of bandwidth where the signal is searched.
            * \param freq_cutoff value of cut-off frequency of the internal IIR used to filer the output of the internal bandwidth.
            * \param threshold it is the minimum difference that must to be between the central band and the lateral ones in order to discriminate if there is
        */
        static sptr make(bool enable, int fftsize, int decimation, bool average, int wintype, float freq_central, float bandwidth, float freq_cutoff, float threshold, float samp_rate);

        virtual float get_freq_central() const = 0;
        virtual float get_bandwidth() const = 0;
        virtual float get_freq_cutoff() const = 0;
        virtual float get_threshold() const = 0;
        virtual bool get_average() const = 0;
        virtual int get_decimation() const = 0;
        virtual int get_fftsize() const = 0;
        virtual bool get_enable() const = 0;
      
        virtual void set_freq_central(float freq_central) = 0;
        virtual void set_bandwidth(float bandwidth) = 0;
        virtual void set_freq_cutoff(float freq_cutoff) = 0;
        virtual void set_threshold(float threshold) = 0;
        virtual void set_average(bool average) = 0;
        virtual void set_enable(bool enable) = 0;
    };

  } // namespace ecss
} // namespace gr

#endif /* INCLUDED_ECSS_SIGNAL_SEARCH_FFT_V_H */
