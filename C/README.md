C/C++ library to call C Deeply's supervised and unsupervised neural network generators.

Using the library involves four steps:

0) Include `cdeeply.h` and define a variable of type `CDNN` to hold the neural network.
1) Call `cdeeply_tabular_regressor(&myNN, ...)` or `cdeeply_tabular_encoder(&myNN, ...)` to train a neural network in supervised or unsupervised mode.
2) Call `run_CDNN(&myNN, ...)` as many times as you want to process new data samples -- one sample per function call.
3) Call `free_CDNN(&myNN)` when you're done.

Function definitions:

`errCode = cdeeply_tabular_regressor(&myNN, numInputs, numOutputs, numSamples,`  
`        &trainingSamples, &importances, sampleTableTranspose, &outputRowOrColumnList,`  
`        maxWeights, maxNeurons, maxLayers, maxLayerSkips,`  
`        ifNNhasBias, ifAllowingInputOutputConnections, &sampleOutputs, &errorMessageString)`  
Generates a x->y prediction network using supervised training.  The 'y's in the table are specified by `outputRowOrColumnList`.

`errCode = cdeeply_tabular_encoder(CDNN *NN, numInputs, numFeatures, numVariationalFeatures, numSamples,`  
`        &trainingSamples, &importances, sampleTableTranspose,`  
`        ifDoEncoder, ifDoDecoder, variationalDist,`  
`        maxWeights, maxNeurons, maxLayers, maxLayerSkips,`  
`        ifNNhasBias, &sampleOutputs, &errorMessageString)`  
Generates an autoencoder (or an encoder or decoder) using unsupervised training.  The size of the encoding is determined by `numFeatures`; optional so-called variational features are extra random inputs used by the decoder.

`outputArray = run_CDNN(&NN, inputArray)`  
Runs the neural network on a set of double-precision inputs, returning a double-precision pointer to the network outputs.  Any variational features should be generated randomly from the appropriate distribution, and appended to `inputArray[]`.

`void free_CDNN(CDNN *NN)`  
Frees memory associated with the neural network.

This library requires [libcurl](https://curl.se/libcurl/).  To compile example.c using gcc, enter the command:

gcc cdeeply.c example.c -o example -lm -lcurl
