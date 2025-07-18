C Deeply ([cdeeply.com](https://www.cdeeply.com)) builds neural networks *very quickly* from small training datasets (<100 kB).
The web portal and APIs allow a 1 second computation time, used for architecture search and network training.

This repository contains the APIs that allow C Deeply's algorithms to be called directly by another application
rather than manually through web form submissions.  The current interfaces are:

- C / C++
- MATLAB / Octave
- Python
- R
- UNIX Bash scripts -- these embed neural networks in [myNN.html](https://github.com/cdeeply/cdeeply/blob/main/myNN.html), just as the web portal does

Each interface gives access to two methods:

- Supervised training (regression), used to predict certain columns/rows from others in a numeric table.
- Unsupervised training to find features in tabular data.  The algorithm can produce an autoencoder, or just an encoder or decoder.

Additional methods (e.g. reinforcement training, methods to use on image/audio data, etc) will be added as they are developed.

Questions or comments should be directed to:  [info@cdeeply.com](mailto:info@cdeeply.com).

<!---
cdeeply/cdeeply is a ✨ special ✨ repository because its `README.md` (this file) appears on your GitHub profile.
You can click the Preview link to take a look at your changes.
--->
