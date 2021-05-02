#ifndef _GRAPH_ALGOTITHMS_KRUSKAL_H_
#define _GRAPH_ALGOTITHMS_KRUSKAL_H_

#include "THeap.h"
#include "TDisjointSet.h"
#include "TGraph.h"

namespace GraphAlgorithms
{
    TGraph kruskalAlgorithm(const TGraph& graph);
}

#endif