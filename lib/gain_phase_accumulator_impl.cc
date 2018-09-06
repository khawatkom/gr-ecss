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
#endif

#include <gnuradio/io_signature.h>
#include "gain_phase_accumulator_impl.h"

namespace gr {
  namespace ecss {

    gain_phase_accumulator::sptr
    gain_phase_accumulator::make(int N, int uplink, int downlink)
    {
      return gnuradio::get_initial_sptr
        (new gain_phase_accumulator_impl(N, uplink, downlink));
    }

    gain_phase_accumulator_impl::gain_phase_accumulator_impl(int N, int uplink, int downlink)
      : gr::sync_block("gain_phase_accumulator",
              gr::io_signature::make(1, 1, sizeof (int64_t)),
              gr::io_signature::make(1, 1, sizeof (int64_t))),
              d_uplink(uplink), d_downlink(downlink), d_N(N)
    {
      precision = pow(2,(- (N - 1)));
    }

    gain_phase_accumulator_impl::~gain_phase_accumulator_impl()
    {}

    int
    gain_phase_accumulator_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const int64_t *in = (const int64_t *) input_items[0];
      int64_t *out = (int64_t *) output_items[0];

      double temp_denormalized;
      int64_t temp_integer_phase;

      for (int i = 0; i < noutput_items; i++){
        temp_integer_phase = (in[i] >> (64 - d_N));
        temp_denormalized = (double)(temp_integer_phase * precision);
        temp_denormalized = temp_denormalized * double(d_downlink / d_uplink);
        temp_integer_phase = (int64_t)(temp_denormalized / precision);
        out[i] = (temp_integer_phase << (64 - d_N));
      }
      return noutput_items;
    }

  } /* namespace ecss */
} /* namespace gr */

