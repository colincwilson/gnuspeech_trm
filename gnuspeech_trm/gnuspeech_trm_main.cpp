/**
 *  gnuspeech_trm -- Standalone gnuspeech articulatory synthesiser
 *  Copyright (C) 2018  Andreas Stöckel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <unistd.h>

#include "gnuspeech_trm.h"

#define SAMPLE_COUNT 1024

int main()
{
	gnuspeech_trm_t trm = gnuspeech_trm_create();

	gnuspeech_trm_set_config(trm, TRM_CONF_VOLUME, 60.0);
	gnuspeech_trm_set_config(trm, TRM_CONF_FILTER_PERIOD, 10e-3);

	gnuspeech_trm_set_parameter(trm, TRM_PARAM_GLOT_PITCH, -1);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_GLOT_VOL, 60);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_VELUM, 0.1);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_FRIC_VOL, 40);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_FRIC_POS, 0.1);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_FRIC_BW, 220.0);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_FRIC_CF, 100.0);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_R1, 1.0);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_R1, 0.3);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_R2, 0.2);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_R3, 1.0);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_R4, 1.0);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_R5, 0.1);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_R6, 0.1);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_R7, 0.1);
	gnuspeech_trm_set_parameter(trm, TRM_PARAM_R8, 1.0);

	float samples[SAMPLE_COUNT];
	for (int i = 0; i < 40; i++) {
		int n = gnuspeech_trm_synthesize(trm, samples, SAMPLE_COUNT, false);
		if (n < 0) {
			return 1;  // Panic! Abort!
		}
		write(STDOUT_FILENO, samples, sizeof(float) * n);
	}

	gnuspeech_trm_free(trm);
	return 0;
}
