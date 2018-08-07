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

#ifdef HAVE_CONFIG_H
#include "config.h"
#include "math.h"
#endif

#include <gnuradio/io_signature.h>
#include <ecss/variables_loop_filter.h>

namespace gr {
  namespace ecss {

    #ifndef M_TWOPI
    #define M_TWOPI (2.0*M_PI)
    #endif

    variables_loop_filter::variables_loop_filter(int index_m, float natural_freq, float damping, int samp_rate) :
    omega(natural_freq * M_TWOPI), samp(samp_rate), damp(damping), m(index_m)
    {
      evaluation();
    }

    variables_loop_filter::~variables_loop_filter()
    {}

    void
    variables_loop_filter::evaluation(){
      double a;
      double b;
      double c;
      double denom_2, denom_3;

      a= (m+2)*damp;
      b= 1 + 2*m*damp*damp;
      c= m*damp;
      denom_3 = 8 + 4*b*(omega/samp) + 2*a*(omega/samp)*(omega/samp)+ c*(omega/samp)*(omega/samp)*(omega/samp);
      coeff1_3 = (8*b*(omega/samp) + 2*c*(omega/samp)*(omega/samp)) / denom_3;
      coeff2_3 = (8*a*(omega/samp)*(omega/samp) - 4*c*(omega/samp)*(omega/samp)*(omega/samp)) / denom_3;
      coeff3_3 = (8*c*(omega/samp)*(omega/samp)*(omega/samp)) / denom_3;

      loop_bw = omega * sqrt( 1 + 2* damp + sqrt(pow((2*damp*damp + 1),2.0) + 1));
      denom_2= (1.0 + 2.0*damp*loop_bw + loop_bw*loop_bw);
      coeff1_2 =  (4*damp*loop_bw) / denom_2;
      coeff2_2 = (4*loop_bw*loop_bw) / denom_2;

    }

    void
    variables_loop_filter::set_index_m(int index_m){
      m = index_m;
      evaluation();
    }

    void
    variables_loop_filter::set_natural_freq(float natural_freq){
      omega = M_TWOPI * natural_freq;
      evaluation();
    }

    void
    variables_loop_filter::set_damping(float damping){
      damp = damping;
      evaluation();
    }

    void
    variables_loop_filter::set_samp_rate(int samp_rate){
      samp = samp_rate;
    }

    double
    variables_loop_filter::get_coeff1_2() const {
      return coeff1_2;
    }

    double
    variables_loop_filter::get_coeff2_2() const {
      return coeff2_2;
    }

    double
    variables_loop_filter::get_coeff1_3() const {
      return coeff1_3;
    }

    double
    variables_loop_filter::get_coeff2_3() const {
      return coeff2_3;
    }

    double
    variables_loop_filter::get_coeff3_3() const {
      return coeff3_3;
    }


  } /* namespace ecss */
} /* namespace gr */
