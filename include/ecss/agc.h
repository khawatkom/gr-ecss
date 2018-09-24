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


#ifndef INCLUDED_ECSS_AGC_H
#define INCLUDED_ECSS_AGC_H

#include <ecss/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ecss {

    /*!
     * \brief AGC Log-based.
     * \ingroup ecss
     *
     * \details This block generates a complex output signal which is the input complex signal adjusted (amplified or attenuated)in order to become
     * an output signal of fixed rms value.
     * The output rms value will be the value of the reference parameter.
     * In order to be more user friendly, it is possible to set the settling time of the AGC.
     */
    class ECSS_API agc : virtual public gr::sync_block
    {
     public:
       /*!
        * \brief Return a shared_ptr to a new instance of ecss::agc.
        */
      typedef boost::shared_ptr<agc> sptr;

      /*!
        * \brief Make a AGC Log-based.
        *
        * \param samp_rate Sampling rate of signal.
        * \param reference rms value of the output.
        * \param gain initial gain of the AGC.
        * \param attack_time is the expected attack/settling time of the AGC.
       */
      static sptr make(float attack_time, float reference, float gain, float samp_rate);

      virtual float attack_time() const=0;
      virtual float reference() const=0;
      virtual float gain() const=0;
      virtual void set_attack_time(float attack_time)=0;
      virtual void set_reference(float reference)=0;
      virtual void set_gain(float gain)=0;
    };

  } // namespace ecss
} // namespace gr

#endif /* INCLUDED_ECSS_AGC_H */
