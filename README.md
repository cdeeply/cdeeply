C Deeply ([cdeeply.com](https://www.cdeeply.com)) builds neural networks *very quickly* from tables of numbers.
The web portal allows a 1 second computation time, used for architecture search and network training.

This repository contains libraries and plugins that allow C Deeply's algorithms to be called directly by another application
rather than manually through the web portal.  The current interfaces are:

- UNIX Bash scripts -- these return the neural network embedded in an HMTL file, rather than the raw data

Each interface gives access to two methods:

- Supervised training (regression) is used to predict certain columns/rows from others in the table.  This is similar to what XGBoost accomplishes.
- Unsupervised training finds features in the data.  The algorithm produces an autoencoder, or just an encoder or decoder.

Additional methods (e.g. reinforcement training, training on image/audio data, etc) will be added as they are developed.

All queries are subject to a daily limit.

<!---
cdeeply/cdeeply is a ✨ special ✨ repository because its `README.md` (this file) appears on your GitHub profile.
You can click the Preview link to take a look at your changes.
--->
