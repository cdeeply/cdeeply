/*
 *  cdeeply.c - interfaces to neural network generator
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

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cdeeply.h"
//#include <time.h>
//#include <sys/socket.h>
//#include <sys/types.h>
//#include <netdb.h>
//#include <unistd.h>


typedef struct { char *name; char **data; } postField;
typedef struct { void *nextBuffer; int numChars; } bufferType;

//const int timeoutInSec = 30;
//int CDsocket;
char *charPtr, *endChars;
long curlWriteDataSize;
bufferType *readBuffer1;


/*int cdSendAll(char *buffer, size_t numBytes)
{
    ssize_t numBytesWritten;
    struct timeval tTimeout;
    
    tTimeout.tv_sec = timeoutInSec;
    tTimeout.tv_usec = 0;
    setsockopt(CDsocket, SOL_SOCKET, SO_SNDTIMEO, (const char *) &tTimeout, sizeof(tTimeout));
    
    while (numBytes > 0)  {
        numBytesWritten = write(CDsocket, (void *) buffer, numBytes);
        if (numBytesWritten < 0)  return 11;
        else if (numBytesWritten == 0)  return 12;        // timeout
        
        if (numBytesWritten == 0)  usleep(10000);
        else  {
            buffer += numBytesWritten;
            numBytes -= numBytesWritten;
    }   }
    
    return 0;
}


int cdReadAll(char *buffer, size_t numBytes)
{
    ssize_t numBytesRead;
    struct timeval tTimeout;
    
    tTimeout.tv_sec = timeoutInSec;
    tTimeout.tv_usec = 0;
    setsockopt(CDsocket, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tTimeout, sizeof(tTimeout));
    
    while (numBytesRead > 0)  {
        numBytesRead = recv(CDsocket, (void *) buffer, numBytes, 0);
        if (numBytesRead < 0)  return 13;
        
        if (numBytesRead == 0)  usleep(10000);
        else  {
            buffer += numBytesRead;
            numBytes -= numBytesRead;
    }   }
    
    return 0;
}*/


int cdReadNum(void *theNum, int mode)
{
    char *numEnd = charPtr;
    while ((*numEnd != ',') && (*numEnd != ';'))  {
        numEnd++;
        if (numEnd > endChars)  return CD_NN_READ_ERROR;   }
    *numEnd = 0;
    
    if (mode == 0)  sscanf(charPtr, "%i", (int *) theNum);
    else  sscanf(charPtr, "%lg", (double *) theNum);
    
    charPtr = numEnd+1;
    
    return 0;
}

int cdReadInt(int *theInt)  {  return cdReadNum((void *) theInt, 0);  }
int cdReadInts(int *theInts, int numInts)
{
    int i;
    for (i = 0; i < numInts; i++)  {
    if (cdReadInt(theInts + i) != 0)  {
        return CD_NN_READ_ERROR;
    }}
    return 0;
}

int cdReadFloat(double *theFloat)  {  return cdReadNum((void *) theFloat, 1);  }
int cdReadFloats(double *theFloats, int numFloats)
{
    int i;
    for (i = 0; i < numFloats; i++)  {
    if (cdReadFloat(theFloats + i) != 0)  {
        return CD_NN_READ_ERROR;
    }}
    return 0;
}


/*int cdConnect()
{
    int status;
    struct addrinfo hints, *server_info;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    status = getaddrinfo("https://cdeeply.com/myNN.php", "http", &hints, &server_info);
    if (status != 0)  return 2;
    if (server_info->ai_next != NULL)  return 3;
    
    CDsocket = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
    if (CDsocket == -1) return 4;
    
    if (connect(CDsocket, server_info->ai_addr, server_info->ai_addrlen) != 0)  return 5;
    
    return 0;
}*/

// FOR DEBUGGING

#include <stdarg.h>
typedef struct {} CURL;
typedef int CURLcode;
typedef struct {} curl_mime;
typedef struct {} curl_mimepart;
#define CURLOPT_URL 0
#define CURLOPT_WRITEDATA 1
#define CURLOPT_WRITEFUNCTION 2
#define CURL_ZERO_TERMINATED 3
#define CURLE_OK 0
    
void curl_global_init() { }
void curl_global_cleanup() { }
CURL *curl_easy_init() { static CURL c; return &c; }
void curl_easy_setopt(CURL *c, int I, ...) { }
int curl_easy_perform(CURL *c) { return 0; }
int curl_easy_cleanup(CURL *c) { return 0; }
curl_mime *curl_mime_init(CURL *c) { static curl_mime m; return &m; }
curl_mimepart *curl_mime_addpart(curl_mime *c) { static curl_mimepart p; return &p; }
int curl_mime_name(curl_mimepart *m, char *C) { printf("&%s=", C); return 0; }
int curl_mime_data(curl_mimepart *m, char *D, int I) { printf("%s", D); return 0; }
char *dbgStrs[2] = { "4,-1,-1;1,2,2,1;0,0,4,0;0,0,2,2;",
            "0,1,0,2;1,0,2,-1,0,1,-1,2,1;0.990109507373461,-0.035972419924183" };


int cdeeply_getNN(CDNN *NN, char *NNchars, long numChars, double *sampleOutputs, int numSamples)
{
    char header[100];
    int loopChar, rtrn, l, li, inputLayer, numWeights;
    
/*    for (loopChar = 0; loopChar < sizeof(header); loopChar++)  {
        rtrn = cdReadAll(&header[loopChar], 1);
        if (rtrn != 0)  return rtrn;
        if (header[loopChar] == ';')  {
            header[loopChar] = 0;
            break;
    }   }
    sscanf(header, "%ld", &numChars);
    
    NNchars = (char *) malloc(numChars+1);
    if (NNchars == NULL)  return 1;
    rtrn = cdReadAll(NNchars, numChars);
    if (rtrn != 0)  return rtrn;*/
    NNchars[numChars] = ';';
    
    charPtr = NNchars;
    endChars = charPtr+numChars;
    
    if (cdReadInt(&NN->numLayers) != 0)  return CD_NN_READ_ERROR;
    if (cdReadInt(&NN->encoderLayer) != 0)  return CD_NN_READ_ERROR;
    if (cdReadInt(&NN->variationalLayer) != 0)  return CD_NN_READ_ERROR;
    
    NN->layerSize = malloc(NN->numLayers*sizeof(int));
    NN->layerAFs = malloc(NN->numLayers*sizeof(int));
    NN->numLayerInputs = malloc(NN->numLayers*sizeof(int));
    NN->layerInputs = malloc(NN->numLayers*sizeof(int *));
    NN->weights = malloc(NN->numLayers*sizeof(double **));
    NN->y = malloc(NN->numLayers*sizeof(double *));
    if ((NN->layerSize == NULL) || (NN->layerAFs == NULL) || (NN->numLayerInputs == NULL)
            || (NN->layerInputs == NULL) || (NN->weights == NULL) || (NN->y == NULL))
        return CD_OUT_OF_MEMORY_ERROR;
    
    if (cdReadInts(NN->layerSize, NN->numLayers) != 0)  return CD_NN_READ_ERROR;
    if (cdReadInts(NN->layerAFs, NN->numLayers) != 0)  return CD_NN_READ_ERROR;
    if (cdReadInts(NN->numLayerInputs, NN->numLayers) != 0)  return CD_NN_READ_ERROR;
    
    for (l = 0; l < NN->numLayers; l++)  {
        NN->layerInputs[l] = malloc(NN->numLayerInputs[l]*sizeof(int));
        NN->y[l] = malloc(NN->layerSize[l]*sizeof(double));
        if ((NN->layerInputs[l] == NULL) || (NN->y[l] == NULL))  return CD_OUT_OF_MEMORY_ERROR;
        
        if (cdReadInts(NN->layerInputs[l], NN->numLayerInputs[l]) != 0)  return CD_NN_READ_ERROR;
    }
    
    for (l = 0; l < NN->numLayers; l++)  {
        NN->weights[l] = malloc(NN->numLayerInputs[l]*sizeof(double *));
        if (NN->weights[l] == NULL)  return CD_OUT_OF_MEMORY_ERROR;
        
        for (li = 0; li < NN->numLayerInputs[l]; li++)  {
            inputLayer = NN->layerInputs[l][li];
            numWeights = NN->layerSize[l]*NN->layerSize[inputLayer];
            
            NN->weights[l][li] = malloc(numWeights*sizeof(double *));
            if (NN->weights[l][li] == NULL)  return CD_OUT_OF_MEMORY_ERROR;
            
            if (cdReadFloats(NN->weights[l][li], numWeights) != 0)  return CD_NN_READ_ERROR;
    }   }
    
    if (sampleOutputs != NULL)  {
    if (cdReadFloats(sampleOutputs, NN->layerSize[NN->numLayers-1]*numSamples) != 0)  {
        return CD_NN_READ_ERROR;
    }}
    
//    close(CDsocket);
    free(NNchars);
    
    return 0;
}



static size_t curlWriteCallback(void *newData, size_t dataLength, size_t typeSize, void *ptr)
{
    size_t numBytes = dataLength*typeSize;
    bufferType **readBufferH = (bufferType **) ptr;
    
    *readBufferH = (bufferType *) malloc(sizeof(bufferType) + numBytes);
    if (*readBufferH == NULL)  return 0;
    if (readBuffer1 == NULL)  readBuffer1 = *readBufferH;
    
    ((bufferType *) *readBufferH)->nextBuffer = NULL;
    memcpy((void *) ((*readBufferH) + 1), newData, numBytes);
    curlWriteDataSize += numBytes;
    
    return numBytes;
}


int cdeeply_buildNN(CDNN *NN, double *sampleOutputs, int numSamples,
            postField *toPOST, int numPostFields, char **errMsg)
{
    int p, rtrn;
    bufferType *readBuffer;
    char *readBufferChars, *readBufferScanner;
    CURL *curlP;
    curl_mime *mime;
    curl_mimepart *mimePart;
    
    curl_global_init();
    curlP = curl_easy_init();
    mime = curl_mime_init(curlP);
    if ((curlP == NULL) || (mime == NULL))  return CD_OUT_OF_MEMORY_ERROR;
    
    curl_easy_setopt(curlP, CURLOPT_URL, "https://cdeeply.com/myNN.php");
    
    for (p = 0; p < numPostFields; p++)  {
        mimePart = curl_mime_addpart(mime);
        if (mimePart == NULL)  return CD_OUT_OF_MEMORY_ERROR;
        rtrn = curl_mime_name(mimePart, toPOST[p].name);
        if (rtrn != CURLE_OK)  return rtrn;
        rtrn = curl_mime_data(mimePart, *toPOST[p].data, CURL_ZERO_TERMINATED);
        if (rtrn != CURLE_OK)  return rtrn;
    }
    
    rtrn = curl_easy_perform(curlP);
    if (rtrn != CURLE_OK)  return rtrn;
    
    readBuffer1 = NULL;
    curlWriteDataSize = 0;
    curl_easy_setopt(curlP, CURLOPT_WRITEFUNCTION, curlWriteCallback);
    curl_easy_setopt(curlP, CURLOPT_WRITEDATA, (void *) &readBuffer);
    rtrn = curl_easy_perform(curlP);
    if (rtrn != CURLE_OK)  return rtrn;
    
bufferType *buffers[2];
for (int c2 = 0; c2 < 2; c2++)  {
    buffers[c2] = malloc(sizeof(bufferType)+strlen(dbgStrs[c2])+1);
    buffers[c2]->numChars = strlen(dbgStrs[c2]);
    memcpy(buffers[c2]+1, dbgStrs[c2], strlen(dbgStrs[c2]));
}
buffers[0]->nextBuffer = (void *) buffers[1];
buffers[1]->nextBuffer = NULL;
curlWriteDataSize = buffers[0]->numChars + buffers[1]->numChars;
readBuffer = readBuffer1 = buffers[0];

    readBufferScanner = readBufferChars = malloc(curlWriteDataSize+1);
    if (readBufferChars == NULL)  return CD_OUT_OF_MEMORY_ERROR;
    readBuffer = readBuffer1;
    while (readBuffer != NULL)  {
        memcpy(readBufferScanner, readBuffer+1, readBuffer->numChars);
        readBufferScanner += readBuffer->numChars;
        readBuffer1 = readBuffer;
        readBuffer = (bufferType *) readBuffer->nextBuffer;
        free(readBuffer1);
    }
    *readBufferScanner = 0;
/*    rtrn = cdConnect();
    if (rtrn != 0)  return rtrn;*/
    
    if (!((*readBufferChars >= '0') || (*readBufferChars <= '9')))  {
        if (errMsg != NULL)  *errMsg = readBufferChars;
        return CD_PARAMS_ERR;          }
    
    rtrn = cdeeply_getNN(NN, readBufferChars, curlWriteDataSize+1, sampleOutputs, numSamples);
    if (errMsg != NULL)  {
        if (rtrn == CD_NN_READ_ERROR)  *errMsg = "Error reading NN params";
        else if (rtrn == CD_NN_READ_ERROR)  *errMsg = readBufferChars;      }
    
    curl_easy_cleanup(curlP);
    curl_global_cleanup();
    
    return 0;
}


char *rowcol[2] = { "columns", "rows" };
char *checked[2] = { "off", "on" };
char *vDists[2] = { "uniform", "normal" };
char *NNtypes[2] = { "autoencoder", "regressor" };
char *SubmitStr = "Submit";

int cdeeply_tabular_encoder(CDNN *NN, int numInputs, int numOutputs, int numSamples, int transpose, int doEncoder, int doDecoder, int numFeatures, int numVariationalFeatures, int variationalDist, int maxWeights, int maxNeurons, int maxLayers, int maxLayerSkips, int hasBias, double *sampleOutputs, char **errMsg)
{
    int rtrn;
    char strs[120], *numFeaturesStr = &strs[0], *numVFsStr = &strs[20];
    char *maxWeightsStr = &strs[40], *maxNeuronsStr = &strs[60];
    char *maxLayersStr = &strs[80], *maxLayerSkipsStr = &strs[100];
    postField toPOST[] = {
        { "rowscols", &rowcol[transpose] },
        { "numFeatures", &numFeaturesStr },
        { "doEncoder", &checked[doEncoder] },
        { "doDecoder", &checked[doDecoder] },
        { "numVPs", &numVFsStr },
        { "variationalDist", &vDists[variationalDist] },
        { "maxWeights", &maxWeightsStr },
        { "maxNeurons", &maxNeuronsStr },
        { "maxLayers", &maxLayersStr },
        { "maxSkips", &maxLayerSkipsStr },
        { "hasBias", &checked[hasBias] },
        { "submitStatus", &SubmitStr },
        { "NNtype", &NNtypes[0] },
        { "embedInJS", &checked[0] }
    };
    
    sprintf(numFeaturesStr, "%i", numFeatures);
    sprintf(numVFsStr, "%i", numVariationalFeatures);
    maxWeightsStr[0] = maxNeuronsStr[0] = maxLayersStr[0] = maxLayerSkipsStr[0] = 0;
    if (maxWeights >= 0)  sprintf(maxWeightsStr, "%i", maxWeights);
    if (maxNeurons >= 0)  sprintf(maxNeuronsStr, "%i", maxNeurons);
    if (maxLayers >= 0)  sprintf(maxLayersStr, "%i", maxLayers);
    if (maxLayerSkips >= 0)  sprintf(maxLayerSkipsStr, "%i", maxLayerSkips);
    
    rtrn = cdeeply_buildNN(NN, sampleOutputs, numSamples, toPOST, sizeof(toPOST)/sizeof(postField), errMsg);
    
//rowscols=columns&numFeatures=1&doEncoder=on&doDecoder=on&numVPs=0&variationalDist=normal&maxWeights=&maxNeurons=&maxLayers=&maxSkips=&hasBias=on&submitStatus=Submit&NNtype=autoencoder&embedInJS=off
    
    return rtrn;
}


int cdeeply_tabular_regressor(CDNN *NN, int numInputs, int numOutputs, int numSamples, int *outputRowsCols, int transpose, int maxWeights, int maxNeurons, int maxLayers, int maxLayerSkips, int hasBias, int allowIOconnections, double *sampleOutputs, char **errMsg)
{
    int o, charIdx, rtrn;
    char *outputRowsColsStr, strs[80], *maxWeightsStr = &strs[0];
    char *maxNeuronsStr = &strs[20], *maxLayersStr = &strs[40], *maxLayerSkipsStr = &strs[60];
    postField toPOST[] = {
        { "rowscols", &rowcol[transpose] },
        { "rowcolRange", &outputRowsColsStr },
        { "maxWeights", &maxWeightsStr },
        { "maxNeurons", &maxNeuronsStr },
        { "maxLayers", &maxLayersStr },
        { "maxSkips", &maxLayerSkipsStr },
        { "hasBias", &checked[hasBias] },
        { "allowIO", &checked[allowIOconnections] },
        { "submitStatus", &SubmitStr },
        { "NNtype", &NNtypes[1] },
        { "embedInJS", &checked[0] }
    };
    
    outputRowsColsStr = malloc(numOutputs*20*sizeof(int));
    if (outputRowsColsStr == NULL)  return CD_OUT_OF_MEMORY_ERROR;
    
    if (numOutputs <= 0)  {  charIdx = 0; outputRowsColsStr[0] = 0;  }
    else  {
        charIdx = sprintf(outputRowsColsStr, "%i", outputRowsCols[0]);
        for (o = 1; o < numOutputs; o++)  {
            charIdx += sprintf(outputRowsColsStr + charIdx, ",%i", outputRowsCols[o]);
    }   }
    
    maxWeightsStr[0] = maxNeuronsStr[0] = maxLayersStr[0] = maxLayerSkipsStr[0] = 0;
    if (maxWeights >= 0)  sprintf((char *) maxWeightsStr, "%i", maxWeights);
    if (maxNeurons >= 0)  sprintf(maxNeuronsStr, "%i", maxNeurons);
    if (maxLayers >= 0)  sprintf(maxLayersStr, "%i", maxLayers);
    if (maxLayerSkips >= 0)  sprintf(maxLayerSkipsStr, "%i", maxLayerSkips);
    
    rtrn = cdeeply_buildNN(NN, sampleOutputs, numSamples, toPOST, sizeof(toPOST)/sizeof(postField), errMsg);
    
    free(outputRowsColsStr);
//rowscols=columns&rowcolRange=1&maxWeights=&maxNeurons=&maxLayers=&maxSkips=&hasBias=on&allowIO=on&submitStatus=Submit&NNtype=regressor&embedInJS=off
    
    return rtrn;
}



double linearAF(const double x)  {  return x;  }

double (*fs[5])(const double) = { &linearAF, NULL, NULL, NULL, &tanh };

double *run_CDNN(CDNN *NN, double *inputs)
{
    int l, li, l0, n, i, i0;
    double *w;
    
    NN->y[0][0] = 1;
    memcpy(NN->y[1], inputs, NN->layerSize[1]*sizeof(double));
    if (NN->variationalLayer > 0)  memcpy(NN->y[NN->variationalLayer],
            inputs+NN->layerSize[1], NN->layerSize[NN->variationalLayer]*sizeof(double));
    
    for (l = 2; l < NN->numLayers; l++)  {
    if (l != NN->variationalLayer)  {
        for (n = 0; n < NN->layerSize[l]; n++)  NN->y[l][n] = 0.;
        for (li = 0; li < NN->numLayerInputs[l]; li++)  {
            l0 = NN->layerInputs[l][li];
            w = NN->weights[l][li];
            for (i = 0; i < NN->layerSize[l]; i++)  {
            for (i0 = 0; i0 < NN->layerSize[l0]; i0++)  {
                NN->y[l][i] += (*w) * NN->y[l0][i0];
                w++;
        }   }}
        for (n = 0; n < NN->layerSize[l]; n++)  {
            NN->y[l][n] = fs[NN->layerAFs[l]](NN->y[l][n]);
    }}  }
    
    return NN->y[NN->numLayers-1];
}


void free_CDNN(CDNN *NN)
{
    int l, li;
    
    for (l = 0; l < NN->numLayers; l++)  {
        for (li = 0; li < NN->numLayerInputs[l]; li++)  {
            free(NN->weights[l][li]);       }
        
        free(NN->layerInputs[l]);
        free(NN->weights[l]);
        free(NN->y[l]);
    }
    
    free(NN->layerSize);
    free(NN->layerAFs);
    free(NN->numLayerInputs);
    free(NN->layerInputs);
    free(NN->weights);
    free(NN->y);
}
