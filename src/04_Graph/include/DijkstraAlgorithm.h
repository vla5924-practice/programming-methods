#ifndef _GRAPH_ALGOTITHMS_KRUSKAL_H_
#define _GRAPH_ALGOTITHMS_KRUSKAL_H_

#include "THeap.h"
#include "TGraph.h"
#include "TPathData.h"

namespace GraphAlgorithms
{
    TPathData dijkstraAlgorithm(const TGraph& graph, TVertexId startVertex = 0);
}

#endif