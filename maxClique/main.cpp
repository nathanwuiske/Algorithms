#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <fstream>
#include <queue>
#include <math.h>
#include <list>
#include <stdio.h>
#include <string>
#include <vector>
#include "structs.h"

using namespace std;

int storeU[maximum][maximum];
int progK, storeN, storeNSize;
int maximumD;
int maximalNum;
double lvl;
fArray storeQ;
firstArray edges[maximum];
fArray arrD[maximum];
secondArray vertices;
fArray maxOfQ;
secondArray storeS;

int intersectCheck(int c, fArray &storeC) {
  int countJ;
  int valCheck = 1;
  for (countJ = 0; countJ < storeC.totalSize; countJ++)
  {
    if (storeU[c][storeC.element[countJ]] == valCheck)
    {
       break;
    }
  }
  if (countJ == storeC.totalSize)
  {
      return 0;
  }
  else
  {
      return 1;
  }
}

void degSort(secondArray arrayK) {
  firstArray eArray2;
  eArray2.element = (int*) calloc(arrayK.totalSize, sizeof(int));
  int storeTemp, storeH;
  for (int i = 0; i < arrayK.totalSize; i++)
  {
    eArray2.element[i] = 0;
    for (int j = 0; j < i; j++)
    {
      if (storeU[arrayK.element[i].storeP][arrayK.element[j].storeP])
      {
        eArray2.element[j]++;
        eArray2.element[i]++;
      }
    }
  }
  //  sort in descending order - taking degree into account
  for (int i = 0; i < arrayK.totalSize; i++)
  {
    storeH = i;
    for (int j = i + 1; j < arrayK.totalSize; j++)
    {
      if (eArray2.element[storeH] < eArray2.element[j])
      {
        storeH = j;
      }
    }
    storeTemp = arrayK.element[i].storeP;
    arrayK.element[i].storeP = arrayK.element[storeH].storeP;
    arrayK.element[storeH].storeP = storeTemp;
    storeTemp = eArray2.element[i];
    eArray2.element[i] = eArray2.element[storeH];
    eArray2.element[storeH] = storeTemp;
  }
}

void copying(fArray &storeX, fArray storeY) {
  for (int count = 0; count < storeY.totalSize; count++)
  {
      storeX.element[count] = storeY.element[count];
  }
  storeX.totalSize = storeY.totalSize;
}
int intersectCheck2(int c, secondArray arrA, secondArray &arrB) {
  arrB.totalSize = 0;
  int valueCheck = 0;
  for (int j = 0; j < arrA.totalSize - 1; j++)
  {
    if (storeU[c][arrA.element[j].storeP] == 1)
    {
        arrB.element[arrB.totalSize++].storeP = arrA.element[j].storeP;
    }
  }
  if (arrB.totalSize == valueCheck)
  {
      return 0;
  }
  else
  {
      return 1;
  }
}

void numSort(secondArray &storeL) {
  int checki = 0, j = 0, storeG, storeK, minimumOfG;
  int checkValue = 0;
  maximalNum = 1;
  minimumOfG = maxOfQ.totalSize - storeQ.totalSize + 1;
  arrD[1].totalSize = 0, arrD[2].totalSize = 0;
  while (checki < storeL.totalSize)
  {
    storeG = 1;
    storeK = storeL.element[checki].storeP;
    while (intersectCheck(storeK, arrD[storeG]) != checkValue)
    {
        storeG++;
    }
    if (storeG > maximalNum)
    {
      maximalNum = storeG;
      arrD[maximalNum+1].totalSize = 0;
    }
    arrD[storeG].element[arrD[storeG].totalSize++] = storeL.element[checki].storeP;
    if (storeG < minimumOfG)
    {
      storeL.element[j++].storeP = storeL.element[checki].storeP;
    }
    checki++;
  }
  if (j > checkValue) storeL.element[j-1].storeM = 0;
  {
    if (minimumOfG <= checkValue) minimumOfG = 1;
    {
        for (storeG = minimumOfG; storeG <= maximalNum; storeG++)
        {
            for (checki = 0; checki < arrD[storeG].totalSize; checki++)
            {
                storeL.element[j].storeP = arrD[storeG].element[checki];
                storeL.element[j++].storeM = storeG;
            }
        }
    }
  }
}

void inflate(secondArray paraR, int l) {
  secondArray arrayP;
  int storeI, valueCheck = 0;
  storeS.element[l].storeP = storeS.element[l].storeP + storeS.element[l - 1].storeP - storeS.element[l].storeM;
  storeS.element[l].storeM = storeS.element[l - 1].storeP;

  while (paraR.totalSize != valueCheck)
  {
    // give storeI last vertex in paraR
    storeI = paraR.element[paraR.totalSize - 1].storeP;
    if (storeQ.totalSize + paraR.element[paraR.totalSize - 1].storeM > maxOfQ.totalSize)
    {
      storeQ.element[storeQ.totalSize++] = storeI;
      arrayP.element = (component*) calloc(paraR.totalSize, sizeof(component));
      if (intersectCheck2(storeI, paraR, arrayP) != valueCheck)
      {
        if ((double)storeS.element[l].storeP / progK < lvl)
        {
          storeNSize += arrayP.totalSize;
          degSort(arrayP);
          storeN++;
        }
        numSort(arrayP);
        inflate(arrayP, l + 1);
        storeS.element[l].storeP++;
        progK++;
      }
      else if (storeQ.totalSize > maxOfQ.totalSize)
      {
        copying(maxOfQ, storeQ);
      }
      storeQ.totalSize--;
     }
     else
     {
       return;
     }
     paraR.totalSize--;
  }
}

void graphRead(string name) {
  ifstream cliqueFile (name);
  char memoryAlloc[516], t[40]; //create memory swapping allocation
  int i, j, nexti, nextj;
  for (i = 0; i < maximum; i++)
  {
    for (j = 0; j < maximum; j++)
    {
         storeU[i][j] = 0; //reset
    }
  }
  while (!cliqueFile.eof())
   {
    cliqueFile.getline (memoryAlloc, 516);
    if (memoryAlloc[0] == 'p')
    {
      cout << "File details: " << memoryAlloc << endl;
      sscanf(&memoryAlloc[8], "%d", &vertices.totalSize);
      vertices.element = (component*)
      calloc(vertices.totalSize, sizeof(component));
      for (i = 0; i < vertices.totalSize; i++)
      {
        vertices.element[i].storeP = i;
        edges[i].totalSize = 0;
        edges[i].element = (int*)
        calloc(vertices.totalSize, sizeof(int));
      }
    }
    if (memoryAlloc[0] == 'e')
    {
      i = 2, j = 0;
      while (memoryAlloc[i] != ' ')
      {
        t[j++] = memoryAlloc[i];
        i++;
      }
      t[j] = '\0';
      i++, j = 0;
      nexti = atoi(t);
      while (memoryAlloc[i] != ' ')
      {
        t[j++] = memoryAlloc[i]; i++;
      }
      t[j] = '\0';
      nextj = atoi(t);
      nexti--, nextj--;
      edges[nextj].element[edges[nextj].totalSize++] = nexti;
      edges[nextj].element[edges[nexti].totalSize++] = nextj;
      storeU[nexti][nextj] = 1, storeU[nextj][nexti] = 1;
    }
  }
}

void maximumClique() {
  int temp;
  storeQ.totalSize = 0, maxOfQ.totalSize = 0;
  for (int i = 0; i < vertices.totalSize; i++)//sort V in descending order
  {
    for (int j = i + 1; j < vertices.totalSize; j++)
    {
      if (edges[vertices.element[i].storeP].totalSize < edges[vertices.element[j].storeP].totalSize)
      {
        temp = vertices.element[i].storeP;
        vertices.element[i].storeP = vertices.element[j].storeP;
        vertices.element[j].storeP = temp;
      }
    }
  }
  maximumD = edges[vertices.element[0].storeP].totalSize;
  for (int i = 0; i < maximumD; i++)
  {
      vertices.element[i].storeM = i + 1;
  }
  for (int i = maximumD; i < vertices.totalSize; i++)
  {
      vertices.element[i].storeM = maximumD + 1;
  }

  storeS.element = (component*)  calloc(vertices.totalSize, sizeof(component));
  for (int i = 0; i < vertices.totalSize; i++)
  {
    storeS.element[i].storeP = 0, storeS.element[i].storeM = 0;
  }
  inflate(vertices, 1);
}

int main() {
  clock_t t;
  t = clock();
  string filename;
  cout<<"Enter file name (include .clq): ";
  cin>>filename;
  graphRead(filename);
  maximumClique();
  cout << endl << "Maximum clique = " << maxOfQ.totalSize << endl;
  cout << "Time elapsed = " << ((double) (clock() - t)) / CLOCKS_PER_SEC << endl;
  return 0;
}
