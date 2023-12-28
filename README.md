C Deeply ([cdeeply.com](https://www.cdeeply.com)) is devoted to building AI modules called neural networks *very quickly*.
The web portal allows a 1 second computation time, used for architecture search and network training from a table of numbers.

This repository contains libraries and plugins that allow C Deeply's NN generator to be called directly by another application
rather than manually through the web portal.  Each interface gives access to two NN generators:

- Supervised NN training predicts certain columns/rows from others.  This is similar to what XGBoost accomplishes.
- Unsupervised NN training finds features in the data:  produces an autoencoder, or just an encoder or decoder.

Additional methods (e.g. reinforcement training, training on image/audio data, etc) will be added as they are developed.

All calls to the NN generator are subject to a daily limit.

<!---
cdeeply/cdeeply is a ✨ special ✨ repository because its `README.md` (this file) appears on your GitHub profile.
You can click the Preview link to take a look at your changes.
--->
