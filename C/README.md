C/C++ library to call C Deeply's supervised and unsupervised neural network generators.

Using the library involves four steps:

0) Include `cdeeply.h` and define a variable of type `CDNN` to hold the neural network.
1) Call `cdeeply_tabular_regressor(&myNN, ...)` or `cdeeply_tabular_encoder(&myNN, ...)` to train a neural network in supervised or unsupervised mode.
2) Call `run_CDNN(&myNN, ...)` as many times as you want to process new data.
3) Call `free_CDNN(&myNN)` when you're done.

Function definitions:

errCode = int cdeeply_tabular_regressor(&myNN, numInputs, numOutputs, numSamples,
        &trainingSamples, &importances, transpose, &outputRowOrColumnList,
        maxWeights or `NO_MAX`, maxNeurons or `NO_MAX`, maxLayers or `NO_MAX`, maxLayerSkips or `NO_MAX`,
        `NO_BIAS` or `HAS_BIAS`, `ALLOW_IO_CONNECTIONS` or `NO_IO_CONNECTIONS`, &sampleOutputs or `NULL`, &errorMessageString or `NULL`)

This library requires [libcurl](https://curl.se/libcurl/).  To compile example.c using gcc, enter the command:

gcc cdeeply.c example.c -o example -lm -lcurl
