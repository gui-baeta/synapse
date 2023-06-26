#!/usr/bin/env python3

import argparse
import numpy as np
import sys

from matplotlib import pyplot as plt

HISTOGRAM_STEP = 8
XTICKS_STEP = 64
MIN_SIZE = 64
MAX_SIZE = 1500

if __name__ == '__main__':
	parser = argparse.ArgumentParser(
		description='Visualize packet size distribution generated by the stats program\n')
	parser.add_argument('data', type=str)
	args = parser.parse_args()

	with open(args.data) as f:
		sizes = np.loadtxt(f, delimiter='\t', dtype='int', usecols=None)
		assert len(sizes)
		
		v_hist = []
		if type(sizes[0]) == np.ndarray:
			for s in sizes:
				v_hist += [ s[0] ] * s[1]
		else:
			v_hist = [ sizes[0] ] * sizes[1]
		
		bins = [ MIN_SIZE ]
		while bins[-1] + HISTOGRAM_STEP < MAX_SIZE:
			bins.append(bins[-1] + HISTOGRAM_STEP)
		bins.append(MAX_SIZE)

		xticks = [ MIN_SIZE ]
		while xticks[-1] + XTICKS_STEP < MAX_SIZE:
			xticks.append(xticks[-1] + XTICKS_STEP)
		xticks.append(MAX_SIZE)

		plt.hist(v_hist, bins=bins, density=True)
		plt.xticks(xticks)
		plt.show()