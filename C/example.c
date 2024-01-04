/*
 *  example.c - interfaces to neural network generator
 *  
 *  C Deeply
 *  Copyright (C) 2023 C Deeply, LLC
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include <stdio.h>
#include "cdeeply.h"


int main(int argc, char **argv)
{
    CDNN NN;
    int rtrn, outRCs[] = { 1 };
    double trainingData[] = { 3, 4, 1, 2, 6, -1 };
    double ins1[] = { 1., 0. }, ins2[] = { .5, 2. }, out1, out2, sampleOuts[2];
    char *errMsg = "no error";
    
    rtrn = cdeeply_tabular_encoder(&NN, 2, 1, 2, trainingData, NULL,
            FEATURE_SAMPLE_ARRAY, DO_ENCODER, DO_DECODER,
            1, 0, NORMAL_DIST, NO_MAX, NO_MAX, NO_MAX, NO_MAX, HAS_BIAS, &sampleOuts[0], &errMsg);
    if (rtrn != 0)  {
        printf("Encoder returned error (%i):  %s\n", rtrn, errMsg);
        return rtrn;    }
    
    free_CDNN(&NN);
    
    rtrn = cdeeply_tabular_regressor(&NN, 2, 1, 2, trainingData, NULL,
            FEATURE_SAMPLE_ARRAY, outRCs,
            NO_MAX, NO_MAX, NO_MAX, NO_MAX, HAS_BIAS, ALLOW_IO_CONNECTIONS, NULL, &errMsg);
    if (rtrn != 0)  {
        printf("Regressor returned error (%i):  %s\n", rtrn, errMsg);
        return rtrn;    }
    
    printf("\nError: %s; rtrn = %i\n", errMsg, rtrn);
    
    out1 = run_CDNN(&NN, ins1)[0];
    out2 = run_CDNN(&NN, ins2)[0];
    printf("Results: %g and %g\n", out1, out2);
printf("sample outs %g %g\n", sampleOuts[0], sampleOuts[1]);
    
    free_CDNN(&NN);
    
    return 0;
}
